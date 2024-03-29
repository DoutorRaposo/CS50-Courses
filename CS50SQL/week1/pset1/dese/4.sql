SELECT
    "city",
    Count("name") AS "Number of Schools"
FROM
    "schools"
WHERE
    "type" = 'Public School'
GROUP BY
    "city"
ORDER BY
    "Number of Schools" DESC, "schools"."city"
LIMIT
    10;