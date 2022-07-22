-- Time to complete: 25 mins

-- Needed to research:
--  - IF() (not IF)
--  - MOD()
--  - LEFT()

---- Begin solution, results at https://leetcode.com/submissions/detail/748125084/


-- Calculates bonus pay for each employee, awarded only to those with
--   an odd id number and a name not starting with 'M'
SELECT employee_id,
       IF(MOD(employee_id, 2) AND LEFT(Employees.name, 1) != 'M', salary, 0)
       AS bonus
FROM Employees
ORDER BY employee_id ASC;


---- End solution
