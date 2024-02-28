SELECT "type" FROM "addresses" WHERE id =
(SELECT
    "address_id"
FROM
    "scans"
WHERE
    "package_id" = (
        SELECT
            "id"
        FROM
            "packages"
        WHERE
            "from_address_id" IS NULL
    )
    AND "action" = 'Drop');