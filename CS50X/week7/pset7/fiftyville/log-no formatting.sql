-- Keep a log of any SQL queries you execute as you solve the mystery.

.schema -- Overview of the database
SELECT * FROM crime_scene_reports; -- Just to get my bearings on what this table looks like.
SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street"; -- Just to see what happened on the street, not including the day;
SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street" AND day = 28 AND month = 7; -- Apparently, there was another crime, but no witness. Don't know yet if correlated. Three witnesses mention the bakery and were interviewed. Tge crime occurred 10h15am;
SELECT * FROM interviews; -- Unproductive, but just to get my bearings.
SELECT * FROM interviews WHERE day = 28 AND month = 7; -- Saw the interviews from this day and month. Not much interesting. Since the bakery apparently was mentioned all three times, the next will be more conclusive.
SELECT * FROM interviews WHERE transcript LIKE "%bakery%" AND day = 28 AND month = 7; -- Decided to limit to only the bakery.
SELECT name,transcript FROM interviews WHERE transcript LIKE "%bakery%" AND day = 28 AND month = 7; -- Just the transcripts with names, so we can take notes.

-- Ruth says the thief got into a car and drove away within10 minutes after the theft. Suggested looking at security footage from the bakery.
-- Eugene says he saw the thief in the morning in the ATM on Leggett Street withdrawing some money. The bakery is Emma's.
-- Raymond said that he called someone and talked less than a minute and planned to take the earliest flight out of fiftyville on the 29/07. The accomplice was asked to buy the ticket.

-- License_plate investigation:
 -- 9 cars exited the premises from 10h16 til 10h35. Most probably one of the the two that left 10h23, would match testimony. Further investigation required.
SELECT * FROM bakery_security_logs WHERE day = 28 AND month = 7 AND hour = 10 AND activity = "exit";
-- List of people who exited the premises at 10am.
SELECT people.name FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE bakery_security_logs.activity = "exit" AND bakery_security_logs.day = 28 AND bakery_security_logs.month = 7 AND bakery_security_logs.hour = 10;
-- This is a list of people that exited "within" ten minutes of the 10h15 incident.
SELECT people.name FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE bakery_security_logs.activity = "exit" AND bakery_security_logs.day = 28 AND bakery_security_logs.month = 7 AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute < 26 AND bakery_security_logs.minute > 14;


-- ATM investigation:
-- List of withdraws made that day on the ATM on Leggett Street.
SELECT * FROM atm_transactions WHERE atm_location = "Leggett Street" AND day = 28 AND month = 7 AND transaction_type = "withdraw";
-- List of bank accounts withdrawn that day.
SELECT * FROM bank_accounts JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE atm_transactions.atm_location = "Leggett Street" AND atm_transactions.day = 28 AND atm_transactions.transaction_type = "withdraw";
-- List of names that withdrew from the account on the 28th
SELECT people.name FROM bank_accounts JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number JOIN people ON people.id = bank_accounts.person_id WHERE atm_transactions.atm_location = "Leggett Street" AND atm_transactions.day = 28 AND atm_transactions.transaction_type = "withdraw";
-- OR important for later!!
SELECT people.name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE atm_transactions.atm_location = "Leggett Street" AND atm_transactions.day = 28 AND atm_transactions.transaction_type = "withdraw";

-- Phone investigation:
-- List of all phone calls that are less than 80 seconds long the 28th.
SELECT * FROM phone_calls WHERE phone_calls.day = 28 AND phone_calls.month = 7 AND phone_calls.duration < 80;
-- List of name of all callers on the 28th that made calls that lasted less than 61 seconds.
SELECT people.name FROM people JOIN phone_calls ON phone_calls.caller = people.phone_number WHERE phone_calls.day = 28 AND phone_calls.month = 7 AND phone_calls.duration < 61;
-- List of name of all receivers.
SELECT people.name FROM people JOIN phone_calls ON phone_calls.receiver = people.phone_number WHERE phone_calls.day = 28 AND phone_calls.month = 7 AND phone_calls.duration < 61;

-- Airport investigation:
-- Id for Fiftyville's airport.
SELECT id FROM airports WHERE city = "Fiftyville";
-- Earliest flight leaving Fiftyville's airport on the 29th.
SELECT * FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND flights.day = 29 ORDER BY flights.hour LIMIT 1;
-- List of passengers on this flight.
SELECT people.name FROM people JOIN passengers ON people.passport_number = passengers.passport_number WHERE passengers.flight_id = (SELECT id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND flights.day = 29 ORDER BY flights.hour LIMIT 1);

-- I corrected the syntax to join ALL the previous name lists and this is the result:
SELECT name FROM people JOIN phone_calls ON phone_calls.caller = people.phone_number JOIN passengers ON people.passport_number = passengers.passport_number JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE phone_calls.day = 28 AND phone_calls.month = 7 AND phone_calls.duration < 61 AND passengers.flight_id = (SELECT id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND flights.day = 29 ORDER BY flights.hour LIMIT 1) AND atm_transactions.atm_location = "Leggett Street" AND atm_transactions.day = 28 AND atm_transactions.transaction_type = "withdraw" AND bakery_security_logs.activity = "exit" AND bakery_security_logs.day = 28 AND bakery_security_logs.month = 7 AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute < 26 AND bakery_security_logs.minute > 14;
-- Only Bruce:
-- - Left within ten minutes of the theft.
-- - Was heading out the next day in the earliest flight.
-- - Withdrew money from the ATM.
-- - And made a call shorter than a minute.

-- Referencing the only person that Bruce called that day for less than a minute:
SELECT * FROM people JOIN phone_calls ON phone_calls.receiver = people.phone_number WHERE phone_calls.day = 28 AND phone_calls.month = 7 AND phone_calls.duration < 61 AND phone_calls.caller = (SELECT people.phone_number FROM people JOIN phone_calls ON phone_calls.caller = people.phone_number JOIN passengers ON people.passport_number = passengers.passport_number JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE phone_calls.day = 28 AND phone_calls.month = 7 AND phone_calls.duration < 61 AND passengers.flight_id = (SELECT id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND flights.day = 29 ORDER BY flights.hour LIMIT 1) AND atm_transactions.atm_location = "Leggett Street" AND atm_transactions.day = 28 AND atm_transactions.transaction_type = "withdraw" AND bakery_security_logs.activity = "exit" AND bakery_security_logs.day = 28 AND bakery_security_logs.month = 7 AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute < 26 AND bakery_security_logs.minute > 14);
-- It's Robin.

-- The flight that Bruce took is going to New York City:
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND flights.day = 29 ORDER BY flights.hour LIMIT 1);




-- I formatted online at SQLFormat.org, but didn't check, so if needed it's below:

-- Keep a log of any SQL queries you execute as you solve the mystery.
 .schema -- Overview of the database

SELECT *
FROM crime_scene_reports; -- Just to get my bearings on what this table looks like.

SELECT *
FROM crime_scene_reports
WHERE street = "Humphrey Street"; -- Just to see what happened on the street, not including the day;

SELECT *
FROM crime_scene_reports
WHERE street = "Humphrey Street"
  AND DAY = 28
  AND MONTH = 7; -- Apparently, there was another crime, but no witness. Don't know yet if correlated. Three witnesses mention the bakery and were interviewed. Tge crime occurred 10h15am;

SELECT *
FROM interviews; -- Unproductive, but just to get my bearings.

SELECT *
FROM interviews
WHERE DAY = 28
  AND MONTH = 7; -- Saw the interviews from this day and month. Not much interesting. Since the bakery apparently was mentioned all three times, the next will be more conclusive.

SELECT *
FROM interviews
WHERE transcript LIKE "%bakery%"
  AND DAY = 28
  AND MONTH = 7; -- Decided to limit to only the bakery.

SELECT name,
       transcript
FROM interviews
WHERE transcript LIKE "%bakery%"
  AND DAY = 28
  AND MONTH = 7; -- Just the transcripts with names, so we can take notes.

-- Ruth says the thief got into a car and drove away within10 minutes after the theft. Suggested looking at security footage from the bakery.
-- Eugene says he saw the thief in the morning in the ATM on Leggett Street withdrawing some money. The bakery is Emma's.
-- Raymond said that he called someone and talked less than a minute and planned to take the earliest flight out of fiftyville on the 29/07. The accomplice was asked to buy the ticket.
 -- License_plate investigation:
 -- 9 cars exited the premises from 10h16 til 10h35. Most probably one of the the two that left 10h23, would match testimony. Further investigation required.

SELECT *
FROM bakery_security_logs
WHERE DAY = 28
  AND MONTH = 7
  AND HOUR = 10
  AND activity = "exit";

-- List of people who exited the premises at 10am.

SELECT people.name
FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.activity = "exit"
  AND bakery_security_logs.day = 28
  AND bakery_security_logs.month = 7
  AND bakery_security_logs.hour = 10;

-- This is a list of people that exited "within" ten minutes of the 10h15 incident.

SELECT people.name
FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.activity = "exit"
  AND bakery_security_logs.day = 28
  AND bakery_security_logs.month = 7
  AND bakery_security_logs.hour = 10
  AND bakery_security_logs.minute < 26
  AND bakery_security_logs.minute > 14;

-- ATM investigation:
-- List of withdraws made that day on the ATM on Leggett Street.

SELECT *
FROM atm_transactions
WHERE atm_location = "Leggett Street"
  AND DAY = 28
  AND MONTH = 7
  AND transaction_type = "withdraw";

-- List of bank accounts withdrawn that day.

SELECT *
FROM bank_accounts
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.atm_location = "Leggett Street"
  AND atm_transactions.day = 28
  AND atm_transactions.transaction_type = "withdraw";

-- List of names that withdrew from the account on the 28th

SELECT people.name
FROM bank_accounts
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON people.id = bank_accounts.person_id
WHERE atm_transactions.atm_location = "Leggett Street"
  AND atm_transactions.day = 28
  AND atm_transactions.transaction_type = "withdraw";

-- OR important for later!!

SELECT people.name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.atm_location = "Leggett Street"
  AND atm_transactions.day = 28
  AND atm_transactions.transaction_type = "withdraw";

-- Phone investigation:
-- List of all phone calls that are less than 80 seconds long the 28th.

SELECT *
FROM phone_calls
WHERE phone_calls.day = 28
  AND phone_calls.month = 7
  AND phone_calls.duration < 80;

-- List of name of all callers on the 28th that made calls that lasted less than 61 seconds.

SELECT people.name
FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE phone_calls.day = 28
  AND phone_calls.month = 7
  AND phone_calls.duration < 61;

-- List of name of all receivers.

SELECT people.name
FROM people
JOIN phone_calls ON phone_calls.receiver = people.phone_number
WHERE phone_calls.day = 28
  AND phone_calls.month = 7
  AND phone_calls.duration < 61;

-- Airport investigation:
-- Id for Fiftyville's airport.

SELECT id
FROM airports
WHERE city = "Fiftyville";

-- Earliest flight leaving Fiftyville's airport on the 29th.

SELECT *
FROM flights
WHERE origin_airport_id =
    (SELECT id
     FROM airports
     WHERE city = "Fiftyville")
  AND flights.day = 29
ORDER BY flights.hour
LIMIT 1;

-- List of passengers on this flight.

SELECT people.name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE passengers.flight_id =
    (SELECT id
     FROM flights
     WHERE origin_airport_id =
         (SELECT id
          FROM airports
          WHERE city = "Fiftyville")
       AND flights.day = 29
     ORDER BY flights.hour
     LIMIT 1);

-- I corrected the syntax to join ALL the previous name lists and this is the result:

SELECT name
FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE phone_calls.day = 28
  AND phone_calls.month = 7
  AND phone_calls.duration < 61
  AND passengers.flight_id =
    (SELECT id
     FROM flights
     WHERE origin_airport_id =
         (SELECT id
          FROM airports
          WHERE city = "Fiftyville")
       AND flights.day = 29
     ORDER BY flights.hour
     LIMIT 1)
  AND atm_transactions.atm_location = "Leggett Street"
  AND atm_transactions.day = 28
  AND atm_transactions.transaction_type = "withdraw"
  AND bakery_security_logs.activity = "exit"
  AND bakery_security_logs.day = 28
  AND bakery_security_logs.month = 7
  AND bakery_security_logs.hour = 10
  AND bakery_security_logs.minute < 26
  AND bakery_security_logs.minute > 14;

-- Only Bruce:
-- - Left within ten minutes of the theft.
-- - Was heading out the next day in the earliest flight.
-- - Withdrew money from the ATM.
-- - And made a call shorter than a minute.
 -- Referencing the only person that Bruce called that day for less than a minute:

SELECT *
FROM people
JOIN phone_calls ON phone_calls.receiver = people.phone_number
WHERE phone_calls.day = 28
  AND phone_calls.month = 7
  AND phone_calls.duration < 61
  AND phone_calls.caller =
    (SELECT people.phone_number
     FROM people
     JOIN phone_calls ON phone_calls.caller = people.phone_number
     JOIN passengers ON people.passport_number = passengers.passport_number
     JOIN bank_accounts ON people.id = bank_accounts.person_id
     JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
     JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
     WHERE phone_calls.day = 28
       AND phone_calls.month = 7
       AND phone_calls.duration < 61
       AND passengers.flight_id =
         (SELECT id
          FROM flights
          WHERE origin_airport_id =
              (SELECT id
               FROM airports
               WHERE city = "Fiftyville")
            AND flights.day = 29
          ORDER BY flights.hour
          LIMIT 1)
       AND atm_transactions.atm_location = "Leggett Street"
       AND atm_transactions.day = 28
       AND atm_transactions.transaction_type = "withdraw"
       AND bakery_security_logs.activity = "exit"
       AND bakery_security_logs.day = 28
       AND bakery_security_logs.month = 7
       AND bakery_security_logs.hour = 10
       AND bakery_security_logs.minute < 26
       AND bakery_security_logs.minute > 14);

-- It's Robin.
 -- The flight that Bruce took is going to New York City:

SELECT city
FROM airports
WHERE id =
    (SELECT destination_airport_id
     FROM flights
     WHERE origin_airport_id =
         (SELECT id
          FROM airports
          WHERE city = "Fiftyville")
       AND flights.day = 29
     ORDER BY flights.hour
     LIMIT 1);