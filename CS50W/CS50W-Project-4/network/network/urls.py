from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("login", views.login_view, name="login"),
    path("logout", views.logout_view, name="logout"),
    path("register", views.register, name="register"),
    path("post", views.post, name="post"),
    path("get_posts/", views.get_posts, name="filter_posts_by_follower"),
    path("profile/user_id-<int:user_id>/", views.get_profile, name="profile"),
    path("handle_follow", views.handle_follow, name="handle_follow"),
    path("edit_post/<int:post_id>", views.edit_post, name="edit_post"),
    path("like_post", views.like_post, name="like_handler"),
]
