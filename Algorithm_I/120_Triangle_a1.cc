#include <iostream>
#include <vector>


template<typename T>
const std::string printableNestedVector(
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
        result.push_back(',');
    }
    if (result.back() == ',')
        result.back() = ']';
    else
        result.push_back(']');
    return result;
}


// Time to complete: 35 mins

// Needed to research:

//// Begin solution, results at https://leetcode.com/submissions/detail/744702180/


#include <algorithm>  // min


class Solution {
public:
    // 1 <= triangle.length <= 200
    // triangle[0].length == 1
    // triangle[i].length == triangle[i - 1].length + 1
    // -10^4 <= triangle[i][j] <= 10^4
    // Optional: use only O(n) extra space, where n == rows in the triangle
    int minimumTotal(const std::vector<std::vector<int>> &triangle) {
        /*
         * Given a triangle array, returns the minimum sum of cell values in
         * a path taken from top to bottom of the triangle, with valid steps
         * in path being [i][j] to [i + 1][j] or [i + 1][j + 1].
         */
        const int t_sz (triangle.size());
        if (t_sz == 1)
            return triangle[0][0];
        std::vector<std::vector<int>> dp {triangle};
        for (int i {t_sz - 2}; i >= 0; --i) {
            for (int j {0}; j < i + 1; ++j) {
                dp[i][j] = std::min(
                    dp[i][j] + dp[i + 1][j],
                    dp[i][j] + dp[i + 1][j + 1]);
            }
        }
        return dp[0][0];
    }
};


//// end solution


int main() {
    std::vector<std::vector<int>> t1 {
        {2},
        {3,4},
        {6,5,7},
        {4,1,8,3}
    };
    std::vector<std::vector<int>> t2 {
        {-10}
    };

    Solution solution;

    std::cout << "solution.minimumTotal(" << printableNestedVector(t1) <<
        "): " << solution.minimumTotal(t1) << '\n';
    // 11

    std::cout << "solution.minimumTotal(" << printableNestedVector(t2) <<
        "): " << solution.minimumTotal(t2) << '\n';
    // -10
}
