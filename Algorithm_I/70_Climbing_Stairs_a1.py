#!/usr/bin/python3


# Time to complete: 15 mins

# Needed to research:

# Note: already solved in C++ as part of Dynamic Programming I study plan

#### Begin solution, results at https://leetcode.com/submissions/detail/744701487/


class Solution:
    """
    """
    # 1 <= n <= 45
    __MAX_N = 45
    __dp = ()

    def climbStairs(self, n: int) -> int:
        """If climbing a staircase of n steps in increments of only 1 or 2
        steps, returns the number of distinct ways one can climb to the top.

        """
        # It was observed on previous attempts that when manually checking
        #   climbing methods up to n == 8, the result was always the fibonacci
        #   number for n + 1. Since submitting this problem to LeetCode's
        #   checker, this seems supported up to n == 45 as well, although
        #   I do not yet understand the correlation.
        return self.__dp[n + 1]

    def __init__(self):
        f = [0, 1]
        for i in range(self.__MAX_N):
            f.append(f[-1] + f[-2])
        self.__dp = tuple(f)


#### end solution


if __name__ == '__main__':
    n1 = 2
    n2 = 3

    solution = Solution()

    print(f'solution.climbStairs({n1}):',
          f'{solution.climbStairs(n1)}')
    # 2
    # Methods: 1. 1 step + 1 step
    #          2. 2 steps

    print(f'solution.climbStairs({n2}):',
          f'{solution.climbStairs(n2)}')
    # 3
    # Methods: 1. 1 step + 1 step + 1 step
    #          2. 1 step + 2 steps
    #          3. 2 steps + 1 step
