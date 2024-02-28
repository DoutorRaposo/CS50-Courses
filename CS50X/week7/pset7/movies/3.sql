-- List of movies released in 2018 and after in alphabetical order.
SELECT
    title
FROM
    movies
WHERE
    year >= 2018
ORDER BY
    title;