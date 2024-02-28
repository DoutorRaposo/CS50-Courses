from django.contrib.auth.models import AbstractUser
from django.db import models
from django.utils.text import slugify


class User(AbstractUser):
    pass

class Category(models.Model):
    category = models.CharField(max_length=64, null=True)

    def __str__(self):
        return f"{self.category}"

class Listing(models.Model):
    name = models.CharField(max_length=64)
    image = models.CharField("Image URL", max_length=512, null=True, blank=True)
    description = models.CharField(max_length=2048)
    vendor = models.ForeignKey(User, on_delete=models.CASCADE, related_name="listings")
    initial_bid = models.DecimalField(max_digits=10, decimal_places=2)
    active = models.BooleanField(default=True)
    category = models.ForeignKey(Category, on_delete=models.CASCADE, related_name="type", null=True, blank=True)
    current_bid = models.ForeignKey("Bid", on_delete=models.CASCADE, related_name="current_bid", null=True, blank=True)
    created_on = models.DateTimeField(auto_now_add=True)

    slug = models.SlugField(unique=True, null=True, blank=True)

    def save(self, *args, **kwargs):
        self.slug = slugify(self.name)
        super(Listing, self).save(*args, **kwargs)

    class Meta:
        ordering = ['created_on']

    def __str__(self):
        return f"{self.name}"
    
class Bid(models.Model):
    listing = models.ForeignKey(Listing, on_delete=models.CASCADE, related_name="bids")
    value = models.DecimalField("", max_digits=10, decimal_places=2)
    bidder = models.ForeignKey(User, on_delete=models.CASCADE, related_name="bidder")
    created_on = models.DateTimeField(auto_now_add=True)

    class Meta:
        ordering = ['created_on']

    def __str__(self):
        return f"{self.value} on {self.listing} by {self.bidder}"


class Watchlist(models.Model):
    listing = models.ManyToManyField(Listing, related_name="watchlist")
    user = models.ForeignKey(User, on_delete=models.CASCADE, related_name="watchlist")

    def __str__(self):
        return f"{self.user}'s watchlist"

class Comment(models.Model):
    listing = models.ForeignKey(Listing, on_delete=models.CASCADE, related_name="comments")
    created_on = models.DateTimeField(auto_now_add=True)
    body = models.TextField("")
    user = models.ForeignKey(User, on_delete=models.CASCADE, related_name="user")

    class Meta:
        ordering = ['created_on']

    def __str__(self):
        return f"{self.body}"

