SELECT
    strftime('%Y', air_date) AS year,
    strftime("%m-%d", MIN(air_date)) AS earliest_release_date
FROM
    "episodes"
GROUP BY
    strftime('%Y', air_date);