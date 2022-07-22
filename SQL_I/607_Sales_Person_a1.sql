-- Time to complete: 30 mins

-- Treated as: study problem (research allowed)

-- Needed to research:

---- Begin solution, results at https://leetcode.com/submissions/detail/749943029/


--  Reports names of all salespersons without orders related to the company "RED"
SELECT DISTINCT A.name FROM SalesPerson AS A
LEFT JOIN Orders AS B
ON A.sales_id = B.sales_id
WHERE B.sales_id IS NULL OR B.sales_id NOT IN (  -- sometimes causes duplicates
    SELECT DISTINCT sales_id FROM Orders
    WHERE com_id = (
        SELECT com_id FROM Company
        WHERE name = 'RED'
    )
);


---- End solution
