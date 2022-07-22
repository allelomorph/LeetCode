-- Time to complete: 5 mins

-- Needed to research:

---- Begin solution, results at https://leetcode.com/submissions/detail/752427484/


-- Reports (actor_id, director_id) for those who have collaborated at
--    least three times
WITH Collaborations AS (
    SELECT
        actor_id,
        director_id,
        COUNT(*) as collab_ct
    FROM
        ActorDirector
    GROUP BY
        actor_id,
        director_id
)

SELECT
    actor_id,
    director_id
FROM
    Collaborations
WHERE
    collab_ct >= 3;


---- End solution
