/*
 At the end of the year, the app needs to send users a summary of their engagement. Find the username of the most popular user, defined as the user who has had the most messages sent to them. If two users have had the same number of messages sent to them, return the username that is first alphabetically.
 Ensure your query uses the search_messages_by_to_user_id index
 */
SELECT
    "users"."username"
FROM
    "users"
    JOIN "messages" ON "users"."id" = "messages"."to_user_id"
GROUP BY
    "to_user_id"
ORDER BY
    COUNT(*) DESC,
    "users"."username"
LIMIT
    1;