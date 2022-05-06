#include <vector>


//// Begin solution, results at https://leetcode.com/submissions/detail/689914314/


#include <algorithm>  // min

class Solution {
public:
    int minCostClimbingStairs(const std::vector<int> &cost) {
        std::size_t sz {cost.size()};
        int prev_prev_cost {cost[0]};
        int prev_cost {cost[1]};
        int curr_cost {std::min(prev_cost, prev_prev_cost)};
        if (sz == 2)
            return curr_cost;
        for (std::size_t i {2}; i < sz - 1; ++i) {
            curr_cost = cost[i] + std::min(prev_cost, prev_prev_cost);
            prev_prev_cost = prev_cost;
            prev_cost = curr_cost;
        }
        curr_cost = cost[sz - 1] + std::min(prev_cost, prev_prev_cost);
        return std::min(curr_cost, prev_cost);
    }
};


//// end solution


#include <iostream>


int main() {
    std::vector<int> v1 {10, 15, 20};                          // 15
    std::vector<int> v2 {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};  // 6
    std::vector<int> v3 {1, 100};                              // 1
    Solution s;

    std::cout << s.minCostClimbingStairs(v1) << std::endl;
    std::cout << s.minCostClimbingStairs(v2) << std::endl;
    std::cout << s.minCostClimbingStairs(v3) << std::endl;
}
