-- List of movies starred both by Bradley Cooper and Jennifer Lawrence
SELECT
    bc_titles AS titles
FROM
    (
        SELECT
            movies.title AS bc_titles,
            people.name
        FROM
            movies
            JOIN stars ON stars.movie_id = movies.id
            JOIN people ON people.id = stars.person_id
        WHERE
            people.name = "Bradley Cooper"
    )
    INNER JOIN (
        SELECT
            movies.title AS jl_titles,
            people.name
        FROM
            movies
            JOIN stars ON stars.movie_id = movies.id
            JOIN people ON people.id = stars.person_id
        WHERE
            people.name = "Jennifer Lawrence"
    ) ON bc_titles = jl_titles;