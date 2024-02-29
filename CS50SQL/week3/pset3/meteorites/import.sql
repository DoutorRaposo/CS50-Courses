-- Cleaning up house if messing with DB before
DROP TABLE IF EXISTS "meteorites";

DROP TABLE IF EXISTS "temp";

-- Creates temporary table
CREATE TABLE IF NOT EXISTS "temp" (
    "name" TEXT,
    "id" INTEGER,
    "nametype" TEXT,
    "class" TEXT,
    "mass" REAL,
    "discovery" TEXT,
    "year" INTEGER,
    "lat" REAL,
    "long" REAL,
    PRIMARY KEY("id")
);

-- Imports the CSV skipping the headers to match datatypes
.import --csv --skip 1 meteorites.csv temp
-- Cleaning up the empty strings to NULL
UPDATE
    temp
SET
    "mass" = NULL
WHERE
    "mass" = '';

UPDATE
    temp
SET
    "year" = NULL
WHERE
    "year" = '';

UPDATE
    temp
SET
    "lat" = NULL
WHERE
    "lat" = '';

UPDATE
    temp
SET
    "long" = NULL
WHERE
    "long" = '';

-- Two decimals on values
UPDATE
    temp
SET
    "mass" = ROUND("mass", 2),
    "long" = ROUND("long", 2),
    "lat" = ROUND("lat", 2);

-- Creates final table
CREATE TABLE IF NOT EXISTS "meteorites" (
    "id" INTEGER,
    "name" TEXT,
    "class" TEXT,
    "mass" REAL,
    "discovery" TEXT,
    "year" INTEGER,
    "lat" REAL,
    "long" REAL,
    PRIMARY KEY("id")
);

-- Inserts data from the temp table ordered by year, then name excluding "Relict" nametype.
INSERT INTO
    "meteorites" (
        "name",
        "class",
        "mass",
        "discovery",
        "lat",
        "long"
    )
SELECT
    "name",
    "class",
    "mass",
    "discovery",
    "lat",
    "long"
FROM
    temp
WHERE
    "nametype" != "Relict"
ORDER BY
    "year",
    "name";

DROP TABLE IF EXISTS "temp";