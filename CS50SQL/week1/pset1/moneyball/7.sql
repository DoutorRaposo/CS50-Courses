SELECT
    "players"."first_name", "players"."last_name"
FROM
    "salaries"
JOIN
    "players"
    ON "players"."id" = "salaries"."player_id"
ORDER BY
    "salary" DESC
LIMIT
    1;