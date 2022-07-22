-- Time to complete: 10 mins

-- Needed to research:
--   - DATE(), BETWEEN for date range:
--     - https://stackoverflow.com/a/3652016

-- Note: slow speed performance, and theme of the day is "Functions." Is there
--   a way to create a faster compound statment inside a BEGIN/END?

---- Begin solution, results at https://leetcode.com/submissions/detail/750628531/


-- Finds the daily active user count for 2019-06-28 to 2019-07-27
SELECT
    activity_date AS day,
    COUNT(DISTINCT user_id) AS active_users
FROM
    Activity
WHERE
    DATE(activity_date) BETWEEN '2019-06-28' AND '2019-07-27'
GROUP BY
    activity_date;


---- End solution
