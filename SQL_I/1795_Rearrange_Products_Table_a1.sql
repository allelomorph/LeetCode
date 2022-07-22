-- Time to complete: 15 mins

-- Treated as: study problem (research allowed)

-- Needed to research:

-- Note: Is there a way to generalize this instead of rewriting the query for
--    all three store columns in the original table? What if there were 100
--    stores?

---- Begin solution, results at https://leetcode.com/submissions/detail/748940815/


-- Retrieves product id, store in which it sold, and price for every valid sale
SELECT product_id,
    'store1' AS store,
    store1 AS price FROM Products
WHERE store1 IS NOT NULL
UNION
SELECT product_id,
    'store2' AS store,
    store2 AS price FROM Products
    WHERE store2 IS NOT NULL
UNION
SELECT product_id,
    'store3' AS store,
    store3 AS price FROM Products
    WHERE store3 IS NOT NULL
ORDER BY product_id, store;


---- End solution
