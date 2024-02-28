SELECT
    "latitude",
    "longitude",
    "50m" AS "temperature"
FROM
    "normals"
WHERE
    (
        "latitude" <= 20
        AND "longitude" >= 55
    )
    AND (
        "latitude" <= 20
        AND "longitude" <= 75
    )
    AND (
        "latitude" >= 0
        AND "longitude" >= 55
    )
    AND (
        "latitude" >= 0
        AND "longitude" <= 75
    );