#include <iostream>
#include <vector>


template<typename T>
const std::string PrintableNestedVector(
    const std::vector<std::vector<T>> &nv) {
    std::string result;
    result.push_back('[');
    for (const auto &v: nv) {
        result.push_back('[');
        for (const auto &o: v) {
            result.append(std::to_string(o) + ",");
        }
            if (result.back() == ',')
                result.back() = ']';
            else
                result.push_back(']');
    }
    if (result.back() == ',')
        result.back() = ']';
    else
        result.push_back(']');
    return result;
}


// Time to complete: 30 mins to refactor a1.cc, which was accepted but slow

// Needed to research:

//// Begin solution, results at https://leetcode.com/submissions/detail/741368387/


class Solution {
public:
    // m == grid.length
    // n == grid[i].length
    // 1 <= m, n <= 50
    // grid[i][j] is either 0 or 1.
    int maxAreaOfIsland(const std::vector<std::vector<int>> &grid) {
        // Given an m by n binary matrix grid, consider an "island" a group of
        // 1s contiguous in 4 directions (horizontally and vertically.) 0s are
        // "water," and assume all four edges of the grid are assumed surrounded
        // by water.
        //
        // The area of an island is the number of cells with a value 1 in the
        // island.
        //
        // Returns the maximum area of an island in grid. If there are no
        // islands, returns 0.
        const int h (grid.size());
        const int w (grid[0].size());
        std::vector<std::vector<bool>> visited;
        for (int i {0}; i < h; ++i) {
            visited.push_back(std::vector<bool> {});
            for (int j {0}; j < w; ++j) {
                visited[i].push_back(false);
            }
        }
        unsigned int max_island_area {0};
        for (int y {0}; y < h; ++y) {
            for (int x {0}; x < w; ++x) {
                if (grid[y][x] == 1 && !visited[y][x]) {
                    // check to see if already recorded
                    unsigned int area {0};
                    chartIsland(grid, visited, area, y, x, h, w);
                    max_island_area = std::max(max_island_area, area);
                }
            }
        }
        return max_island_area;
    }
private:
    void chartIsland(const std::vector<std::vector<int>> &grid,
                     std::vector<std::vector<bool>> &visited,
                     unsigned int &area,
                     const int y, const int x, const int &h, const int &w) {
        if (y < 0 || x < 0 || y >= h || x >= w)
            return;   // out of bounds
        if (grid[y][x] == 0 || visited[y][x])
            return;
        visited[y][x] = true;
        ++area;
        chartIsland(grid, visited, area, y - 1, x, h, w);  // up
        chartIsland(grid, visited, area, y + 1, x, h, w);  // down
        chartIsland(grid, visited, area, y, x - 1, h, w);  // left
        chartIsland(grid, visited, area, y, x + 1, h, w);  // right
    }
};


//// end solution


int main() {
    const std::vector<std::vector<int>> grid1 {
        // 1 2 3 4 5 6 7 8 9101112
        {0,0,1,0,0,0,0,1,0,0,0,0,0}, // 0
        {0,0,0,0,0,0,0,1,1,1,0,0,0}, // 1
        {0,1,1,0,1,0,0,0,0,0,0,0,0}, // 2
        {0,1,0,0,1,1,0,0,1,0,1,0,0}, // 3
        {0,1,0,0,1,1,0,0,1,1,1,0,0}, // 4
        {0,0,0,0,0,0,0,0,0,0,1,0,0}, // 5
        {0,0,0,0,0,0,0,1,1,1,0,0,0}, // 6
        {0,0,0,0,0,0,0,1,1,0,0,0,0}  // 7
    };

    const std::vector<std::vector<int>>grid2 {
        {0,0,0,0,0,0,0,0}
    };

    Solution solution;


    std::cout << "solution.maxAreaOfIsland(" << PrintableNestedVector(grid1) <<
        "): " << solution.maxAreaOfIsland(grid1) << '\n';
    // 6 [(, ), (, ), (, ), (, ), (, ), (, )]

    std::cout << "solution.maxAreaOfIsland(" << PrintableNestedVector(grid2) <<
        "): " << solution.maxAreaOfIsland(grid2) << '\n';
    // 0
}
