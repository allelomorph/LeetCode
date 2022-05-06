#include <vector>


//// Begin solution, results at https://leetcode.com/submissions/detail/694006106/


#include <algorithm>  // max


class Solution {
public:
    int rob(const std::vector<int> &nums) {
        // 1 <= nums.size() <= 100
        // 0 <= nums[i] <= 1000
        int sz (nums.size());
        if (sz == 1)
            return nums[0];
        if (sz == 2)
            return std::max(nums[0], nums[1]);
        return std::max(RobRange(nums, 0, sz - 1),
                        RobRange(nums, 1, sz));
    }
private:
    int RobRange(const std::vector<int> &nums,
                 const int beg_i, const int end_i) {
        // 3 <= nums.size() <= 100
        // 0 <= nums[i] <= 1000
        // 0 <= beg_i <= nums.size()
        // nums.size() - 1 <= end_i <= nums.size()
        int ppdp {nums[beg_i]};                            // previous previous dp, i - 2
        int pdp {std::max(nums[beg_i], nums[beg_i + 1])};  // previous dp, i - 1
        int dp {pdp};                                      // at i (loop not entered for sz == 3)
        for (int i {beg_i + 2}; i < end_i; ++i) {
            dp = std::max(nums[i] + ppdp, pdp);
            ppdp = pdp;
            pdp = dp;
        }
        return dp;
    }
};



//// end solution


#include <iostream>


int main() {
    std::vector<int> v1 {2, 3, 2};          // 3
    std::vector<int> v2 {1, 2, 3, 1};       // 4
    std::vector<int> v3 {1, 2, 3};          // 3 (can only take from index 2)
    Solution s;

    std::cout << s.rob(v1) << std::endl;
    std::cout << s.rob(v2) << std::endl;
    std::cout << s.rob(v3) << std::endl;
}
