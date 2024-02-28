-- This version was complicated.

SELECT
    "districts"."name", "exp_list"."per_pupil_expenditure"
FROM
    "districts"
    JOIN (
        SELECT
            "district_id",
            "per_pupil_expenditure"
        FROM
            "expenditures"
    ) AS "exp_list" ON "districts"."id" = "exp_list"."district_id"
WHERE "type" = 'Public School District'
ORDER BY
    "exp_list"."per_pupil_expenditure" DESC
LIMIT
    10;