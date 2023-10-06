-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Check tables list
.tables

-- Check crime_scene_reports structure
.schema crime_scene_reports

-- Query details about the crime that took place on 'July 28' on 'Humphrey Street'
SELECT description
  FROM crime_scene_reports
 WHERE month = 7
   AND day = 28
   AND street = "Humphrey Street";

-- Check interviews structure
.schema interviews

-- Query details about the interviews on 'July 28'
SELECT name, transcript
  FROM interviews
 WHERE month = 7
   AND day = 28;

-- Check flights, airports structure
.schema flights
.schema airports

-- Query details of the 'earliest' flight on 'July 29' from 'Fiftyville'
SELECT *
  FROM flights
 WHERE month = 7
   AND day = 29
   AND origin_airport_id =
       (SELECT id
          FROM airports
         WHERE city = "Fiftyville")
 ORDER BY hour, minute
 LIMIT 1;

 -- Query city of destination airport id of '4'
 SELECT city
   FROM airports
  WHERE id = 4;

-- Check various tables structure
.schema people
.schema atm_transactions
.schema bank_accounts
.schema phone_calls
.schema passengers

-- Query names about people who 'exit' from bakery on 'July 28' between '10.15am' and '10.25am'
--                          who 'withdraw' from an ATM on 'Leggett Street' on 'July 28'
--                          who made a phone call on 'July 28' with a duration of 'less than 60s'
--                          who will be on flight id '36'
SELECT name
  FROM people
 WHERE license_plate IN
       (SELECT license_plate
          FROM bakery_security_logs
         WHERE month = 7
           AND day = 28
           AND hour = 10
           AND minute >= 15
           AND minute <= 25
           AND activity = "exit")
   AND id IN
       (SELECT person_id
          FROM bank_accounts
         WHERE account_number IN
               (SELECT account_number
                  FROM atm_transactions
                 WHERE month = 7
                   AND day = 28
                   AND atm_location = "Leggett Street"
                   AND transaction_type = "withdraw"))
   AND phone_number IN
       (SELECT caller
          FROM phone_calls
         WHERE month = 7
           AND day = 28
           AND duration < 60)
   AND passport_number IN
       (SELECT passport_number
          FROM passengers
         WHERE flight_id = 36);

-- Query names about people who receive a phone call on 'July 28' with a duration of 'less than 60s' from 'Bruce'
SELECT name
  FROM people
 WHERE phone_number IN
       (SELECT receiver
          FROM phone_calls
         WHERE month = 7
           AND day = 28
           AND duration < 60
           AND caller IN
               (SELECT phone_number
                  FROM people
                 WHERE name = "Bruce"));
