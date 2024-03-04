/*
 14 	98 	4
 114 	3 	5
 618 	72 	9
 630 	7 	3
 932 	12 	5
 2230 	50 	7
 2346 	44 	10
 3041 	14 	5
 
 
 */
-- Testing: apparently it starts with 'Find me in...'
/*
 SELECT substr("sentence", 98, 4) FROM sentences WHERE id = 14;
 SELECT substr("sentence", 3, 5) FROM sentences WHERE id = 114;
 SELECT substr("sentence", 72, 9) FROM sentences WHERE id = 618;
 SELECT substr("sentence", 7, 3) FROM sentences WHERE id = 630;
 SELECT substr("sentence", 12, 5) FROM sentences WHERE id = 932;
 SELECT substr("sentence", 50, 7) FROM sentences WHERE id = 2230;
 SELECT substr("sentence", 44, 10) FROM sentences WHERE id = 2346;
 SELECT substr("sentence", 14, 5) FROM sentences WHERE id = 3041;
 
 */
-- Found all:
-- SELECT "sentence" FROM "sentences" WHERE id IN (14,114,618,630,932,2230,2346,3041);
DROP TABLE IF EXISTS "parameters";

DROP VIEW IF EXISTS "message";

CREATE TABLE IF NOT EXISTS "parameters" (
    "sentence_id" INTEGER,
    "position" INTEGER,
    "length" INTEGER
);

INSERT INTO
    "parameters"("sentence_id", "position", "length")
VALUES
    (14, 98, 4),
    (114, 3, 5),
    (618, 72, 9),
    (630, 7, 3),
    (932, 12, 5),
    (2230, 50, 7),
    (2346, 44, 10),
    (3041, 14, 5);

CREATE VIEW "message" AS
SELECT
    substr(
        "sentences"."sentence",
        "parameters"."position",
        "parameters"."length"
    ) as "phrase"
FROM
    "parameters"
    JOIN "sentences" ON "sentences"."id" = "parameters"."sentence_id";