-- Time to complete: 2 hrs

-- Treated as: study problem (research allowed)

-- Needed to research:

---- Begin solution, results at https://leetcode.com/submissions/detail/749098231/


-- Returns a descriptive label for every "node" in a database representation
--    of a binary tree:
--   - 'Root' if no parents
--   - 'Inner' if 1 or 2 children
--   - 'Leaf' if 0 children
(
    -- any node ids listed at least once as p_id + root as (id, null)
    SELECT IF (p_id IS NULL, id, p_id) AS id,
        IF(p_id IS NULL, 'Root', 'Inner') AS type
    FROM Tree
    WHERE p_id IS NULL OR p_id != (
        SELECT id from Tree
        WHERE p_id IS NULL
    )
    GROUP BY p_id
    ORDER BY p_id ASC
) UNION (
    -- all node ids never listed as p_ids (aside from root)
    SELECT A.id, 'Leaf' AS type FROM Tree AS A
    LEFT JOIN (
        SELECT p_id AS id FROM Tree
        GROUP BY p_id
        ORDER BY p_id
    ) AS B
    ON A.id = B.id
    WHERE A.p_id IS NOT NULL AND B.id IS NULL
    ORDER BY A.id ASC
);


---- End solution
