from django.contrib.auth import authenticate, login, logout
from django.db import IntegrityError
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render, redirect
from django.urls import reverse
from django.contrib.auth.decorators import login_required
from django.shortcuts import render, get_object_or_404

from .models import User, Category, Listing, Watchlist, Comment, Bid
from .forms import BidForm, ListingForm, CommentForm


def index(request):
    return render(request, "auctions/index.html", {"listings": Listing.objects.all()})


def login_view(request):
    if request.method == "POST":
        # Attempt to sign user in
        username = request.POST["username"]
        password = request.POST["password"]
        user = authenticate(request, username=username, password=password)

        # Check if authentication successful
        if user is not None:
            login(request, user)
            return HttpResponseRedirect(reverse("index"))
        else:
            return render(
                request,
                "auctions/login.html",
                {"message": "Invalid username and/or password."},
            )
    else:
        return render(request, "auctions/login.html")


def logout_view(request):
    logout(request)
    return HttpResponseRedirect(reverse("index"))


def register(request):
    if request.method == "POST":
        username = request.POST["username"]
        email = request.POST["email"]

        # Ensure password matches confirmation
        password = request.POST["password"]
        confirmation = request.POST["confirmation"]
        if password != confirmation:
            return render(
                request, "auctions/register.html", {"message": "Passwords must match."}
            )

        # Attempt to create new user
        try:
            user = User.objects.create_user(username, email, password)
            user.save()
        except IntegrityError:
            return render(
                request,
                "auctions/register.html",
                {"message": "Username already taken."},
            )
        login(request, user)
        return HttpResponseRedirect(reverse("index"))
    else:
        return render(request, "auctions/register.html")


def listing_page(request, slug):
    listing = Listing.objects.get(slug=slug)
    number_bids = Bid.objects.filter(listing=listing).count()
    watchlisted = False
    if request.user.is_authenticated:
        if Watchlist.objects.filter(user=request.user, listing=listing).exists():
            watchlisted = True
    return render(
        request, "auctions/listing.html", {"listing": listing, "Bid_Form": BidForm(), "Comment_Form": CommentForm, "number_bids": number_bids, "comments": listing.comments.all(), "watchlisted": watchlisted}
    )


@login_required(login_url="login")
def addbid(request, slug):
    if request.method == "POST":
        listing = get_object_or_404(Listing, slug=slug)
        if listing.current_bid == None:
            current_value = listing.initial_bid
        else:
            current_value = listing.current_bid.value
        if current_value >= float(request.POST["value"]):
                message = "Invalid bid!"
                return render(
        request, "auctions/listing.html", {"listing": listing, "Bid_Form": BidForm(), "message": message}
    )
        user = get_object_or_404(User, pk=request.user.id)
        bid_form = Bid()
        bid_form.value = request.POST["value"]
        bid_form.listing = listing
        bid_form.bidder = user
        bid_form.save()
        listing.current_bid = bid_form
        listing.save()
        return redirect("listing", slug)
    else:
        return redirect("listing", slug)
    
@login_required(login_url="login")
def addlisting(request):
    if request.method == "POST":
        user = get_object_or_404(User, pk=request.user.id)
        listing_form = Listing()
        listing_form.name = request.POST["name"]
        listing_form.image = request.POST["image"]
        listing_form.description = request.POST["description"]
        listing_form.initial_bid = request.POST["initial_bid"]
        print(request.POST["category"])
        if request.POST["category"]:
            category = get_object_or_404(Category, pk=request.POST["category"])
            listing_form.category = category
        listing_form.vendor = user
        listing_form.save()
        return redirect("listing", listing_form.slug)
    else:
        return render(request, "auctions/addlisting.html", {"ListingForm": ListingForm()})
    
@login_required(login_url="login")
def closelisting(request, slug):
    if request.method == "POST":
        user = get_object_or_404(User, pk=request.user.id)
        listing = get_object_or_404(Listing, slug=slug)
        if user == listing.vendor:
            listing.active = False
            listing.save()
            return redirect("listing", slug)
    else:
        return redirect("listing", slug)

@login_required(login_url="login")
def addcomment(request, slug):
    if request.method == "POST":
        user = get_object_or_404(User, pk=request.user.id)
        listing = get_object_or_404(Listing, slug=slug)
        comment_form = Comment()
        comment_form.body = request.POST["body"]
        comment_form.listing = listing
        comment_form.user = user
        comment_form.save()
        return redirect("listing", slug)
    else:
        return redirect("listing", slug)
    

@login_required(login_url="login")
def addwatchlist(request, slug):
    if request.method == "POST":
        listing = get_object_or_404(Listing, slug=slug)
        user_list, created = Watchlist.objects.get_or_create(user=request.user)
        user_list.listing.add(listing)
        return redirect("listing", slug)
    else:
        return redirect("listing", slug)
    
@login_required(login_url="login")
def remwatchlist(request, slug):
    if request.method == "POST":
        listing = get_object_or_404(Listing, slug=slug)
        user_list, created = Watchlist.objects.get_or_create(user=request.user)
        user_list.listing.remove(listing)
        return redirect("listing", slug)
    else:
        return redirect("listing", slug)
    

@login_required(login_url="login")
def watchlist(request):
    watchlist_object = request.user.watchlist.first()
    watchlist = watchlist_object.listing.all()
    return render(request, "auctions/index.html", {"listings": watchlist, "watchlist": True})

def categories(request):
    categories = Category.objects.all()
    return render(request, "auctions/categories.html", {"categories": categories})

def categories_page(request, category):
    if category == "no_category":
        return render(request, "auctions/index.html", {"listings": Listing.objects.filter(category=None), "in_category": category})
    else:
        category_obj = get_object_or_404(Category, category=category)
        return render(request, "auctions/index.html", {"listings": Listing.objects.filter(category=category_obj), "in_category": category})