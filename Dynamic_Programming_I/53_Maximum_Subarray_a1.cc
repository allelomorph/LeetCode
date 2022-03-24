#include <vector>
#include <iostream>


//// Begin solution, results at https://leetcode.com/submissions/detail/666486338/


class Solution {
public:
    int maxSubArray(std::vector<int> &nums) {
        // 1 <= nums.length <= 10^5
        const int sz (nums.size());
        if (sz == 1)
            return nums[0];
        int curr_st {nums[0]};  // current subarray total
        int max_st {curr_st};   // maximum subarray total
        for (int i {1}; i < sz; ++i) {
            if (curr_st + nums[i] < nums[i])
                curr_st = nums[i];
            else
                curr_st += nums[i];
            if (curr_st > max_st)
                max_st = curr_st;
        }
        return max_st;
    }
};


//// end solution


int main() {
    std::vector<int> v1 {-2, 1 -3, 4, -1, 2, 1, -5, 4};  // 6
    std::vector<int> v2 {1};                             // 1
    std::vector<int> v3 {4, -1, -1, -1, 10};             // 11
    Solution s;
    std::cout << "v1: " << s.maxSubArray(v1) << std::endl;
    std::cout << "v2: " << s.maxSubArray(v2) << std::endl;
    std::cout << "v3: " << s.maxSubArray(v3) << std::endl;
}
