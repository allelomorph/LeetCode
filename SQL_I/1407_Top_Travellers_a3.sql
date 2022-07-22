-- Time to complete: 15 mins

-- Needed to research:
--   - IFNULL()

---- Begin solution, results at https://leetcode.com/submissions/detail/752418596/


-- Report the distance traveled by each user.
WITH UserTrips AS (
    SELECT
        Users.id AS user_id,
        name,
        distance
    FROM
        Users
            LEFT JOIN
        Rides ON Users.id = Rides.user_id
), UserDistanceSums AS (
    SELECT
        name,
        SUM(distance) AS sum_distance
    FROM
        UserTrips
    GROUP BY
        user_id
)

SELECT
    name,
    IFNULL(sum_distance, 0) AS travelled_distance
FROM
    UserDistanceSums
ORDER BY
    travelled_distance DESC,
    name ASC;


---- End solution
