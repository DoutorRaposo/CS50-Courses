/*
 For any two users, the app needs to quickly show a list of the friends they have in common. Given two usernames, lovelytrust487 and exceptionalinspiration482, find the user IDs of their mutual friends. A mutual friend is a user that both lovelytrust487 and exceptionalinspiration482 count among their friends.
 
 Ensure your query uses the index automatically created on primary key columns of the friends table. This index is called sqlite_autoindex_friends_1
 */
WITH "lt_friends" AS (
    SELECT
        "friend_id"
    FROM
        "friends"
        JOIN "users" ON "users"."id" = "friends"."user_id"
    WHERE
        "users"."username" = 'lovelytrust487'
),
"ei_friends" AS (
    SELECT
        "friend_id"
    FROM
        "friends"
        JOIN "users" ON "users"."id" = "friends"."user_id"
    WHERE
        "users"."username" = 'exceptionalinspiration482'
)
SELECT
    "ei_friends"."friend_id"
FROM
    "ei_friends"
    JOIN "lt_friends"
WHERE
    "ei_friends"."friend_id" = "lt_friends"."friend_id";