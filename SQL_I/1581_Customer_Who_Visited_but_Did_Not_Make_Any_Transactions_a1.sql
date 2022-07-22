-- Time to complete: 10 mins

-- Needed to research:

---- Begin solution, results at https://leetcode.com/submissions/detail/749863102/


-- Retrieves IDs of users who visited without making any transactions, and the number
--    of times they made these types of visits
SELECT A.customer_id, COUNT(*) AS count_no_trans FROM Visits AS A
LEFT JOIN Transactions AS B
ON A.visit_id = B.visit_id
WHERE B.visit_id IS NULL
GROUP BY A.customer_id;


---- End solution
