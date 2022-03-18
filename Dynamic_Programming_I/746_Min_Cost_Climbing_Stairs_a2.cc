#include <vector>
#include <iostream>


//// Begin solution, results at https://leetcode.com/submissions/detail/662322750/

#include <algorithm>


// Needed to look at community discussion to find a solution after getting bogged down
//   trying to find some type of backtracking optimization for simple recursion into
//   min(cumulative cost + cost[i + 1], cumulative cost + cost[i + 2]). This solution
//   hews closest to one of my first intuitions to move backwards through cost, although
//   it builds forward while looking back.

class Solution {
public:
    int minCostClimbingStairs(std::vector<int>& cost) {
        // 2 <= cost.size() <= 1000
        int sz (cost.size());
        std::vector<int> cuml_cost (sz);
        cuml_cost[0] = cost[0];
        cuml_cost[1] = cost[1];
        for (auto i {2}; i < sz; ++i) {
            cuml_cost[i] = cost[i] +
                std::min(cuml_cost[i - 1], cuml_cost[i - 2]);
        }
        return std::min(cuml_cost[sz - 1], cuml_cost[sz - 2]);
    }
};

//// end solution

int main() {
    std::vector<int> v1 {10, 15, 20};
    std::vector<int> v2 {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    Solution s;

    std::cout << s.minCostClimbingStairs(v1) << std::endl;
    std::cout << s.minCostClimbingStairs(v2) << std::endl;
}
