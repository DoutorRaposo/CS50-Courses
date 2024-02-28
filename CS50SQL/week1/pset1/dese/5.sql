SELECT
    "city",
    Count("name") AS "Number of Schools"
FROM
    "schools"
WHERE
    "type" != 'Charter School'
GROUP BY
    "city"
HAVING
    Count("name") <= 3
ORDER BY
    "Number of Schools" DESC,
    "city";