-- This is a valid version without LIMIT 1, but we haven't learned this yet

SELECT
    "name"
FROM
    "districts"
    JOIN (
        SELECT
            "districts"."id" AS id,
            MIN("expenditures"."pupils") AS "pupils"
        FROM
            "districts"
            JOIN "expenditures" ON "districts"."id" = "expenditures"."district_id"
        ORDER BY
            "expenditures"."pupils"
    ) AS min_pupil ON "districts"."id" = min_pupil.id;