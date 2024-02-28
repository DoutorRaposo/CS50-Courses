-- This version is more confusing

SELECT
    "districts"."name",
    sub_query."per_pupil_expenditure",
    sub_query."exemplary"
FROM
    "districts"
    JOIN (
        SELECT
            "expenditures"."district_id",
            "expenditures"."per_pupil_expenditure",
            above_avg_exemplary."exemplary"
        FROM
            "expenditures"
            JOIN (
                SELECT
                    "exemplary",
                    "district_id"
                FROM
                    "staff_evaluations"
                WHERE
                    "exemplary" > (
                        SELECT
                            AVG("exemplary")
                        FROM
                            "staff_evaluations"
                    )
            ) AS above_avg_exemplary ON above_avg_exemplary."district_id" = "expenditures"."district_id"
        WHERE
            "expenditures"."per_pupil_expenditure" > (
                SELECT
                    AVG("per_pupil_expenditure")
                FROM
                    "expenditures"
            )
    ) AS sub_query ON "districts"."id" = sub_query."district_id"
WHERE
    "type" = 'Public School District'
ORDER BY
    sub_query."exemplary" DESC,
    sub_query."per_pupil_expenditure" DESC;