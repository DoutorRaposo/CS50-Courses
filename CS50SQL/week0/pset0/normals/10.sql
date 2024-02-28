SELECT
    COUNT(DISTINCT("latitude"))
FROM
    "normals"
WHERE
    "latitude" NOT NULL;