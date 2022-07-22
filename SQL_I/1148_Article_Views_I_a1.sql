-- Time to complete: 5 mins

-- Needed to research:

---- Begin solution, results at https://leetcode.com/submissions/detail/749865664/


-- Retrieve all authors that viewed at least one of their own articles
SELECT DISTINCT author_id AS id FROM Views
WHERE author_id = viewer_id
ORDER BY id ASC;


---- End solution
