#include <vector>
#include <iostream>


//// Begin solution, results at https://leetcode.com/submissions/detail/666028718/


class Solution {
public:
    int jump(std::vector<int> &nums) {
        // 1 <= nums.length <= 10^4
        const int sz (nums.size());
        if (sz == 1) return 0;
        if (sz == 2) return 1;
        std::vector<int> dp (sz, 0);
        dp[1] = 1;
        for (int i {0}, j; i < sz; ++i) {
            j = i + 1;
            for (int jump_max {nums[i]}; j < sz && j - i <= jump_max; ++j) {
                if (!dp[j] || dp[j] > dp[i] + 1)
                    dp[j] = dp[i] + 1;
            }
            // Was previous jump max sufficient to reach last index?
            if (j == sz)
                break;
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
    // std::vector<int> v5 {5, 6, 4, 4, 6, 9, 4, 4, 7, 4, 4, 8, 2, 6, 8, 1, 5, 9,
    //                      6, 5, 2, 7, 9, 7, 9, 6, 9, 4, 1, 6, 8, 8, 4, 4, 2, 0,
    //                      3, 8, 5};
    std::vector<int> v6 {1, 2};              // 1
    std::vector<int> v7 {3, 2, 1};           // 1
    std::vector<int> v8 {1, 2, 1, 1, 1};     // 4
    Solution s;
    std::cout << "v1: " << s.jump(v1) << std::endl;
    std::cout << "v2: " << s.jump(v2) << std::endl;
    std::cout << "v3: " << s.jump(v3) << std::endl;
    std::cout << "v4: " << s.jump(v4) << std::endl;
//    std::cout << "v5: " << s.jump(v5) << std::endl;
    std::cout << "v6: " << s.jump(v6) << std::endl;
    std::cout << "v7: " << s.jump(v7) << std::endl;
    std::cout << "v8: " << s.jump(v8) << std::endl;
}
