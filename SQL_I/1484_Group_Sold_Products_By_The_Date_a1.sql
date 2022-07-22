-- Time to complete: 20 mins

-- Treated as: study problem (research allowed)

-- Needed to research:
--   - GROUP_CONCAT()
--   - https://mathworld.wolfram.com/LexicographicOrder.html
--   - DISTINCT

---- Begin solution, results at https://leetcode.com/submissions/detail/748235516/


-- Retrieves sales data by date: total products sold and sorted names of products
-- GROUP_CONCAT also takes a SEPARATOR arg, but ',' is the default
SELECT sell_date,
       COUNT(*) AS num_sold,
       GROUP_CONCAT(
           product ORDER BY product ASC
       ) AS products
FROM (
     SELECT DISTINCT sell_date, product
         FROM Activities
         ORDER BY sell_date
) AS _Activities
GROUP BY sell_date;


---- End solution
