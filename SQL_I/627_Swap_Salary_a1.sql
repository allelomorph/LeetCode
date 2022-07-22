-- Time to complete: 15 mins

-- Needed to research:
--  - UPDATE / SET
--  SQL uses `=` for evaluation as well as assignment

---- Begin solution, results at https://leetcode.com/submissions/detail/748133014/


-- Swaps all 'f' and 'm' values in Salary with a single update statement
UPDATE Salary SET sex = IF(Salary.sex = 'm', 'f', 'm');


---- End solution
