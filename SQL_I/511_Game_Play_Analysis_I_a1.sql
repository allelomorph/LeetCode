-- Time to complete: 5 mins

-- Treated as: study problem (research allowed)

-- Needed to research:

---- Begin solution, results at https://leetcode.com/submissions/detail/750634699/


-- Reports the first login date for each player
SELECT
    player_id,
    MIN(event_date) AS first_login
FROM
    Activity
GROUP BY
    player_id;


---- End solution
