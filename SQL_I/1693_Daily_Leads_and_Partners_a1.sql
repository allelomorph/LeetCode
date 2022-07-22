-- Time to complete: 10 mins

-- Needed to research:

-- Note: slow speed performance, and theme of the day is "Functions." Is there
--   a way to create a faster compound statment inside a BEGIN/END?

---- Begin solution, results at https://leetcode.com/submissions/detail/750619616/


-- Returns number of distinct lead_ids and partner_ids for each date_id and make_name
SELECT
    date_id,
    make_name,
    COUNT(DISTINCT lead_id) AS unique_leads,
    COUNT(DISTINCT partner_id) AS unique_partners
FROM
    DailySales
GROUP BY
    make_name,
    date_id;


---- End solution
