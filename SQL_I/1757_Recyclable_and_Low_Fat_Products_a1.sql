-- Time to complete: 5 min

-- Treated as: study problem (research allowed)

-- Needed to research:

---- Begin solution, results at https://leetcode.com/submissions/detail/747276971/


-- Retrieves ids of products that are both low fat and recycleable
SELECT product_id FROM Products
    WHERE low_fats = 'Y' AND recyclable = 'Y';


---- End solution
