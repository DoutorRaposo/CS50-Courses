SELECT
    "first_name",
    "last_name",
    "debut",
    "birth_country" AS "Country"
FROM
    "players"
WHERE
    "birth_country" = 'Brazil'
ORDER BY
    "birth_year";