#include <vector>
#include <iostream>


//// Begin solution, results at https://leetcode.com/submissions/detail/666509501/


#include <algorithm>  // max

class Solution {
public:
    int maxSubArray(std::vector<int> &nums) {
        // 1 <= nums.length <= 10^5
        const int sz (nums.size());
        if (sz == 1)
            return nums[0];
        int Lcurr_st {nums[0]};       // current subarray total from left
        int Rcurr_st {nums[sz - 1]};  // current subarray total from right
        int max_st {std::max(Lcurr_st, Rcurr_st)};
        for (int i {1}, j {sz - 2}; j >= i; ++i, --j) {
            Lcurr_st = std::max(Lcurr_st + nums[i], nums[i]);
            if (j > i)
                Rcurr_st = std::max(Rcurr_st + nums[j], nums[j]);
            max_st = std::max(std::max(Lcurr_st, Rcurr_st), max_st);
        }
        return std::max(Lcurr_st + Rcurr_st, max_st);
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
