-- Demonstrates schema of mfa.db for insert files
-- Creates mfa.db

-- Deletes prior tables if they exist
DROP TABLE IF EXISTS "collections";
DROP TABLE IF EXISTS "artists";
DROP TABLE IF EXISTS "created";

-- Creates collections table
CREATE TABLE IF NOT EXISTS "collections" (
    "id" INTEGER,
    "title" TEXT NOT NULL,
    "accession_number" TEXT NOT NULL UNIQUE,
    "acquired" NUMERIC,
    PRIMARY KEY("id")
);
