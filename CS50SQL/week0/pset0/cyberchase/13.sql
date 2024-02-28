SELECT
    "title"
FROM
    "episodes"
WHERE
    "season" >= 3
    AND "topic" LIKE "%data%";