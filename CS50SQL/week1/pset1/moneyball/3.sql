SELECT
    "performances"."year",
    "performances"."HR"
FROM
    "players"
    JOIN "performances" ON "players"."id" = "performances"."player_id"
WHERE
    "players"."first_name" = 'Ken'
    AND "players"."last_name" = 'Griffey'
    AND "players"."birth_year" = 1969
ORDER BY
    "performances"."year" DESC;