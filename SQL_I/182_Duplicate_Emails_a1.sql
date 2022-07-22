-- Time to complete: 3 mins

-- Treated as: study problem (research allowed)

-- Needed to research:

---- Begin solution, results at https://leetcode.com/submissions/detail/752422759/


-- Reports all duplicate emails in Person.
WITH EmailCounts AS (
    SELECT
        email,
        COUNT(*) as count
    FROM
        Person
    GROUP BY
        email
)

SELECT
        email AS Email
    FROM
        EmailCounts
    WHERE
        count > 1;


---- End solution
