import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    current_portfolio = db.execute(
        "SELECT name, symbol, SUM(shares) as shares FROM history GROUP BY symbol HAVING user_id = ?",
        session["user_id"],
    )
    for i in range(len(current_portfolio)):
        dict = lookup(current_portfolio[i]["symbol"])
        current_portfolio[i]["value"] = dict["price"]
        current_portfolio[i]["total"] = (
            current_portfolio[i]["value"] * current_portfolio[i]["shares"]
        )
    sum = 0
    for i in range(len(current_portfolio)):
        sum += current_portfolio[i]["total"]

    cash_dict = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash_dict[0]["cash"]
    full_amount = cash + sum

    return render_template(
        "index.html", rows=current_portfolio, current_cash=cash, grand_total=full_amount
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        # Checking if symbol exists
        if lookup(request.form.get("symbol")) == None:
            return apology("invalid symbol", 400)

        dict = lookup(request.form.get("symbol"))
        share_symbol = dict["symbol"]
        share_number = request.form.get("shares")

        # Checking if positive int
        if not share_number.isdigit():
            return apology("invalid number of shares", 400)
        # Checking if it is positive
        if int(share_number) <= 0:
            return apology("invalid number of shares", 400)

        share_name = dict["name"]
        share_symbol = dict["symbol"]
        share_price = dict["price"]

        cash_dict = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )
        cash = cash_dict[0]["cash"]
        transaction_value = int(share_number) * share_price
        # Condition for not enough cash
        if transaction_value > cash:
            return apology("not enough cash", 400)

        new_cash = cash - transaction_value
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"]
        )
        db.execute(
            "INSERT INTO history (user_id, symbol, name, shares, price, total) VALUES (?, ?, ?, ?, ?, ?)",
            session["user_id"],
            share_symbol,
            share_name,
            share_number,
            share_price,
            transaction_value,
        )

        # If all is correct
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    rows = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    if request.method == "POST":
        if float(request.form.get("addcash")) <= 0:
            return apology("invalid cash number", 403)
        cash_dict = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )
        cash = cash_dict[0]["cash"]
        new_cash = cash + float(request.form.get("addcash"))
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"]
        )
        return redirect("/")
    else:
        return render_template("addcash.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        # Checking if symbol exists
        if lookup(request.form.get("symbol")) == None:
            return apology("invalid symbol", 400)
        # Getting the information and unpacking the dict
        dict = lookup(request.form.get("symbol"))
        quote_name = dict["name"]
        quote_symbol = dict["symbol"]
        quote_price = dict["price"]
        return render_template(
            "quoted.html", name=quote_name, symbol=quote_symbol, price=quote_price
        )
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        # All conditions for blank in form
        if not request.form.get("username"):
            return apology("username is blank", 400)
        if not request.form.get("password"):
            return apology("password or confirmation is blank", 400)
        if not request.form.get("confirmation"):
            return apology("confirmation is blank", 400)
        # Condition for not matching the confirmation
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("password and confirmation do not match", 400)
        # Condition for password already in use
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )
        if len(rows) != 0:
            return apology("username already taken", 400)
        else:
            # Now inserting if the information is valid
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?);",
                request.form.get("username"),
                generate_password_hash(request.form.get("password")),
            )
            return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        # Checking if symbol exists
        if lookup(request.form.get("symbol")) == None:
            return apology("invalid symbol", 400)
        # Checking if it is positive
        if int(request.form.get("shares")) <= 0:
            return apology("invalid number of shares", 400)

        shares_current = db.execute(
            "SELECT SUM(shares) as shares FROM history WHERE symbol = ? AND user_id = ?",
            request.form.get("symbol"),
            session["user_id"],
        )

        if shares_current[0]["shares"] < int(request.form.get("shares")):
            return apology("you don't have that number of shares", 400)

        dict = lookup(request.form.get("symbol"))
        share_name = dict["name"]
        share_symbol = dict["symbol"]
        share_price = dict["price"]
        share_number = request.form.get("shares")
        cash_dict = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )
        cash = cash_dict[0]["cash"]
        transaction_value = int(share_number) * share_price
        transaction_value = -transaction_value
        share_number = "-" + share_number
        new_cash = cash - transaction_value
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"]
        )
        db.execute(
            "INSERT INTO history (user_id, symbol, name, shares, price, total) VALUES (?, ?, ?, ?, ?, ?)",
            session["user_id"],
            share_symbol,
            share_name,
            share_number,
            share_price,
            transaction_value,
        )

        # If all is correct
        return redirect("/")
    else:
        dict = db.execute(
            "SELECT symbol FROM history GROUP BY symbol HAVING user_id = ?",
            session["user_id"],
        )
        return render_template("sell.html", rows=dict)
