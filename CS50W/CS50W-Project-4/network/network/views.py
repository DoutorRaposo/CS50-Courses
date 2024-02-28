from django.contrib.auth import authenticate, login, logout
from django.db import IntegrityError
from django.http import HttpResponse, HttpResponseRedirect, JsonResponse
from django.shortcuts import render
from django.urls import reverse
import json
from django.views.decorators.csrf import csrf_exempt
from django.contrib.auth.decorators import login_required
from .models import User, Post, FollowingUser
from django.core.paginator import Paginator


# This function gives back which route of series of posts the API user requests. Everything via GET params.
def get_posts(request):
    if type := request.GET.get("type"):
        if (
            request.GET.get("page") != "undefined"
            and request.GET.get("page").isnumeric()
        ):
            if type == "all":
                post_list = Post.objects.all()
                paginator = Paginator(post_list, 10)
                page_obj = paginator.get_page(int(request.GET.get("page")))
                post_series = [x.serialize() for x in page_obj]
                return JsonResponse(
                    {
                        "posts": post_series,
                        "metadata": {
                            "page": page_obj.number,
                            "total_pages": paginator.num_pages,
                            "total_item": paginator.count,
                            "type": type,
                            "view": "all_posts-view",
                        },
                    },
                    status=200,
                    safe=False,
                )
            if type == "profile":
                user_id = request.GET.get("user_id")
                post_list = Post.objects.filter(poster=user_id)
                paginator = Paginator(post_list, 10)
                page_obj = paginator.get_page(int(request.GET.get("page")))
                post_series = [x.serialize() for x in page_obj]
                return JsonResponse(
                    {
                        "posts": post_series,
                        "metadata": {
                            "page": page_obj.number,
                            "total_pages": paginator.num_pages,
                            "total_item": paginator.count,
                            "type": type,
                            "user_id": user_id,
                            "view": "profile-view",
                        },
                    },
                    status=200,
                    safe=False,
                )
            if type == "following":
                user_id = request.GET.get("user_id")
                following = [
                    x.get_following()
                    for x in User.objects.get(id=user_id).following.all()
                ]
                post_list = Post.objects.filter(poster__in=following)
                paginator = Paginator(post_list, 10)
                page_obj = paginator.get_page(int(request.GET.get("page")))
                post_series = [x.serialize() for x in page_obj]
                return JsonResponse(
                    {
                        "posts": post_series,
                        "metadata": {
                            "page": page_obj.number,
                            "total_pages": paginator.num_pages,
                            "total_item": paginator.count,
                            "type": type,
                            "user_id": user_id,
                            "view": "following-view",
                        },
                    },
                    status=200,
                    safe=False,
                )

        else:
            return JsonResponse(
                {"message": "Something went wrong with your request."}, status=400
            )


@csrf_exempt
def like_post(request):
    if request.method != "POST":
        return JsonResponse({"error": "POST request required."}, status=304)
    data = json.loads(request.body)
    user = User.objects.get(id=data["user"])
    post = Post.objects.get(id=data["post_id"])

    if post.likes.filter(id=user.id).exists():
        user.likes.remove(post)
        metadata = post.serialize()
        return JsonResponse(
            {
                "Message": "Removing like was successful",
                "type": "dislike",
                "metadata": metadata,
            }
        )
    else:
        user.likes.add(post)
        metadata = post.serialize()
        return JsonResponse(
            {
                "Message": "Adding like was successful",
                "type": "like",
                "metadata": metadata,
            }
        )


@csrf_exempt
def edit_post(request, post_id):
    if request.method != "POST":
        return JsonResponse({"error": "POST request required."}, status=400)

    post = Post.objects.get(id=post_id)
    if post.poster == request.user:
        data = json.loads(request.body)
        post.body = data["new_text"]
        post.save()
        return JsonResponse({"message": "POST request successful."}, status=201)
    else:
        return JsonResponse({"error": "POST request denied."}, status=403)


# This function gets the profile as API.
def get_profile(request, user_id):
    user = User.objects.get(id=user_id)
    return JsonResponse(user.get_profile(), status=201, safe=False)


@csrf_exempt
@login_required
def handle_follow(request):
    if request.method != "POST":
        return JsonResponse({"error": "POST request required."}, status=400)

    data = json.loads(request.body)
    if data["action"] == "unfollow":
        FollowingUser.objects.get(
            user_id=data["user_on_page"], following_user_id=data["target_profile"]
        ).delete()
    elif data["action"] == "follow":
        user_on_page = User(id=data["user_on_page"])
        target_profile = User(id=data["target_profile"])
        action = FollowingUser(user_id=user_on_page, following_user_id=target_profile)
        action.save()
    else:
        return JsonResponse(
            {"error": "Something went wrong with request required."}, status=400
        )

    return JsonResponse(
        {
            "message": f"{data['action']} went successfully.",
            "action": f"{data['action'].title()}",
        },
        status=201,
    )


# All the functions below came with the code.
def index(request):
    return render(request, "network/index.html")


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
                "network/login.html",
                {"message": "Invalid username and/or password."},
            )
    else:
        return render(request, "network/login.html")


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
                request, "network/register.html", {"message": "Passwords must match."}
            )

        # Attempt to create new user
        try:
            user = User.objects.create_user(username, email, password)
            user.save()
        except IntegrityError:
            return render(
                request, "network/register.html", {"message": "Username already taken."}
            )
        login(request, user)
        return HttpResponseRedirect(reverse("index"))
    else:
        return render(request, "network/register.html")


@csrf_exempt
@login_required
def post(request):
    # Composing a new email must be via POST
    if request.method != "POST":
        return JsonResponse({"error": "POST request required."}, status=400)

    # Check recipient emails
    data = json.loads(request.body)
    post = Post(poster=request.user, body=data["body"])
    post.save()

    return JsonResponse({"message": "Post sent successfully."}, status=201)
