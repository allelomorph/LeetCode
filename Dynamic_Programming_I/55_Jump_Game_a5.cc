#include <vector>
#include <iostream>
#include <iomanip>  // boolalpha


//// Begin solution, results at https://leetcode.com/submissions/detail/694394841/


#include <algorithm>  // max


class Solution {
public:
    bool canJump(const std::vector<int> &nums) {
        // 1 <= nums.size() <= 104
        // 0 <= nums[i] <= 105
        const int sz (nums.size());
        int dp {0};  // maximum reachable index
        for (auto i {0}; i < sz && i <= dp; ++i) {
            dp = std::max(dp, i + nums[i]);
        }
        return (dp >= sz - 1);
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
