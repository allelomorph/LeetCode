-- Time to complete: 5 min

-- Needed to research:

-- Note: Poor speed performance, at only 7.32 percentile - how to improve?

---- Begin solution, results at https://leetcode.com/submissions/detail/747280154/


-- Finds the names any customers that are not referred by the customer with id = 2
SELECT name from Customer
    WHERE referee_id IS NULL OR referee_id != 2;


---- End solution
