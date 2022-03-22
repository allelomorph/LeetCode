#include <vector>
#include <iostream>
#include <iomanip>  // boolalpha


//// Begin solution, results at https://leetcode.com/submissions/detail/664702001/


class Solution {
public:
    bool canJump(std::vector<int> &nums) {
        const int sz (nums.size());
        // 1 <= nums.length <= 10^4
        std::vector<bool> dp (sz, false);
        dp[0] = true;
        for (auto i {0}; i < sz && dp[i]; ++i) {
            if (nums[i] >= sz - 1 - i)
                return true;
            for (auto j {0}; j < nums[i]; ++j)
                dp[i + 1 + j] = true;
        }
        return dp[sz - 1];
    }
};


//// end solution


int main() {
    std::vector<int> v1 {0};                 // true
    std::vector<int> v2 {2, 3, 1, 1, 4};     // true
    std::vector<int> v3 {3, 2, 1, 0, 4};     // false
    std::vector<int> v4 {2, 0, 0};           // true
    Solution s;
    std::cout << "v1: " << std::boolalpha << s.canJump(v1) << std::endl;
    std::cout << "v2: " << s.canJump(v2) << std::endl;
    std::cout << "v3: " << s.canJump(v3) << std::endl;
    std::cout << "v4: " << s.canJump(v4) << std::endl;
}
