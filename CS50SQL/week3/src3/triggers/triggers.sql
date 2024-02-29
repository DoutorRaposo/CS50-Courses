-- Demonstrates triggers on delete and insert
-- Uses mfa.db

-- Creates a table to track buying and selling of items from collections
CREATE TABLE "transactions" (
    "id" INTEGER,
    "title" TEXT,
    "action" TEXT,
    PRIMARY KEY("id")
);

-- Creates a trigger to log selling items from collections
CREATE TRIGGER "sell" 
BEFORE DELETE ON "collections"
FOR EACH ROW
BEGIN
    INSERT INTO "transactions" ("title", "action")
    VALUES (OLD."title", 'sold');
END;

-- Lists existing triggers
.schema

-- Deletes from collections
DELETE FROM "collections" WHERE "title" = 'Profusion of flowers';

-- Creates a trigger to log buying items
CREATE TRIGGER "buy" 
AFTER INSERT ON "collections"
FOR EACH ROW
BEGIN
    INSERT INTO "transactions" ("title", "action")
    VALUES (NEW."title", 'bought');
END;

-- Adds item to collections
INSERT INTO "collections" ("title", "accession_number", "acquired")
VALUES ('Profusion of flowers', '56.257', '1956-04-12');
