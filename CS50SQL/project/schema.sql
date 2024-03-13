CREATE TABLE IF NOT EXISTS "title" (
    "id" INTEGER PRIMARY KEY,
    "title" TEXT NOT NULL,
    "overview" TEXT NOT NULL,
    "release_date" DATE,
    "poster_path" TEXT NOT NULL,
    "budget" DECIMAL(10, 2),
    "revenue" INTEGER,
    "runtime" INTEGER,
    "status" TEXT NOT NULL,
    "tagline" TEXT NOT NULL,
    "certification" TEXT NOT NULL
);

-- Creates genre and genre-title many-to-many relationship
CREATE TABLE IF NOT EXISTS "genre" (
    "id" INTEGER NOT NULL PRIMARY KEY,
    "name" TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS "title_genre" (
    "id" INTEGER NOT NULL PRIMARY KEY,
    "title_id" INTEGER NOT NULL REFERENCES "title" ("id"),
    "genre_id" INTEGER NOT NULL REFERENCES "genre" ("id")
);

-- Creates companies and companies-title many-to-many relationshop
CREATE TABLE IF NOT EXISTS "companies" (
    "id" INTEGER NOT NULL PRIMARY KEY,
    "name" TEXT NOT NULL,
    "creation" DATE
);

CREATE TABLE IF NOT EXISTS "title_companies" (
    "id" INTEGER NOT NULL PRIMARY KEY,
    "title_id" INTEGER NOT NULL REFERENCES "title" ("id"),
    "company_id" INTEGER NOT NULL REFERENCES "companies" ("id")
);

-- Creates persons and cast-title and crew-title many-to-many relationship

CREATE TABLE IF NOT EXISTS "person" (
    "id" INTEGER PRIMARY KEY,
    "name" TEXT NOT NULL,
    "birth" DATE NOT NULL,
    "death" DATE,
    "known_for" TEXT
);

CREATE TABLE IF NOT EXISTS "title_crew" (
    "id" INTEGER NOT NULL PRIMARY KEY,
    "title_id" INTEGER NOT NULL REFERENCES "title" ("id"),
    "crew_id" INTEGER NOT NULL REFERENCES "person" ("id")
);


CREATE TABLE IF NOT EXISTS "title_cast" (
    "id" INTEGER NOT NULL PRIMARY KEY,
    "title_id" INTEGER NOT NULL REFERENCES "title" ("id"),
    "crew_id" INTEGER NOT NULL REFERENCES "person" ("id")
);

-- Indexes on the "title" table
CREATE INDEX IF NOT EXISTS idx_title_title ON "title"("title");

CREATE INDEX IF NOT EXISTS idx_title_release_date ON "title"("release_date");

-- Indexes on the "genre" table
CREATE INDEX IF NOT EXISTS idx_genre_name ON "genre"("name");

-- Indexes on the "companies" table
CREATE INDEX IF NOT EXISTS idx_companies_name ON "companies"("name");

-- Indexes for many-to-many relationships
CREATE INDEX IF NOT EXISTS idx_title_genre_title_id ON "title_genre"("title_id");

CREATE INDEX IF NOT EXISTS idx_title_genre_genre_id ON "title_genre"("genre_id");

CREATE INDEX IF NOT EXISTS idx_title_companies_title_id ON "title_companies"("title_id");

CREATE INDEX IF NOT EXISTS idx_title_companies_company_id ON "title_companies"("company_id");

CREATE INDEX IF NOT EXISTS idx_title_crew_title_id ON "title_crew"("title_id");

CREATE INDEX IF NOT EXISTS idx_title_crew_crew_id ON "title_crew"("crew_id");

CREATE INDEX IF NOT EXISTS idx_title_cast_title_id ON "title_cast"("title_id");

CREATE INDEX IF NOT EXISTS idx_title_cast_crew_id ON "title_cast"("crew_id");

-- Indexes on commonly queried columns
CREATE INDEX IF NOT EXISTS idx_person_name ON "person"("name");


-- View for summaries
CREATE VIEW IF NOT EXISTS title_summary AS
SELECT
    title,
    overview,
    release_date,
    runtime
FROM
    title;

