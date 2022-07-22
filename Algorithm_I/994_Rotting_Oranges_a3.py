#!/usr/bin/python3


from typing import List


# Time to complete: 4.5 hrs

# Needed to research:
#  - queue.Queue versus collections.deque
#  - BFS via queue

#### Begin solution, results at https://leetcode.com/submissions/detail/742930718/


class Solution:
    """
    """
    # constants
    FRESH = 1
    ROTTEN = 2

    def orangesRotting(self, grid: List[List[int]]) -> int:
        """Given an m x n grid where each cell can have one of three values:
          0 representing an empty cell,
          1 representing a fresh orange, or
          2 representing a rotten orange.

        Every minute, any fresh orange that is vertically and horiziontally
        adjacent to a rotten orange becomes rotten.

        Return the minimum number of minutes that must elapse until no cell
        has a fresh orange. If this is impossible, return -1.

        """
        h = len(grid)
        w = len(grid[0])
        fresh_ct = 0
        next_to_rot = set()
        for y in range(h):
            for x in range(w):
                if grid[y][x] == self.FRESH:
                    fresh_ct += 1
                if grid[y][x] == self.ROTTEN:
                    if x + 1 < w and grid[y][x + 1] == self.FRESH:
                        next_to_rot.add((y, x + 1))  # R
                    if y - 1 >= 0 and grid[y - 1][x] == self.FRESH:
                        next_to_rot.add((y - 1, x))  # U
                    if x - 1 >= 0 and grid[y][x - 1] == self.FRESH:
                        next_to_rot.add((y, x - 1))  # L
                    if y + 1 < h and grid[y + 1][x] == self.FRESH:
                        next_to_rot.add((y + 1, x))  # D
        minutes = 0
        while len(next_to_rot):
            rotting_now = next_to_rot
            next_to_rot = set()
            for coords in rotting_now:
                y, x = coords
                grid[y][x] = self.ROTTEN
                fresh_ct -= 1
            for coords in rotting_now:
                y, x = coords
                if x + 1 < w and grid[y][x + 1] == self.FRESH:
                    next_to_rot.add((y, x + 1))  # R
                if y - 1 >= 0 and grid[y - 1][x] == self.FRESH:
                    next_to_rot.add((y - 1, x))  # U
                if x - 1 >= 0 and grid[y][x - 1] == self.FRESH:
                    next_to_rot.add((y, x - 1))  # L
                if y + 1 < h and grid[y + 1][x] == self.FRESH:
                    next_to_rot.add((y + 1, x))  # D
            minutes += 1

        return -1 if fresh_ct != 0 else minutes


#### end solution


if __name__ == '__main__':
    grid1 = [
        [2,1,1],
        [1,1,0],
        [0,1,1]
    ]

    grid2 = [
        [2,1,1],
        [0,1,1],
        [1,0,1]
    ]

    grid3 = [
        [0,2]
    ]

    grid4 = [
        [1,2]
    ]

    grid5 = [
        [2,1,1],
        [1,1,1],
        [0,1,2]
    ]

    grid6 = [
        [1,2,1,1,2,1,1]
    ]

    solution = Solution()

    print(f'solution.orangesRotting({grid1}):',
          f'{solution.orangesRotting(grid1)}')
    # 4

    print(f'solution.orangesRotting({grid2}):',
          f'{solution.orangesRotting(grid2)}')
    # -1

    print(f'solution.orangesRotting({grid3}):',
          f'{solution.orangesRotting(grid3)}')
    # 0

    print(f'solution.orangesRotting({grid4}):',
          f'{solution.orangesRotting(grid4)}')
    # 1

    print(f'solution.orangesRotting({grid5}):',
          f'{solution.orangesRotting(grid5)}')
    # 2

    print(f'solution.orangesRotting({grid6}):',
          f'{solution.orangesRotting(grid6)}')
    # 2
