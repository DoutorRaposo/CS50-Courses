from django.shortcuts import render, redirect
from django import forms
import random
from . import util

import markdown2


class NewPage(forms.Form):
    title = forms.CharField(label="Title")
    text = forms.CharField(widget=forms.Textarea, label="Text")


class EditPage(forms.Form):
    text = forms.CharField(widget=forms.Textarea, label="Text")
    title = forms.CharField(widget=forms.HiddenInput(), label="Title")


def index(request):
    return render(request, "encyclopedia/index.html", {"entries": util.list_entries()})


def entry(request, title):
    if mk := util.get_entry(title):
        html = markdown2.markdown(mk)
        return render(
            request,
            "encyclopedia/entry.html",
            {"html": html, "title_page": title.title()},
        )
    else:
        return render(
            request,
            "encyclopedia/error.html",
            {"title_page": title.capitalize(), "error_code": "404"},
        )


def search(request):
    query = request.GET["q"]
    list_entries = util.list_entries()
    list_results = []
    for document in list_entries:
        if query.casefold() == document.casefold():
            return redirect("title_page", query)
        if query.casefold() in document.casefold():
            list_results.append(document)
    return render(
        request, "encyclopedia/results.html", {"results": list_results, "query": query}
    )


def new_page(request):
    if request.method == "GET":
        return render(request, "encyclopedia/new_page.html", {"form": NewPage()})
    if request.method == "POST":
        title = request.POST["title"]
        text = request.POST["text"]
        list_entries = util.list_entries()
        if title in list_entries:
            return render(
                request,
                "encyclopedia/error.html",
                {"error_code": "418"},
            )
        else:
            util.save_entry(title, text)
            return redirect("title_page", title)


def edit_page(request, title):
    if request.method == "GET":
        text = util.get_entry(title)
        form = EditPage(initial={"text": text, "title": title})
        return render(
            request, "encyclopedia/edit_page.html", {"form": form, "title": title}
        )
    if request.method == "POST":
        title = request.POST["title"]
        text = request.POST["text"]
        util.save_entry(title, text)
        return redirect("title_page", title)


def random_page(request):
    return redirect("title_page", random.choice(util.list_entries()))
