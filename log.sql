-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find description of crimes from the right date and street
SELECT description
FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time –
-- each of their interview transcripts mentions the bakery. |
-- Littering took place at 16:36. No known witnesses.

-- Find the interview texts
SELECT transcript, name
FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28;

--information from witnesses:

--Ruth:
--Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

--Check security footage
SELECT activity, license_plate
FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

--License Plates that Left
--5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55

--Eugene:
--I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
--I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

--look at transactions and amount
SELECT account_number, transaction_type, amount
FROM atm_transactions
WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street";

--account number, amount:
--28500762, 48
--28296815, 20
--76054385, 60
--49610011, 50
--16153065, 80
--25506511, 20
--81061156, 30
--26013199, 35

--Raymond:
--As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--The thief then asked the person on the other end of the phone to purchase the flight ticket.

--check phones to see details of the call
SELECT caller, receiver
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

-- caller     |    receiver    |
----------------+----------------+
--| (130) 555-0289 | (996) 555-8899 |
--| (499) 555-9472 | (892) 555-8872 |
--| (367) 555-5533 | (375) 555-8161 |
--| (499) 555-9472 | (717) 555-1342 |
--| (286) 555-6063 | (676) 555-6554 |
--| (770) 555-1861 | (725) 555-3243 |
--| (031) 555-6622 | (910) 555-3251 |
--| (826) 555-1652 | (066) 555-9701 |
--| (338) 555-6650 | (704) 555-2131 |

--Find city the thief escaped to
SELECT abbreviation, full_name, city
FROM airports
WHERE id =
(SELECT destination_airport_id
FROM flights
WHERE origin_airport_id =
(SELECT id FROM airports WHERE city = "Fiftyville")
AND year = 2021 AND month = 7 AND day = 29
ORDER BY hour
LIMIT 1);

--Find passport number and seat
SELECT passport_number, seat
FROM passengers
WHERE flight_id =
(SELECT id
FROM flights
WHERE origin_airport_id =
(SELECT id FROM airports WHERE city = "Fiftyville")
AND year = 2021 AND month = 7 AND day = 29
ORDER BY hour
LIMIT 1);

--Info known: potential license plates, potential phone numbers, potential account_numbers, potential passport_numbers

-- passport_number | seat |
-----------------+------+
--| 7214083635      | 2A   |
--| 1695452385      | 3B   |
--| 5773159633      | 4A   |
--| 1540955065      | 5C   |
--| 8294398571      | 6C   |
--| 1988161715      | 6D   |
--| 9878712108      | 7A   |
--| 8496433585      | 7B   |

--Find person
SELECT name
FROM people
WHERE phone_number IN
(SELECT caller
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
AND license_plate IN
(SELECT license_plate
FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25)
AND passport_number IN
(SELECT passport_number
FROM passengers
WHERE flight_id =
(SELECT id
FROM flights
WHERE origin_airport_id =
(SELECT id FROM airports WHERE city = "Fiftyville")
AND year = 2021 AND month = 7 AND day = 29
ORDER BY hour
LIMIT 1));

--Sofia, Bruce, Kesley

--Figure out who it is based on ATM

SELECT name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.person_id IN
(SELECT id
FROM people
WHERE phone_number IN
(SELECT caller
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60)
AND license_plate IN
(SELECT license_plate
FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25)
AND passport_number IN
(SELECT passport_number
FROM passengers
WHERE flight_id =
(SELECT id
FROM flights
WHERE origin_airport_id =
(SELECT id FROM airports WHERE city = "Fiftyville")
AND year = 2021 AND month = 7 AND day = 29
ORDER BY hour
LIMIT 1)));

--Confirm that it is Bruce
SELECT name
FROM people
WHERE id IN
(SELECT person_id
FROM bank_accounts
WHERE account_number IN
(SELECT account_number
FROM atm_transactions
WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street"));

--Find the accomplice
SELECT name
FROM people
WHERE phone_number =
(SELECT receiver
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller =
(SELECT phone_number
FROM people
WHERE name = "Bruce"));
