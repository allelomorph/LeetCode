#include <vector>


// Needed help with this one, credit user ayanmitra2197. Could not see how to
//  handle the edge case of {2, 1, 1, 2}, as the jump could be two or three
//  indicies ahead. The key in their solution was to look backward instead.
// Adapted from dp int array to three ints, as only [i], [i - 1], and [i - 2]
//  were ever used.


//// Begin solution, results at https://leetcode.com/submissions/detail/690385520/


#include <algorithm>  // max

class Solution {
public:
    int rob(const std::vector<int> &nums) {
        // 1 <= nums.size() <= 100
        // 0 <= nums[i] <= 400
        // max possible haul: 50 * 400 (20000)
        int sz (nums.size());
        if (sz == 1)
            return nums[0];
        if (sz == 2)
            return std::max(nums[0], nums[1]);
        int ppdp {nums[0]};                    // previous previous dp, i - 2
        int pdp {std::max(nums[0], nums[1])};  // previous dp, i - 1
        int dp {};                             // at i
        for (int i {2}; i < sz; ++i) {
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
    std::vector<int> v1 {1, 2, 3, 1};          // 4
    std::vector<int> v2 {2, 7, 9, 3, 1};       // 12
    std::vector<int> v3 {2, 1, 1, 2};          // 4
    std::vector<int> v4 {2, 1, 1, 2, 0};       // 4
    std::vector<int> v5 {2, 1, 1, 2, 10};      // 13
    Solution s;

    std::cout << s.rob(v1) << std::endl;
    std::cout << s.rob(v2) << std::endl;
    std::cout << s.rob(v3) << std::endl;
    std::cout << s.rob(v4) << std::endl;
    std::cout << s.rob(v5) << std::endl;
}
