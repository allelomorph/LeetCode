-- Time to complete: 20 mins

-- Treated as: study problem (research allowed)

-- Needed to research:
--   - MAX() in WHERE clause of same query:
--     - https://stackoverflow.com/a/22538476

---- Begin solution, results at https://leetcode.com/submissions/detail/750652972/


--  Retrieves customer_number(s) with the largest number of orders.
SELECT
    A.customer_number
FROM
    (
     SELECT
         customer_number,
         COUNT(order_number) AS order_count
     FROM
         Orders
     GROUP BY
         customer_number
    ) AS A
JOIN
    (
     SELECT
         MAX(B.order_count) AS max_order_count
     FROM (
           SELECT
               COUNT(order_number) AS order_count
           FROM
               Orders
           GROUP BY
               customer_number
          ) AS B
     ) AS C ON A.order_count = max_order_count;


---- End solution
