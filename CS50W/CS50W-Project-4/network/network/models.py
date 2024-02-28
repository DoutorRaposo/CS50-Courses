from django.contrib.auth.models import AbstractUser
from django.db import models


class User(AbstractUser):
    def get_profile(self):
        following = [
            {"user": x.following_user_id.username, "user_id": x.following_user_id.id}
            for x in self.following.all()
        ]
        followers = [
            {"user": x.user_id.username, "user_id": x.user_id.id}
            for x in self.followers.all()
        ]
        posts = [x.serialize() for x in self.posts.all()]
        profile = {
            "user_id": self.id,
            "username": self.username,
            "followers": followers,
            "total_followers": len(followers),
            "following": following,
            "total_following": len(following),
            "posts": posts,
            "likes": [user.id for user in self.likes.all()],
        }
        return profile


class Post(models.Model):
    poster = models.ForeignKey("User", on_delete=models.CASCADE, related_name="posts")
    body = models.TextField(blank=True)
    likes = models.ManyToManyField("User", related_name="likes", blank=True)
    timestamp = models.DateTimeField(auto_now_add=True)

    class Meta:
        ordering = ["-timestamp"]

    def serialize(self):
        likes_list = [user.id for user in self.likes.all()]
        return {
            "id": self.id,
            "sender": self.poster.username,
            "sender_id": self.poster.id,
            "likes": likes_list,
            "total_likes": len(likes_list),
            "body": self.body,
            "timestamp": self.timestamp.strftime("%b %d %Y, %I:%M %p"),
        }

    def __str__(self):
        return self.body


class FollowingUser(models.Model):
    user_id = models.ForeignKey(
        "User", related_name="following", on_delete=models.CASCADE
    )
    following_user_id = models.ForeignKey(
        "User", related_name="followers", on_delete=models.CASCADE
    )
    timestamp = models.DateTimeField(auto_now_add=True)

    class Meta:
        constraints = [
            models.UniqueConstraint(
                fields=["user_id", "following_user_id"], name="followers_unique"
            )
        ]

        ordering = ["-timestamp"]

    def __str__(self):
        return f"{self.user_id} follows {self.following_user_id}"

    def get_following(self):
        return self.following_user_id
