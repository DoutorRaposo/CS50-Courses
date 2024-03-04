/*
 In frequently_reviewed.sql, write a SQL statement to create a view named frequently_reviewed. This view should contain the 100 most frequently reviewed listings, sorted from most- to least-frequently reviewed. Ensure the view contains the following columns:
 
 id, which is the id of the listing from the listings table.
 property_type, from the listings table.
 host_name, from the listings table.
 reviews, which is the number of reviews the listing has received.
 
 If any two listings have the same number of reviews, sort by property_type (in alphabetical order), followed by host_name (in alphabetical order).
 */
CREATE VIEW "frequently_reviewed" AS WITH "number_of_reviews" AS (
    SELECT
        "listing_id",
        COUNT(*) AS "reviews"
    FROM
        "reviews"
    GROUP BY
        "listing_id"
)
SELECT
    "listings"."id",
    "listings"."property_type",
    "listings"."host_name",
    "number_of_reviews"."reviews"
FROM
    "listings"
    JOIN "number_of_reviews" ON "listings"."id" = "number_of_reviews"."listing_id"
ORDER BY
    "number_of_reviews"."reviews" DESC,
    "listings"."property_type",
    "listings"."host_name"
LIMIT
    100;