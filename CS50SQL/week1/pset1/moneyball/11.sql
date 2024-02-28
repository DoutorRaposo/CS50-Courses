SELECT
    "players"."first_name",
    "players"."last_name",
    ("salaries"."salary" / "performances"."H") AS "dollars per hit"
FROM
    "players"
    JOIN "salaries" ON "salaries"."player_id" = "players"."id"
    JOIN "performances" ON "performances"."player_id" = "players"."id"
WHERE
    "dollars per hit" NOT NULL
    AND "performances"."year" = 2001
    AND  "salaries"."year" = 2001
ORDER BY
    "dollars per hit",
    "players"."first_name",
    "players"."last_name"
LIMIT
    10;