CREATE TABLE "users" (
    "id" INTEGER,
    "first_name" TEXT NOT NULL,
    "last_name" TEXT NOT NULL,
    PRIMARY KEY("id")
);

CREATE TABLE "institutions" (
    "id" INTEGER,
    "institution_name" TEXT NOT NULL,
    "type" TEXT NOT NULL,
    "location" TEXT NOT NULL,
    "foundation_year" INTEGER,
    PRIMARY KEY("id")
);

CREATE TABLE "companies" (
    "id" INTEGER,
    "company_name" TEXT NOT NULL,
    "company_area" TEXT NOT NULL,
    "company_location" TEXT NOT NULL,
    PRIMARY KEY("id")
);

CREATE TABLE "people_connections" (
    "id" INTEGER,
    "user_id_A" INTEGER NOT NULL,
    "user_id_B" INTEGER NOT NULL,
    PRIMARY KEY("id"),
    FOREIGN KEY("user_id_A") REFERENCES "users"("id"),
    FOREIGN KEY("user_id_B") REFERENCES "users"("id")
);

CREATE TABLE "school_connections" (
    "id" INTEGER,
    "user_id" INTEGER NOT NULL,
    "start_affiliation" NUMERIC NOT NULL,
    "end_affiliation" NUMERIC,
    "degree" TEXT NOT NULL,
    PRIMARY KEY("id"),
    FOREIGN KEY("user_id") REFERENCES "users"("id")
);

CREATE TABLE "company_connections" (
    "id" INTEGER,
    "user_id" INTEGER NOT NULL,
    "start_affiliation" NUMERIC NOT NULL,
    "end_affiliation" NUMERIC,
    "title" TEXT NOT NULL,
    PRIMARY KEY("id"),
    FOREIGN KEY("user_id") REFERENCES "users"("id")
);