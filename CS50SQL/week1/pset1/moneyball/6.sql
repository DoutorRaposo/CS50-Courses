SELECT
    "teams"."name",
    "thitsbyteam"."total hits"
FROM
    "teams"
    JOIN (
        SELECT
            team_id,
            SUM("H") AS "total hits"
        FROM
            "performances"
        WHERE
            "year" = 2001
        GROUP BY
            "team_id"
    ) AS "thitsbyteam" ON thitsbyteam."team_id" = "teams"."id"
ORDER BY
    thitsbyteam."total hits" DESC
LIMIT
    5;