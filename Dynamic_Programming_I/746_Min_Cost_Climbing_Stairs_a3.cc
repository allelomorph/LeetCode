#include <vector>


//// Begin solution, results at https://leetcode.com/submissions/detail/689878935/


#include <algorithm>  // min

class Solution {
public:
    int minCostClimbingStairs(const std::vector<int> &cost) {
        std::size_t sz {cost.size()};
        dp[0] = cost[0];
        dp[1] = cost[1];
        for (std::size_t i {2}; i < sz; ++i) {
            dp[i] = cost[i] + std::min(dp[i - 1], dp[i - 2]);
        }
        return std::min(dp[sz - 1], dp[sz - 2]);
    }
private:
    // 2 <= cost.size() <= 1000
    // 0 <= cost[i] <= 999
    // max total cost = 500 * 999 = 499,500 (fits in 32 bit int)
    static constexpr int dp_sz {1000};
    static int dp[dp_sz];
};


int Solution::dp[Solution::dp_sz] {};


//// end solution


#include <iostream>


int main() {
    std::vector<int> v1 {10, 15, 20};
    std::vector<int> v2 {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    Solution s;

    std::cout << s.minCostClimbingStairs(v1) << std::endl;
    std::cout << s.minCostClimbingStairs(v2) << std::endl;
}
