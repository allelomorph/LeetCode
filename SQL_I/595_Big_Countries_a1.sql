-- Time to complete: 5 mins

-- Treated as: study problem (research allowed)

-- Needed to research:

-- Note: Poor speed performance, at only 10.62 percentile - how to improve?

---- Begin solution, results at https://leetcode.com/submissions/detail/747269507/


-- Retreive countries defined as "large" by either area or population.
SELECT name, population, area FROM World
    WHERE World.area >= 3000000 OR World.population >= 25000000;


---- End solution
