SELECT
    "players"."first_name",
    "players"."last_name",
    "salaries"."salary",
    "performances"."year",
    "salaries"."year",
    "performances"."HR"
FROM
    "players"
    JOIN "salaries" ON "salaries"."player_id" = "players"."id"
    JOIN "performances" ON "performances"."player_id" = "players"."id" AND "performances"."year" = "salaries"."year"
ORDER BY
    "players"."id",
    "performances"."year" DESC,
    "performances"."HR" DESC,
    "salaries"."salary" DESC;