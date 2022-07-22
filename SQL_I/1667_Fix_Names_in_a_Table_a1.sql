-- Time to complete: 10 mins

-- Needed to research:
--   - UPPER, LOWER, LENGTH, CONCAT

---- Begin solution, results at


-- Returns Users with all names starting with uppercase letter followed by lowercase
SELECT user_id,
    CONCAT(UPPER(LEFT(name, 1)), LOWER(RIGHT(name, LENGTH(name) - 1))) AS name
    FROM Users
    ORDER BY user_id ASC;



---- End solution
