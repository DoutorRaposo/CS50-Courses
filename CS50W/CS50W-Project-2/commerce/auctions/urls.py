from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("login", views.login_view, name="login"),
    path("logout", views.logout_view, name="logout"),
    path("register", views.register, name="register"),
    path("add_listing", views.addlisting, name="add_listing"),
    path("listings/<str:slug>", views.listing_page, name="listing"),
    path("listings/<str:slug>/close_listing", views.closelisting, name="close_listing"),
    path("listings/<str:slug>/addbid", views.addbid, name="addbid"),
    path("listing/<str:slug>/addcomment", views.addcomment, name="addcomment"),
    path("listing/<str:slug>/addwatchlist", views.addwatchlist, name="addwatchlist"),
    path("listing/<str:slug>/remwatchlist", views.remwatchlist, name="remwatchlist"),
    path("watchlist", views.watchlist, name="watchlist"),
    path("categories", views.categories, name="categories"),
    path("categories/<str:category>", views.categories_page, name="categories_page")
]
