/*
 In available.sql, write a SQL statement to create a view named available. This view should contain all dates that are available at all listings. Ensure the view contains the following columns:
 
 id, which is the id of the listing from the listings table.
 property_type, from the listings table.
 host_name, from the listings table.
 date, from the availabilities table, which is the date of the availability.
 
 */
CREATE VIEW "available" AS
SELECT
    "listings"."id",
    "listings"."property_type",
    "listings"."host_name",
    "availabilities"."date"
FROM
    "listings"
    JOIN "availabilities" ON "listings"."id" = "availabilities"."listing_id"
WHERE
    "availabilities"."available" = 'TRUE';