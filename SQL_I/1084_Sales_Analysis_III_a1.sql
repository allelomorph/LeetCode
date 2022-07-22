-- Time to complete: 15 mins

-- Treated as: study problem (research allowed)

-- Needed to research:

---- Begin solution, results at https://leetcode.com/submissions/detail/752441705/


-- Reports the products that were only sold in the first quarter of 2019
WITH Q1_Sales AS (
    SELECT
        product_id,
        SUM(IF(
          sale_date >= '2019-01-01' AND sale_date < '2019-04-01', 1, 0)
          ) AS sold_q1,
        COUNT(*) AS total_sold
    FROM
       Sales
    GROUP BY
       product_id
)

SELECT
    product_id,
    product_name
FROM
    Product
       JOIN
    Q1_Sales USING(product_id)
WHERE
    total_sold = sold_q1;


---- End solution
