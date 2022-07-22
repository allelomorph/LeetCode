-- Time to complete: 30 mins

-- Needed to research:

---- Begin solution, results at https://leetcode.com/submissions/detail/752413818/


-- Finds join date and number of orders as buyer for each user in 2019
WITH 2019_Purchases AS (
    SELECT
        buyer_id,
        COUNT(*) AS orders_in_2019
    FROM
        Orders
    WHERE
        YEAR(order_date) = 2019
    GROUP BY
        buyer_id
)

SELECT
    user_id AS buyer_id,
    join_date,
    IFNULL(orders_in_2019, 0) AS orders_in_2019
FROM
    Users
        LEFT JOIN
    2019_Purchases ON user_id = buyer_id;


---- End solution
