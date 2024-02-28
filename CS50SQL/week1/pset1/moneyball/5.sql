SELECT
    "name"
FROM
    "teams"
WHERE
    "id" IN (
        SELECT
            "team_id"
        FROM
            "performances"
            JOIN "players" ON "players"."id" = "performances"."player_id"
        WHERE
            "players"."first_name" = 'Satchel'
            AND "players"."last_name" = 'Paige'
        GROUP BY
            "team_id"
    );