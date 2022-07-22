-- Time to complete: 15 mins

-- Needed to research:
--   - UNION (DISTINCT), UNION ALL
--   - no FULL OUTER JOIN in MySQL: https://stackoverflow.com/a/4796911

---- Begin solution, results at https://leetcode.com/submissions/detail/748932355/


-- Lists all ids for employees with missing records, in ascending order
-- FULL OUTER JOIN not supported by MySQL
SELECT A.employee_id FROM Employees AS A
LEFT JOIN Salaries AS B
ON A.employee_id = B.employee_id
WHERE B.employee_id IS NULL
UNION
SELECT A.employee_id FROM Salaries AS A
LEFT JOIN Employees AS B
ON A.employee_id = B.employee_id
WHERE B.employee_id IS NULL
ORDER BY employee_id ASC;


---- End solution
