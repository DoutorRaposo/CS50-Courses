SELECT
    COUNT(*)
FROM
    "players"
WHERE
    (
        "bats" = 'R'
        AND "throws" = 'L'
    )
    OR (
        "throws" = 'R'
        AND "bats" = 'L'
    );