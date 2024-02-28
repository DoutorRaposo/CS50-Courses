from keys.API_Keys import api_token
import requests
from collections import OrderedDict

headers = {"accept": "application/json", "Authorization": "Bearer " + api_token}


# Search for artist and returns a dict with all search results.
def query_artists(name):
    search_url = (
        "https://api.themoviedb.org/3/search/person?query="
        + name.replace(" ", "%20")
        + "&include_adult=false&language=en-US&page=1"
    )
    response = requests.get(search_url, headers=headers)

    return response.json()


# This function have the input of the ID of the subject and returns a relevant information, with the movie credits appended.
def get_details(id):
    details_url = (
        "https://api.themoviedb.org/3/person/"
        + id
        + "?append_to_response=movie_credits"
    )
    response = requests.get(details_url, headers=headers)
    return response.json()


# Gets all filmography of a subject and returns a dict that each key represents a job. This function takes a dict that is a result of the "details" function.
def get_filmography(filmography_json):
    filmography = {}
    for key in filmography_json:
        for movies in filmography_json[key]:
            try:
                if movies["job"] not in filmography:
                    filmography[movies["job"]] = []
                filmography[movies["job"]].append(movies)
            except KeyError:
                continue
    filmography["cast"] = filmography_json["cast"]
    list_roles = list(filmography.keys())
    ordered_list = sorted(list_roles, key=str.casefold)
    ordered_filmography = {k: filmography[k] for k in ordered_list}
    return ordered_filmography


# This function filters the filmography for the selected jobs and also changes the links of the posters so movies without posters can have a default image.
def filter_filmography(filmography, roles_list):
    filtered_filmography = {}
    for index in range(len(roles_list)):
        roles_list[index] = roles_list[index].lower()
    for role in filmography:
        if role.lower() in roles_list:
            filtered_filmography[role.lower()] = filmography[role]
    # This part is for adding a poster_path in case there is none.
    for key in filtered_filmography:
        for index, dkey in enumerate(filtered_filmography[key]):
            if dkey["poster_path"] == None:
                filtered_filmography[key][index][
                    "poster_path"
                ] = "https://www.themoviedb.org/assets/2/v4/glyphicons/basic/glyphicons-basic-38-picture-grey-c2ebdbb057f2a7614185931650f8cee23fa137b93812ccb132b9df511df1cfac.svg"
            else:
                filtered_filmography[key][index]["poster_path"] = (
                    "https://www.themoviedb.org/t/p/w600_and_h900_bestv2"
                    + filtered_filmography[key][index]["poster_path"]
                )
    return filtered_filmography

# This function gets movie details and movie credits just so we can have pages for them also. 
def get_movie_details(id):
    details_movie_url = (
        "https://api.themoviedb.org/3/movie/" + id + "?append_to_response=credits"
    )
    response = requests.get(details_movie_url, headers=headers)
    return response.json()
