#include <vector>
#include <iostream>


//// Begin solution, results at https://leetcode.com/submissions/detail/694463873/


#include <algorithm>  // min
#include <limits>


class Solution {
public:
    int jump(const std::vector<int> &nums) {
        // 1 <= nums.size() <= 10^4
        // 0 <= nums[i] <= 1000
        const int sz (nums.size());
        if (sz == 1) return 0;
        std::vector<int> dp (sz, std::numeric_limits<int>::max());
        dp[0] = 0;
        for (int i {}, j {}; i < sz && j < sz; ++i) {
            for (j = i + 1; j < sz && j - i <= nums[i]; ++j) {
                dp[j] = std::min(dp[j], dp[i] + 1);
            }
        }
        return dp[sz - 1];
    }
};


//// end solution


int main() {
    std::vector<int> v1 {0};                 // 0
    std::vector<int> v2 {2, 3, 1, 1, 4};     // 2
    std::vector<int> v3 {2, 3, 0, 1, 4};     // 2
    std::vector<int> v4 {1, 2, 3};           // 2
    std::vector<int> v5 {2, 3, 1};           // 1
    std::vector<int> v6 {1, 2, 1, 1, 1};     // 3
    std::vector<int> v7 {7,0,9,6,9,6,1,7,9,0,1,2,9,0,3};  // 2
    Solution s;

    std::cout << "v1: " << s.jump(v1) << std::endl;
    std::cout << "v15: " << s.jump(v15) << std::endl;
    std::cout << "v2: " << s.jump(v2) << std::endl;
    std::cout << "v3: " << s.jump(v3) << std::endl;
    std::cout << "v4: " << s.jump(v4) << std::endl;
    std::cout << "v5: " << s.jump(v5) << std::endl;
    std::cout << "v6: " << s.jump(v6) << std::endl;
    std::cout << "v7: " << s.jump(v7) << std::endl;
}
