-- Time to complete: 5 mins

-- Treated as: study problem (research allowed)

-- Needed to research:
--   - YEAR()

---- Begin solution, results at https://leetcode.com/submissions/detail/751545027/


-- Reports most recent login in 2020 for all users in the year 2020.
SELECT
    user_id,
    MAX(time_stamp) AS last_stamp
FROM
    Logins
WHERE
    YEAR(time_stamp) = 2020
GROUP BY
    user_id;


---- End solution
