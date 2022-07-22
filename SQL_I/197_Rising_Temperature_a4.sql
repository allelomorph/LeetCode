-- Time to complete: 1 hr

-- Needed to research:
--   - date functions:
--     - https://dev.mysql.com/doc/refman/8.0/en/date-and-time-functions.html
--     - https://www.mysqltutorial.org/mysql-date/
--   - why one cannot use `<date> + 1` syntax:
--     - https://stackoverflow.com/a/68865318
--   - but `<date> + INTERVAL 1 day` would work?
--     - https://www.tutorialspoint.com/How-MySQL-performs-date-arithmetic-with-addition-and-subtraction-operators
--   - `INNER JOIN`ing a table to itself to compare successive rows:
--     - https://www.mysqltutorial.org/mysql-tips/mysql-compare-calculate-difference-successive-rows/

---- Begin solution, results at https://leetcode.com/submissions/detail/749932102/


-- Retreive all ids of date records of temperatures higher than the previous day.
SELECT
    B.id
FROM
    Weather AS A
        INNER JOIN
    Weather AS B ON B.recordDate = DATE_ADD(A.recordDate, INTERVAL 1 DAY)
WHERE
    B.temperature > A.temperature
ORDER BY
    A.recordDate ASC;


---- End solution
