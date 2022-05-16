#include <vector>
#include <iostream>


//// Begin solution, results at https://leetcode.com/submissions/detail/698301773/


#include <algorithm>  // max, max_element
#include <array>


class Solution {
public:
    int maxProduct(std::vector<int> &nums) {
        // 1 <= nums.size() <= 2 * 10^4
        // -10 <= nums[i] <= 10
        // The product of any prefix or suffix of nums is guaranteed to fit in
        //   a 32-bit integer
        int n (nums.size());
        if (n == 1)
            return nums[0];
        enum MaxArrIndex {
            L_K_SP,   // Kadane subarray product from left
            L_C_SP,   // Cumulative product from left, resets after nums[i] == 0
            R_K_SP,   // Kadane subarray product from right
            R_C_SP,   // Cumulative product from right resets after nums[i] == 0
            MAX_SP,   // Overall maximum subarray product
            MAX_ARR_SZ
        };
        std::array<int, MAX_ARR_SZ> dp { { nums[0], nums[0],
                                           nums[n - 1], nums[n - 1],
                                           std::max(nums[0], nums[n - 1]) }
        };
        for (int i {1}, j {n - 2}; i < n; ++i, --j) {
            dp[L_K_SP] = std::max(dp[L_K_SP] * nums[i], nums[i]);
            dp[L_C_SP] = dp[L_C_SP] ? dp[L_C_SP] * nums[i] : nums[i];
            dp[R_K_SP] = std::max(dp[R_K_SP] * nums[j], nums[j]);
            dp[R_C_SP] = dp[R_C_SP] ? dp[R_C_SP] * nums[j] : nums[j];
            dp[MAX_SP] = *std::max_element(dp.begin(), dp.end());
        }
        return dp[MAX_SP];
    }
};


//// end solution


int main() {
    std::vector<int> v1 {2, 3, -2, 4};             // 6
    std::vector<int> v2 {-2, 0, -1};               // 0
    std::vector<int> v3 {-2, 3, -4};               // 24
    std::vector<int> v4 {-1, -2, -3};              // 6, own example
    std::vector<int> v5 {0, 0, 1, 0, 2};           // 2, own example
    std::vector<int> v6 {-2, 3, 1, 1, 1, -4};      // 24
    std::vector<int> v7 {-2, 3, 1, 0, 1, -4};      // 3
    std::vector<int> v8 {-2, 3, -4, 0, 5, 5};      // 25
    std::vector<int> v9 {1, 0, -1, 2, 3, -5, -2};  // 60

    Solution s;

    std::cout << "v1: " << s.maxProduct(v1) << std::endl;
    std::cout << "v2: " << s.maxProduct(v2) << std::endl;
    std::cout << "v3: " << s.maxProduct(v3) << std::endl;
    std::cout << "v4: " << s.maxProduct(v4) << std::endl;
    std::cout << "v5: " << s.maxProduct(v5) << std::endl;
    std::cout << "v6: " << s.maxProduct(v6) << std::endl;
    std::cout << "v7: " << s.maxProduct(v7) << std::endl;
    std::cout << "v8: " << s.maxProduct(v8) << std::endl;
    std::cout << "v9: " << s.maxProduct(v9) << std::endl;
}
