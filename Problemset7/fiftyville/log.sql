-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get police report
--SELECT id, description
--FROM crime_scene_reports
--WHERE street = 'Humphrey Street' AND day = 28 AND month = 7 and year = 2021;
    -- 295|Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- Find interviews
--SELECT name, transcript
--FROM interviews
--WHERE day = 28 AND month = 7 AND year = 2021 AND transcript LIKE '%bakery%';
    -- Ruth|Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame
    -- Eugene|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
    -- Raymond|As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Get bakery security logs per Ruth interview
--SELECT hour, minute, activity, license_plate
--FROM bakery_security_logs
--WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10;
    --10|8|entrance|R3G7486
    --10|14|entrance|13FNH73
    --10|16|exit|5P2BI95
    --10|18|exit|94KL13X
    --10|18|exit|6P58WS2
    --10|19|exit|4328GD8
    --10|20|exit|G412CB7
    --10|21|exit|L93JTIZ
    --10|23|exit|322W7JE
    --10|23|exit|0NTHK55
    --10|35|exit|1106N58
    --10|42|entrance|NRYN856
    --10|44|entrance|WD5M8I6
    --10|55|entrance|V47T75I

-- Get atm transactions per Eugene interview
--SELECT account_number, transaction_type, amount, atm_location
--FROM atm_transactions
--WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location LIKE '%Leggett%';
    -- 28500762|withdraw|48|Leggett Street
    -- 28296815|withdraw|20|Leggett Street
    -- 76054385|withdraw|60|Leggett Street
    -- 49610011|withdraw|50|Leggett Street
    -- 16153065|withdraw|80|Leggett Street
    -- 86363979|deposit|10|Leggett Street
    -- 25506511|withdraw|20|Leggett Street
    -- 81061156|withdraw|30|Leggett Street
    -- 26013199|withdraw|35|Leggett Street
        -- Get bank accounts matching atm
        --SELECT person_id, creation_year, name, phone_number, passport_number, license_plate
        --FROM bank_accounts
        --JOIN people ON people.id = bank_accounts.person_id
        --WHERE account_number IN
            --(SELECT account_number
            --FROM atm_transactions
            --WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location LIKE '%Leggett%' AND transaction_type = 'withdraw');
            --686048|2010|Bruce|(367) 555-5533|5773159633|94KL13X
            --514354|2012|Diana|(770) 555-1861|3592750733|322W7JE
            --458378|2012|Brooke|(122) 555-4581|4408372428|QX4YZN3
            --395717|2014|Kenny|(826) 555-1652|9878712108|30G67EN
            --396669|2014|Iman|(829) 555-5269|7049073643|L93JTIZ
            --467400|2014|Luca|(389) 555-5198|8496433585|4328GD8
            --449774|2015|Taylor|(286) 555-6 a063|1988161715|1106N58
            --438727|2018|Benista|(338) 555-6650|9586786673|8X428L0

-- Get phone calls per Raymond interview
--SELECT caller, receiver, duration
--FROM phone_calls
--WHERE day = 28 AND month = 7 AND year = 2021 AND duration <60;

-- Get flights per Raymond interview
-- Passengers
--SELECT passport_number
--FROM passengers
--WHERE flight_id =
    --(SELECT id
    --FROM flights
    --WHERE day = 29 AND month = 7 AND year = 2021 AND origin_airport_id =
        --(SELECT id
        --FROM airports
        --WHERE city = 'Fiftyville')
    --ORDER BY hour, minute
    --LIMIT 1);
--Destination
SELECT full_name, city
FROM airports
WHERE id =
    (SELECT destination_airport_id
    FROM flights
    WHERE day = 29 AND month = 7 AND year = 2021 AND origin_airport_id =
        (SELECT id
        FROM airports
        WHERE city = 'Fiftyville')
    ORDER BY hour, minute
    LIMIT 1);

-- ONGOING SUSPECT QUERY
SELECT person_id, creation_year, name, phone_number, passport_number, license_plate
FROM bank_accounts
JOIN people ON people.id = bank_accounts.person_id
WHERE account_number IN
    (SELECT account_number
    FROM atm_transactions
    WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location LIKE '%Leggett%' AND transaction_type = 'withdraw')
AND license_plate IN
    (SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute BETWEEN 15 AND 25 AND activity = 'exit')
AND phone_number IN
    (SELECT caller
    FROM phone_calls
    WHERE day = 28 AND month = 7 AND year = 2021 AND duration <60)
AND passport_number IN
    (SELECT passport_number
    FROM passengers
    WHERE flight_id =
        (SELECT id
        FROM flights
        WHERE day = 29 AND month = 7 AND year = 2021 AND origin_airport_id =
            (SELECT id
            FROM airports
            WHERE city = 'Fiftyville')
        ORDER BY hour, minute
        LIMIT 1));

-- ONGOING ACCOMPLICE QUERY
SELECT name
FROM people
WHERE phone_number IN
    (SELECT receiver
    FROM phone_calls
    WHERE day = 28 AND month = 7 AND year = 2021 AND duration <60 AND caller = '(367) 555-5533');
