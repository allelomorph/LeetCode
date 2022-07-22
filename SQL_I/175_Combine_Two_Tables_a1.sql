-- Time to complete: 5 mins

-- Needed to research:

---- Begin solution, results at https://leetcode.com/submissions/detail/749857475/


-- Reports the first name, last name, city, and state of each person in Person,
--    with null for missing addresses
SELECT A.firstName, A.lastName, B.city, B.state
FROM Person AS A
LEFT JOIN Address AS B
ON A.personId = B.personId;


---- End solution
