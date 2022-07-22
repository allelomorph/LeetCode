-- Time to complete: 30 mins (all attempts)

-- Needed to research:
--  - https://www.databasestar.com/sql-remove-duplicates/

---- Begin solution, results at https://leetcode.com/submissions/detail/748150273/


-- Deletes all duplicate emails, keeping only the copy with the lowest id
-- (AS is redundant in both cases, but improves readability)
DELETE t1 FROM Person AS t1
INNER JOIN Person AS t2
ON t1.id > t2.id AND t1.email = t2.email;


---- End solution
