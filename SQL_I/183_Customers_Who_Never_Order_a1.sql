-- Time to complete: 5 mins

-- Treated as: study problem (research allowed)

-- Needed to research:

-- Note: Poor speed performance, at only 5.39 percentile - how to improve?

---- Begin solution, results at https://leetcode.com/submissions/detail/747289925/


-- reports any customers who have no orders on record
SELECT name AS Customers FROM Customers
    LEFT JOIN Orders ON Customers.id = customerId
        WHERE customerId IS NULL;


---- End solution
