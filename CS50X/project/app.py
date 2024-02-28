from helpers import (
    query_artists,
    get_filmography,
    get_details,
    filter_filmography,
    get_movie_details,
)
from flask import Flask, flash, redirect, render_template, url_for, request
import secrets

app_key = secrets.token_urlsafe(16)
app = Flask(__name__)
app.secret_key = app_key


# Basic search box for querying the API for an artist.
@app.route("/", methods=["GET"])
def index():
    return render_template("index.html")


# This is the page for the search results. If there is only one result, we go directly to the options page.
@app.route("/search")
def search():
    artist = request.args.get("q")
    try:
        search_results = query_artists(artist)
    except AttributeError:
        flash(
            "Something went wrong with your request: AttributeError (parameter error). Redirecting to main page:"
        )
        return redirect(url_for("index"))
    if search_results["total_results"] == 1:
        id = search_results["results"][0]["id"]
        url_redir = "/options?id=" + str(id)
        flash("Only one result, redirecting to artist's page:")
        return redirect(url_redir)
    return render_template(
        "search.html", search=search_results["results"], artist=artist
    )


# In this page, the user can select the options for the jobs that they want to see for the artist (Director, Producer, etc.)
@app.route("/options")
def options():
    id = request.args.get("id")
    try:
        details = get_details(id)
    except TypeError:
        flash(
            "Something went wrong with your request: TypeError (ID error). Redirecting to main page:"
        )
        return redirect(url_for("index"))
    try:
        filmography = get_filmography(details["movie_credits"])
    except KeyError:
        flash(
            "Something went wrong with your request: KeyError (parameter error). Redirecting to main page:"
        )
        return redirect(url_for("index"))
    roles = list(filmography.keys())
    return render_template(
        "options.html", roles=roles, filmography=filmography, details=details
    )


# This is the page with all the posters selected by role.
@app.route("/posters")
def posters():
    id = request.args.get("id")
    roles_list = request.args.getlist("o")
    if len(roles_list) == 0:
        flash("Must select at least one option!")
        return redirect(url_for("options") + "?id=" + str(id))
    try:
        details = get_details(id)
    except TypeError:
        flash(
            "Something went wrong with your request: TypeError (ID error). Redirecting to main page:"
        )
        return redirect(url_for("index"))
    try:
        filmography = get_filmography(details["movie_credits"])
    except KeyError:
        flash(
            "Something went wrong with your request: KeyError (parameter error). Redirecting to main page:"
        )
        return redirect(url_for("index"))
    filtered_filmography = filter_filmography(filmography, roles_list)
    for role in roles_list:
        if role.lower() not in list(filtered_filmography):
            flash(
                "Something went wrong with your request: KeyError (parameter error: role inputed not originally listed). Redirecting to main page:"
            )
            return redirect(url_for("index"))
    return render_template(
        "posters.html", filmography=filtered_filmography, details=details
    )


@app.errorhandler(404)
def page_not_found(error):
    flash("Page not found: 404. Redirecting to main page:")
    return redirect(url_for("index"))


@app.route("/artist")
def artist():
    id = request.args.get("p")
    try:
        details = get_details(id)
    except TypeError:
        flash(
            "Something went wrong with your request: TypeError (ID error). Redirecting to main page:"
        )
        return redirect(url_for("index"))
    try:
        filmography = get_filmography(details["movie_credits"])
    except KeyError:
        flash(
            "Something went wrong with your request: KeyError (parameter error). Redirecting to main page:"
        )
        return redirect(url_for("index"))
    roles = list(filmography.keys())
    roles.sort()
    filtered_filmography = filter_filmography(filmography, roles)
    return render_template(
        "artist.html", roles=roles, filmography=filtered_filmography, details=details
    )


@app.route("/movie")
def movie():
    id = request.args.get("m")
    movie_details = get_movie_details(id)
    for type in movie_details["credits"]:
        print(movie_details["credits"][type])

    return render_template("movie.html", details=movie_details)
