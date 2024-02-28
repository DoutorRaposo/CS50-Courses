-- All movies in 2010 and theirs ratings, in descending order by rating and alphabetically by title.
SELECT
    movies.title,
    ratings.rating
FROM
    movies
    JOIN ratings ON movies.id = ratings.movie_id
WHERE
    ratings.rating > 0
    AND movies.year = 2010
ORDER BY
    rating DESC,
    title;