SELECT
    best_rbi."first_name",
    best_rbi."last_name"
FROM
    (
        SELECT
            "players"."first_name",
            "players"."last_name",
            ("salaries"."salary" / "performances"."RBI") AS "Dollars per RBI"
        FROM
            "players"
            JOIN "salaries" ON "salaries"."player_id" = "players"."id"
            JOIN "performances" ON "performances"."player_id" = "players"."id"
        WHERE
            "Dollars per RBI" NOT NULL
            AND "performances"."year" = 2001
            AND "salaries"."year" = 2001
        ORDER BY
            "Dollars per RBI",
            "players"."first_name",
            "players"."last_name"
        LIMIT
            10
    ) AS best_rbi
INTERSECT
SELECT
    best_hits."first_name",
    best_hits."last_name"
FROM
    (
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
            AND "salaries"."year" = 2001
        ORDER BY
            "dollars per hit",
            "players"."first_name",
            "players"."last_name"
        LIMIT
            10
    ) AS best_hits
ORDER BY
    "last_name";