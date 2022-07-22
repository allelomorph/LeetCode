-- Time to complete: 3 mins

-- Needed to research:

---- Begin solution, results at https://leetcode.com/submissions/detail/753072797/


-- Reports name and balance of users with a balance higher than 10000.
WITH UserBalances AS (
    SELECT
        account,
        SUM(amount) AS balance
    FROM
        Transactions
    GROUP BY
        account
)

SELECT
    name,
    balance
FROM
    UserBalances
        JOIN
    Users USING(account)
WHERE
    balance > 10000;


---- End solution
