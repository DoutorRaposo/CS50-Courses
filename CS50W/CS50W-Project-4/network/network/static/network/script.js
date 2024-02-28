document.addEventListener('DOMContentLoaded', function () {
    // First load comes with the post field.
    if (document.querySelector('#compose-body')) {
        compose_post();
    }
    // Handlers for each of the top buttons.
    if (document.querySelector('#following-page')) {
        document.querySelector('#following-page').addEventListener('click', handleFollowerFilter())
    }
    if (document.querySelector("#user_page")) {
        document.querySelector("#user_page").addEventListener('click', profileHandler(JSON.parse(document.getElementById('logged_user').textContent)))
    }
    // First load of posts.
    route_object = {
        "type": "all",
        "view": "all_posts-view",
        "page": 1
    }
    get_posts(route_object)
});

// This function receives a route_object that describes the GET parameters that the Django route uses.
function get_posts(route_object) {
    if (route_object.user_id == undefined) {
        fetch(`get_posts?type=${route_object.type}&page=${route_object.page}`)
            .then(response => response.json())
            .then(response => {
                generate_posts(response)

            })
    }
    else {
        fetch(`get_posts?type=${route_object.type}&page=${route_object.page}&user_id=${route_object.user_id}`)
            .then(response => response.json())
            .then(response => {
                generate_posts(response)

            })
    }
}
// Handles the likes by changing the color and updating total likes
function handleLikes(e) {
    user_on_page = JSON.parse(document.getElementById('logged_user').textContent)
    if (user_on_page)
    {
        post_id = e.target.parentElement.parentElement.querySelector('.body-post').id
        fetch('like_post',
            {
                method: 'POST',
                body: JSON.stringify({ "post_id": post_id, "user": user_on_page })
            }
        )
        .then(response => response.json())
        .then(response => {
            if (response.type === "like") {
                e.target.parentElement.children[0].style.color = "red"
                e.target.parentElement.children[1].innerHTML = response.metadata.total_likes
            }
            else {
                e.target.parentElement.children[0].style.color = "black"
                e.target.parentElement.children[1].innerHTML = response.metadata.total_likes
            }
        })
    }
    else {
        alert("You must be logged in to like a post!")
    }

}

// This function is the post constructor with the pagination used in a "metadata"
function generate_posts(response) {
    posts = response.posts
    view = response.metadata.view
    metadata = response.metadata

    const new_view = document.createElement('div')
    new_view.className = view
    document.querySelector(".body").append(new_view)

    posts.forEach(post => {
        user_on_page = JSON.parse(document.getElementById('logged_user').textContent);

        const mainDiv = document.createElement('div');
        mainDiv.className = "single-post"

        const poster = document.createElement('span');
        poster.className = "poster-post"
        poster.innerHTML = post.sender
        poster.dataset.poster = post.sender_id

        mainDiv.append(poster)

        if (post.sender_id === user_on_page) {
            const editButton = document.createElement('button')
            editButton.className = "edit-btn"
            editButton.innerHTML = "Edit"
            editButton.dataset.id = post.id
            mainDiv.append(editButton)
            editButton.addEventListener('click', (editEvent) => editHandler(editEvent))
        }

        const body = document.createElement('span');
        body.className = "body-post"
        body.innerHTML = post.body
        body.id = post.id

        const timestamp = document.createElement('span');
        timestamp.className = "timestamp-post"
        timestamp.innerHTML = post.timestamp

        const likes = document.createElement('span');
        likes.className = "likes-post"
        likes.innerHTML = post.total_likes

        const div_like_button = document.createElement('div');
        div_like_button.className = "h_container"
        div_like_button.innerHTML = `<i id="heart" name="post-${post.id}" class="far fa-heart"></i>`
        div_like_button.append(likes)
        div_like_button.addEventListener('click', (e) => handleLikes(e))
        if (post.likes.includes(user_on_page))
        {
            div_like_button.querySelector("i").style.color = 'red'
        }

        mainDiv.append(body, timestamp, div_like_button)

        document.querySelector(`.${view}`).append(mainDiv);
    }
    );
    document.querySelectorAll('.poster-post').forEach(post => {
        post.addEventListener('click', profileHandler(post.dataset.poster))
    })
    if (metadata.total_pages > 1) {
        const nav = document.createElement('nav')
        nav.ariaLabel = "Page navigation example"
        nav.className = "navigation"

        const ul = document.createElement('ul')
        ul.className = "pagination"

        if (1 < metadata.page) {
            const left_arrow = document.createElement('li')
            left_arrow.className = "page-item"
            const left_anchor = document.createElement('a')
            left_anchor.className = "page-link"
            left_anchor.id = "prev-btn"
            left_anchor.ariaLabel = "Previous"
            const left_span = document.createElement('span')
            left_span.ariaHidden = "true"
            left_span.innerHTML = "&laquo;"

            left_anchor.append(left_span)
            left_arrow.append(left_anchor)
            ul.append(left_arrow)
        }

        for (let i = 0; i < metadata.total_pages; i++) {
            const li = document.createElement('li')
            li.className = "page-item"
            const anchor = document.createElement('a')
            anchor.className = "page-link numbered"
            anchor.id = i + 1
            anchor.innerHTML = i + 1
            if (metadata.page === i + 1) {
                anchor.style.backgroundColor = "#007bff"
                anchor.style.color = "white"
            }
            li.append(anchor)
            ul.append(li)
        }
        if (metadata.total_pages > metadata.page) {
            const right_arrow = document.createElement('li')
            right_arrow.className = "page-item"
            const right_anchor = document.createElement('a')
            right_anchor.className = "page-link"
            right_anchor.id = "next-btn"
            right_anchor.ariaLabel = "Next"
            const right_span = document.createElement('span')
            right_span.ariaHidden = "true"
            right_span.innerHTML = "&raquo;"

            right_anchor.append(right_span)
            right_arrow.append(right_anchor)
            ul.append(right_arrow)
        }


        nav.append(ul)

        document.querySelector(`.${view}`).append(nav);

        if (1 < metadata.page) {
            document.querySelector("#prev-btn").addEventListener("click", () => {
                previous_page = metadata.page - 1;
                document.querySelector(`.${view}`).remove();
                route_object = {
                    "type": metadata.type,
                    "view": view,
                    "page": previous_page,
                    "user_id": metadata.user_id
                };
                get_posts(route_object);

            })
        }

        if (metadata.total_pages > metadata.page) {
            document.querySelector("#next-btn").addEventListener("click", () => {
                next_page = metadata.page + 1;
                document.querySelector(`.${view}`).remove();
                route_object = {
                    "type": metadata.type,
                    "view": view,
                    "page": next_page,
                    "user_id": metadata.user_id
                };
                get_posts(route_object);

            })
        }

        if (metadata.total_pages > 1) {
            document.querySelectorAll(".page-link.numbered").forEach(link => {
                link.addEventListener("click", () => {
                    document.querySelector(`.${view}`).remove();
                    route_object = {
                        "type": metadata.type,
                        "view": view,
                        "page": link.id,
                        "user_id": metadata.user_id
                    };
                    get_posts(route_object);
    
                })
            })            
        }
    }
}

// This is the logic behind the edit button.
function editHandler(editEvent) {
    const post_id = editEvent.target.dataset.id;
    const post = editEvent.target.closest(".single-post");
    let body = post.querySelector('.body-post')
    const text = body.innerHTML;
    editEvent.target.style.display = 'none'
    const textarea = document.createElement('textarea')
    textarea.innerHTML = text
    textarea.className = "form-control"
    textarea.id = "edit-body"
    const confirm_edit = document.createElement('input')
    confirm_edit.type = "submit"
    confirm_edit.id = "edit-btn"
    confirm_edit.className = "btn btn-primary"
    const form_div = document.createElement('div')
    form_div.className = "edit-div"
    form_div.append(textarea, confirm_edit)
    body.replaceWith(form_div)

    confirm_edit.addEventListener('click', (e) => {
        text_value = e.target.parentElement.children[0].value
        if (text_value != ''){
            object = {
                "new_text": text_value
            }
            fetch(`edit_post/${post_id}`,
                {
                    method: 'POST',
                    body: JSON.stringify(object)
                }
            ).then(
                () => {
                    editEvent.target.style.display = 'block'
                    body.innerHTML = text_value;
                    form_div.replaceWith(body);
                }
            )
        }
        else {
            alert("Please type something to edit!")
        }

    })


}

// This function creates a header for a user profile and the posts below.
function profileHandler(user_id) {
    return () => {
        fetch(`/profile/user_id-${user_id}`)
            .then(response => response.json())
            .then(profile => {
                clearViews();

                const profileHeader = createProfileHeader(profile);

                document.querySelector(".body").append(profileHeader);
                route_object = {
                    "type": "profile",
                    "view": "profile-view",
                    "user_id": profile.user_id,
                    "page": 1
                }

                get_posts(route_object)
            });
    };
}

function createProfileHeader(profile) {
    const profileHeader = document.createElement('div');
    profileHeader.className = "profile-header";

    const profileName = document.createElement('span');
    profileName.className = "profile-name";
    profileName.innerHTML = `${profile.username}'s profile`;

    const profileFollowers = document.createElement('span');
    profileFollowers.className = "profile-followers";
    profileFollowers.innerHTML = `Followers: ${profile.total_followers}`;


    const profileFollowing = document.createElement('span');
    profileFollowing.className = "profile-following";
    profileFollowing.innerHTML = `Following: ${profile.total_following}`;
    profileHeader.append(profileName, profileFollowers, profileFollowing);

    user_on_page = JSON.parse(document.getElementById('logged_user').textContent);
    if (user_on_page != null & user_on_page != profile.user_id) {
        const followButton = document.createElement('button');
        followButton.id = "f-button";
        if (check_follow(user_on_page, profile)) {
            followButton.innerHTML = "Unfollow";
            followButton.className = "Unfollow-button";
        }
        else {
            followButton.innerHTML = "Follow";
            followButton.className = "Follow-button";
        }
        profileHeader.append(followButton);
        followButton.addEventListener('click', () => {
            handleFollow(profile);
        });
    }
    return profileHeader;
}

function clearViews() {
    if (document.querySelector('.compose-view')) {
        document.querySelectorAll('.compose-view').forEach(view => clearSingleView(view));
    };

    if (document.querySelector('.profile-header')) {
        document.querySelectorAll('.profile-header').forEach(view => clearSingleView(view));
    };

    if (document.querySelector('.following-view')) {
        document.querySelectorAll('.following-view').forEach(view => clearSingleView(view));
    };

    if (document.querySelector('.profile-view')) {
        document.querySelectorAll('.profile-view').forEach(view => clearSingleView(view));
    };

    if (document.querySelector('.all_posts-view')) {
        document.querySelectorAll('.all_posts-view').forEach(view => clearSingleView(view));
    };
}

function clearSingleView(view) {
    view.remove();
}

// This function handles the follow function and changes the button dynamically
function handleFollow(profile) {
    button = document.querySelector("#f-button");
    object = {
        "action": button.innerHTML.toLowerCase(),
        "user_on_page": user_on_page,
        "target_profile": profile.user_id
    };
    fetch('/handle_follow', {
        method: 'POST',
        body: JSON.stringify(object)
    })
        .then((response) => response.json())
        .then((response) => {
            if (response.action === "Unfollow") {
                button.innerHTML = "Follow"
                button.className = "Follow-button"
            }
            else if (response.action === "Follow") {
                button.innerHTML = "Unfollow"
                button.className = "Unfollow-button"
            }

        });
}

// This function is a helper for the function above.
function check_follow(user_on_page, profile) {
    for (let i = 0; i < profile.followers.length; i++) {
        if (user_on_page === profile.followers[i]["user_id"]) {
            return true
        }
    }
    return false
}

// This function generates the view for only those who the user is following.
function handleFollowerFilter() {
    return async () => {
        clearViews();
        user_on_page = JSON.parse(document.getElementById('logged_user').textContent);
        route_object = {
            "type": "following",
            "view": "following-view",
            "user_id": user_on_page,
            "page": 1
        }
        get_posts(route_object)
    };
}

// This function generates the text field for a new post.
function compose_post() {

    composeBody = document.querySelector('#compose-body')
    composeBody.value = '';

    document.querySelector('#compose-btn').onclick = () => {
        if (composeBody.value != '')
        {
            post = {
                body: composeBody.value
            }
            fetch('/post', {
                method: 'POST',
                body: JSON.stringify(post)
            })
                .then(response => response.json())
                .then(result => {
                    // Print error if it is returned.
                    if (result.error != undefined) {
                        alert(result.error)
                        return false
                    };
                }).then(() => {
                    composeBody.value = '';
                    document.querySelector(".all_posts-view").innerHTML = '';
                    route_object = {
                        "type": "all",
                        "view": "all_posts-view",
                        "page": 1
                    }
                    get_posts(route_object);
                }
                ); 
        }
        else {
            alert("Please type something to post!")
        }
        
        // Prevents default behavior of button.
        return false
    };
}
