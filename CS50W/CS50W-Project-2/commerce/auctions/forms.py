from .models import Bid, Listing, Comment
from django.forms import ModelForm
from django import forms

class BidForm(ModelForm):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.fields["value"].widget.attrs.update({"placeholder": "Bid", "class": "bid-field"})

    class Meta:
        model = Bid
        fields = ["value"]

class ListingForm(ModelForm):
    class Meta:
        model = Listing
        fields = ["name", "image", "description", "initial_bid", "category"]

class CommentForm(ModelForm):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.fields["body"].widget.attrs.update({"placeholder": "Type your comment here!", "class": "comment-field"})

    class Meta:
        model = Comment
        fields = ["body"]