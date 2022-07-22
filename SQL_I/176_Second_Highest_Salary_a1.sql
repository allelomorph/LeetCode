-- Time to complete: 2 hrs

-- Needed to research:
--   - LIMIT:
--     - https://dev.mysql.com/doc/refman/8.0/en/limit-optimization.html
--     - https://stackoverflow.com/a/463112
--   - SET:
--     - https://dev.mysql.com/doc/refman/8.0/en/set-variable.html ,
--     - https://www.delftstack.com/howto/mysql/mysql-declare-variable/

-- Notes:
--   - `AS _` due to requirement for distinct aliases in query
--   - Would have preferred to make main query once, then test its length, and
--       return either the singular value or NULL. But could not figure out how
--       to store anything other than int/string/etc into variables.
--   - In the official docs, there is no mention of LIMIT taking two
--       arguments, but with experimentation they were found to be the
--       starting 0-index of results, and the amount of results to include.


---- Begin solution, results at https://leetcode.com/submissions/detail/748974718/


--  Reports second highest salary from the Employee table, or null if none found
SELECT IF(
    (
        SELECT COUNT(*) FROM (
            SELECT salary FROM Employee
            GROUP BY salary
            ORDER BY salary DESC
            LIMIT 1,1
        ) AS _
    ) = 1,
    (
        SELECT salary FROM Employee
        GROUP BY salary
        ORDER BY salary DESC
        LIMIT 1,1
    ),
    NULL
) AS SecondHighestSalary;


---- End solution
