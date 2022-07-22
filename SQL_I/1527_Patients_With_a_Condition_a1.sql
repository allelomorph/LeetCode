-- Time to complete: 25 mins

-- Treated as: study problem (research allowed)

-- Needed to research:
--   - REGEXP
--   - regex non-capture groups

---- Begin solution, results at https://leetcode.com/submissions/detail/748260294/


-- Retrieves id, name, and all conditions of patients who have Type I Diabetes
-- LEFT returns null on null input
SELECT patient_id, patient_name, conditions
FROM Patients
WHERE conditions REGEXP '(?:^| +)DIAB1';


---- End solution
