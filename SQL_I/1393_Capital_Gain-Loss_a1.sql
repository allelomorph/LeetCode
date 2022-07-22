-- Time to complete: 20 mins

-- Needed to research:
--   - CTEs
--     - https://www.mysqltutorial.org/mysql-cte/
--     - https://learnsql.com/blog/sql-subquery-cte-difference/
--   - USING()

---- Begin solution, results at https://leetcode.com/submissions/detail/751668237/


-- Reports the capital gain/loss for each stock.
-- Note: every Buy has a corresponding (later) Sell, and vice versa
WITH Expenditures AS (
    SELECT
        stock_name,
        SUM(price) AS expenditure
    FROM
        Stocks
    WHERE
        operation = 'Buy'
    GROUP BY
        stock_name
), Revenue AS (
    SELECT
        stock_name,
        SUM(price) AS revenue
    FROM
        Stocks
    WHERE
        operation = 'Sell'
    GROUP BY
        stock_name
)
SELECT
    stock_name,
    revenue - expenditure AS capital_gain_loss
FROM
    Expenditures
        JOIN
    Revenue USING(stock_name);


---- End solution
