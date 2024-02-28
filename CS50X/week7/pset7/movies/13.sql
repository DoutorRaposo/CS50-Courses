-- All people who starred in a movie in which Kevin Bacon also starred
SELECT
    people.name
FROM
    movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON people.id = stars.person_id
    JOIN (
        SELECT
            movies.id AS kb_movies
        FROM
            movies
            JOIN stars ON movies.id = stars.movie_id
            JOIN people ON people.id = stars.person_id
        WHERE
            people.name = "Kevin Bacon"
            AND people.birth = "1958"
    ) ON movies.id = kb_movies WHERE people.name != "Kevin Bacon";