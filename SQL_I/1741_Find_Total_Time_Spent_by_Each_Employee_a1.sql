-- Time to complete: 10 mins

-- Treated as: study problem (research allowed)

-- Needed to research:

---- Begin solution, results at https://leetcode.com/submissions/detail/751553640/


-- Returns total minutes spent by each employee on each day at the office.
SELECT
    day,
    emp_id,
    SUM(visit_time) AS total_time
FROM (
      SELECT
          emp_id,
          event_day AS day,
          out_time - in_time AS visit_time
      FROM
          Employees
      ) AS EmployeeVisits
GROUP BY
    day,
    emp_id
ORDER BY
    day,
    emp_id;


---- End solution
