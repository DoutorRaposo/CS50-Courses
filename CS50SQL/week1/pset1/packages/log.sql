-- *** The Lost Letter ***
/*
 Clerk, my name’s Anneke. I live over at 900 Somerville Avenue. 
 Not long ago, I sent out a special letter. It’s meant for my friend Varsha. 
 She’s starting a new chapter of her life at 2 Finnegan Street, uptown. 
 (That address, let me tell you: it was a bit tricky to get right the first time.) 
 The letter is a congratulatory note—a cheery little paper hug from me to her, to celebrate this big move of hers. 
 Can you check if it’s made its way to her yet?
 */
-- First, I checked out the address, because I had a suspicion when she said "it was tricky to get right";
SELECT
    *
FROM
    "addresses"
WHERE
    "address" LIKE '%finnegan%';

-- Then, apparently the address was incorrect in the report. There is a chance that it is wrong in the package also.
SELECT
    *
FROM
    "addresses"
WHERE
    "address" LIKE '2 %finn%';

-- The address of Anneke
SELECT
    "id"
FROM
    "addresses"
WHERE
    "address" = '900 Somerville Avenue';

-- Four packages were picked-up at Anneke's
SELECT
    *
FROM
    "scans"
    JOIN "addresses" ON "address_id" = "addresses"."id"
WHERE
    "address_id" = (
        SELECT
            "id"
        FROM
            "addresses"
        WHERE
            "address" = '900 Somerville Avenue'
    );

-- Found the package in the addresses table
SELECT
    *
FROM
    "packages"
WHERE
    "id" IN (
        SELECT
            "package_id"
        FROM
            "scans"
            JOIN "addresses" ON "address_id" = "addresses"."id"
        WHERE
            "address_id" = (
                SELECT
                    "id"
                FROM
                    "addresses"
                WHERE
                    "address" = '900 Somerville Avenue'
            )
    )
    AND "packages"."contents" LIKE '%congratulatory%';

-- Confirmation that this is, indeed, the package, by visualizing also the addresses
SELECT
    "packages"."id",
    "packages"."contents",
    "fa"."address" AS "from_address",
    "ta"."address" as "to_address"
FROM
    "packages"
    JOIN "addresses" fa ON "packages"."from_address_id" = "fa"."id"
    JOIN "addresses" ta ON "packages"."to_address_id" = "ta"."id"
WHERE
    "packages"."id" IN (
        SELECT
            "package_id"
        FROM
            "scans"
            JOIN "addresses" ON "address_id" = "addresses"."id"
        WHERE
            "address_id" = (
                SELECT
                    "id"
                FROM
                    "addresses"
                WHERE
                    "address" = '900 Somerville Avenue'
            )
    )
    AND "packages"."contents" LIKE '%congratulatory%';

-- This query gives me pickup and drop situations.
SELECT
    *
FROM
    "scans"
WHERE
    "package_id" = (
        SELECT
            "packages"."id"
        FROM
            "packages"
        WHERE
            "id" IN (
                SELECT
                    "package_id"
                FROM
                    "scans"
                    JOIN "addresses" ON "address_id" = "addresses"."id"
                WHERE
                    "address_id" = (
                        SELECT
                            "id"
                        FROM
                            "addresses"
                        WHERE
                            "address" = '900 Somerville Avenue'
                    )
            )
            AND "packages"."contents" LIKE '%congratulatory%'
    );

-- Now, to find out if the package was delivered to the right address. And it was!
SELECT
    "address"
FROM
    "scans"
    JOIN "addresses" ON "addresses"."id" = "scans"."address_id"
WHERE
    "package_id" = (
        SELECT
            "packages"."id"
        FROM
            "packages"
        WHERE
            "id" IN (
                SELECT
                    "package_id"
                FROM
                    "scans"
                    JOIN "addresses" ON "address_id" = "addresses"."id"
                WHERE
                    "address_id" = (
                        SELECT
                            "id"
                        FROM
                            "addresses"
                        WHERE
                            "address" = '900 Somerville Avenue'
                    )
            )
            AND "packages"."contents" LIKE '%congratulatory%'
    )
    AND "scans"."action" = 'Drop';

-- *** The Devious Delivery ***
/*
 Good day to you, deliverer of the mail. 
 You might remember that not too long ago I made my way over from the town of Fiftyville. 
 I gave a certain box into your reliable hands and asked you to keep things low. 
 My associate has been expecting the package for a while now. 
 And yet, it appears to have grown wings and flown away. Ha! 
 Any chance you could help clarify this mystery? Afraid there’s no “From” address. 
 It’s the kind of parcel that would add a bit more… quack to someone’s bath times, if you catch my drift.
 */
-- The only package that has no "from address" is the Duck debugger
SELECT
    *
FROM
    "packages"
WHERE
    "from_address_id" IS NULL;

-- Apparently the package was picked up!
SELECT
    *
FROM
    "scans"
WHERE
    "package_id" = (
        SELECT
            "id"
        FROM
            "packages"
        WHERE
            "from_address_id" IS NULL
    )
    AND "action" = 'Pick';

-- Where was it dropped?
SELECT
    *
FROM
    "scans"
WHERE
    "package_id" = (
        SELECT
            "id"
        FROM
            "packages"
        WHERE
            "from_address_id" IS NULL
    )
    AND "action" = 'Drop';

-- The police got it!
SELECT
    "type"
FROM
    "addresses"
WHERE
    id = (
        SELECT
            "address_id"
        FROM
            "scans"
        WHERE
            "package_id" = (
                SELECT
                    "id"
                FROM
                    "packages"
                WHERE
                    "from_address_id" IS NULL
            )
            AND "action" = 'Drop'
    );

-- *** The Forgotten Gift ***
/*
 Oh, excuse me, Clerk. I had sent a mystery gift, you see, to my wonderful granddaughter, off at 728 Maple Place. 
 That was about two weeks ago. Now the delivery date has passed by seven whole days and I hear she still waits, her hands empty and heart filled with anticipation. 
 I’m a bit worried wondering where my package has gone. 
 I cannot for the life of me remember what’s inside, but I do know it’s filled to the brim with my love for her. 
 Can we possibly track it down so it can fill her day with joy? I did send it from my home at 109 Tileston Street.
 */
-- Found the package id
SELECT
    "package_id"
FROM
    "scans"
    JOIN "addresses" ON "address_id" = "addresses"."id"
WHERE
    "address_id" = (
        SELECT
            "id"
        FROM
            "addresses"
        WHERE
            "address" = '109 Tileston Street'
    )
    AND "action" = 'Pick';

-- This query confirms that the address is correct
SELECT
    "packages"."contents",
    fa."address" AS "From Address",
    ta."address" AS "To Address"
FROM
    "packages"
    JOIN "addresses" fa ON "fa"."id" = "packages"."from_address_id"
    JOIN "addresses" ta ON "ta"."id" = "packages"."to_address_id"
WHERE
    "packages"."id" = (
        SELECT
            "package_id"
        FROM
            "scans"
            JOIN "addresses" ON "address_id" = "addresses"."id"
        WHERE
            "address_id" = (
                SELECT
                    "id"
                FROM
                    "addresses"
                WHERE
                    "address" = '109 Tileston Street'
            )
            AND "action" = 'Pick'
    );

-- However, it appears that the package was picked up again
SELECT
    *
FROM
    "scans"
WHERE
    "package_id" = (
        SELECT
            "package_id"
        FROM
            "scans"
            JOIN "addresses" ON "address_id" = "addresses"."id"
        WHERE
            "address_id" = (
                SELECT
                    "id"
                FROM
                    "addresses"
                WHERE
                    "address" = '109 Tileston Street'
            )
            AND "action" = 'Pick'
    );

-- This query will see the ID who has the package
SELECT
    "driver_id"
FROM
    "scans"
WHERE
    "package_id" = (
        SELECT
            "package_id"
        FROM
            "scans"
            JOIN "addresses" ON "address_id" = "addresses"."id"
        WHERE
            "address_id" = (
                SELECT
                    "id"
                FROM
                    "addresses"
                WHERE
                    "address" = '109 Tileston Street'
            )
            AND "action" = 'Pick'
    )
ORDER BY
    "timestamp" DESC
LIMIT
    1;

-- Now, for the name
SELECT
    "name"
FROM
    "drivers"
WHERE
    "id" = (
        SELECT
            "driver_id"
        FROM
            "scans"
        WHERE
            "package_id" = (
                SELECT
                    "package_id"
                FROM
                    "scans"
                    JOIN "addresses" ON "address_id" = "addresses"."id"
                WHERE
                    "address_id" = (
                        SELECT
                            "id"
                        FROM
                            "addresses"
                        WHERE
                            "address" = '109 Tileston Street'
                    )
                    AND "action" = 'Pick'
            )
        ORDER BY
            "timestamp" DESC
        LIMIT
            1
    );

-- Mikel, you rascal!