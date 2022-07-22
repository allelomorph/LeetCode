#!/usr/bin/python3


from typing import List


# Time to complete: 5.5 hrs

# Needed to research:

# Note: decent speed, but only in 5.83 percentile for space. Any way to improve?

#### Begin solution, results at https://leetcode.com/submissions/detail/743002479/


from copy import deepcopy


class Solution:
    """
    """
    # m == mat.length
    # n == mat[i].length
    # 1 <= m, n <= 10^4
    # 1 <= m * n <= 10^4
    # mat[i][j] is either 0 or 1
    # there is at least one 0 in mat
    # (?) can we assume at least one 0 per row/col?
    def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:
        """Given a m x n binary matrix mat, returns the distance of the
        nearest 0 for each cell.

        The distance between two adjacent cells is 1.

        """
        h = len(mat)
        w = len(mat[0])
        result = deepcopy(mat)  # can we just modify mat to save space?
        next_edge = set()
        # find set of cells at boundary between 0 fill and 1 fill,
        #   and mark interior of boundary as -1
        for y in range(h):
            for x in range(w):
                if result[y][x] == 1:
                    # if bordered by 0 cell:
                    if any([x + 1 < w  and result[y][x + 1] == 0,
                            y - 1 >= 0 and result[y - 1][x] == 0,
                            x - 1 >= 0 and result[y][x - 1] == 0,
                            y + 1 < h  and result[y + 1][x] == 0]):
                        next_edge.add((y, x))
                    else:
                        result[y][x] = -1
        i = 1
        # set of cells i units away from nearest 0
        edge_cells = set()
        while len(next_edge):
            edge_cells = next_edge
            next_edge = set()
            for cell in edge_cells:
                y, x = cell
                if x + 1 < w  and result[y][x + 1] == -1:  # R
                    next_edge.add((y, x + 1))
                    result[y][x + 1] = i + 1
                if y - 1 >= 0 and result[y - 1][x] == -1:  # U
                    next_edge.add((y - 1, x))
                    result[y - 1][x] = i + 1
                if x - 1 >= 0 and result[y][x - 1] == -1:  # L
                    next_edge.add((y, x - 1))
                    result[y][x - 1] = i + 1
                if y + 1 < h  and result[y + 1][x] == -1:  # D
                    next_edge.add((y + 1, x))
                    result[y + 1][x] = i + 1
            i += 1
        return result


#### end solution


if __name__ == '__main__':
    mat1 = [
        [0,0,0],
        [0,1,0],
        [0,0,0]
    ]

    mat2 = [
        [0,0,0],
        [0,1,0],
        [1,1,1]
    ]

    mat3 = [
        [0,1,0],
        [0,1,0],
        [1,1,1]
    ]

    mat4 = [
        [0,0,0,0,0,0],
        [0,1,1,1,1,0],
        [0,1,1,1,1,0],
        [0,1,1,1,1,0],
        [0,0,0,0,0,0]
    ]

    mat5 = [
        [0]
    ]

    mat6 = [
        [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0]
    ]

    solution = Solution()

    print(f'solution.updateMatrix({mat1}):',
          f'{solution.updateMatrix(mat1)}')
    # [[0,0,0],[0,1,0],[0,0,0]]

    print(f'solution.updateMatrix({mat2}):',
          f'{solution.updateMatrix(mat2)}')
    # [[0,0,0],[0,1,0],[1,2,1]]

    # Nothing in problem description about full rows/columns of 1s:
    print(f'solution.updateMatrix({mat3}):',
          f'{solution.updateMatrix(mat3)}')
    # [[0,1,0],[0,1,0],[1,2,1]]

    print(f'solution.updateMatrix({mat4}):',
          f'{solution.updateMatrix(mat4)}')
    # [[0,0,0,0,0,0], [0,1,1,1,1,0], [0,1,2,2,1,0], [0,1,1,1,1,0], [0,0,0,0,0,0]]

    print(f'solution.updateMatrix({mat5}):',
          f'{solution.updateMatrix(mat5)}')
    # [[0]]

    print(f'solution.updateMatrix({mat6}):',
          f'{solution.updateMatrix(mat6)}')
    # [[59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42,
    #   41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24,
    #   23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5,
    #   4, 3, 2, 1, 0]]
