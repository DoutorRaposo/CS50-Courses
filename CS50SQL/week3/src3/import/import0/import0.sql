-- Demonstrates importing a CSV into an existing table
-- Creates mfa.db

-- Deletes prior tables if they exist
DROP TABLE IF EXISTS "collections";
-- ** And for some reason the author of this files DROPS the table that it will be imported to
DROP TABLE IF EXISTS "artists";
DROP TABLE IF EXISTS "created";

-- Imports into an existing table by specifying mode and skipping header columns
.import --csv --skip 1 mfa.csv collections
-- **This skip should only be used if header is already created