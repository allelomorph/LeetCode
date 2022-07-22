-- Time to complete: 5 mins

-- Needed to research:

---- Begin solution, results at https://leetcode.com/submissions/detail/750630676/


-- Returns the number of followers for each user
SELECT
    user_id,
    COUNT(DISTINCT follower_id) AS followers_count
FROM
    Followers
GROUP BY
    user_id
ORDER BY
    user_id ASC;


---- End solution
