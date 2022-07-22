-- Time to complete: 30 mins (all attempts)

-- Needed to research:
--  - https://www.databasestar.com/sql-remove-duplicates/
--  - https://stackoverflow.com/a/14302701

---- Begin solution, results at https://leetcode.com/submissions/detail/748154402/


-- (MySQL prevents duplicate aliases, and also reference of the same table
--    in a subquery, otherwise the 4th line could be: `FROM Person`
DELETE FROM Person
WHERE id NOT IN (
      SELECT MIN(id)
      FROM (SELECT id, email FROM Person) AS t2
      GROUP BY email
);


---- End solution
