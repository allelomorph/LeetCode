#include <vector>
#include <iostream>


//// Begin solution, results at https://leetcode.com/submissions/detail/696418063/


#include <algorithm>  // max

class Solution {
public:
    int maxSubArray(const std::vector<int> &nums) {
        // 1 <= nums.size() <= 10^5
        // -104 <= nums[i] <= 10^4
        int sz (nums.size());
        if (sz == 1)
            return nums[0];
        int l_st {nums[0]};       // current subarray total from start of nums
        int r_st {nums[sz - 1]};  // current subarray total from end of nums
        int max_st {std::max(l_st, r_st)};  // max subarray total
        for (int i {1}, j {sz - 2}; j >= i; ++i, --j) {
            l_st = std::max(l_st + nums[i], nums[i]);
            if (j > i)
                r_st = std::max(r_st + nums[j], nums[j]);
            max_st = std::max(std::max(l_st, r_st), max_st);
        }
        return std::max(l_st + r_st, max_st);
    }
};


//// end solution


int main() {
    std::vector<int> v1 {-2, 1 -3, 4, -1, 2, 1, -5, 4};  // 6
    std::vector<int> v2 {1};                             // 1
    std::vector<int> v3 {4, -1, -1, -1, 10};             // 11
    std::vector<int> v4 {5, 4, -1, 7, 8};                // 23
    std::vector<int> v5 {-2, 1};                         // 1
    Solution s;
    std::cout << "v1: " << s.maxSubArray(v1) << std::endl;
    std::cout << "v2: " << s.maxSubArray(v2) << std::endl;
    std::cout << "v3: " << s.maxSubArray(v3) << std::endl;
    std::cout << "v4: " << s.maxSubArray(v4) << std::endl;
    std::cout << "v5: " << s.maxSubArray(v5) << std::endl;
}
