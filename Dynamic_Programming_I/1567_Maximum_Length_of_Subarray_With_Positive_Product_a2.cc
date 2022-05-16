#include <vector>
#include <iostream>


//// Begin solution, results at https://leetcode.com/submissions/detail/698383683/


#include <algorithm>  // max


struct SubarrayProductStats {
    int  ss_len;  // current length of local positive subarray, resetting when sign changes
    int  ls_len;  // current length of ongoing subarray not containing any 0 values
    int max_len;  // max length of any subarray with positive product
    bool ss_neg;  // short subarray candidate product is currently negative
    bool ls_neg;  // long subarray candidate product is currently negative
};

using Stats = struct SubarrayProductStats;


class Solution {
public:
    int getMaxLen(const std::vector<int> &nums) {
        // 1 <= nums.size() <= 10^5
        // -10^9 <= nums[i] <= 10^9
        int n (nums.size());
        if (n == 1)
            return int (nums[0] > 0);
        Stats l { (nums[0] != 0), (nums[0] != 0), (nums[0] != 0),
                  nums[0] < 0, nums[0] < 0
        };  // subarray stats for forward traversal
        Stats r {(nums[n - 1] != 0), (nums[n - 1] != 0), (nums[n - 1] != 0),
                  nums[n - 1] < 0, nums[n - 1] < 0
        };  // subarray stats for backward traversal
        for (int i {1}, j {n - 2}; i < n; ++i, --j) {
            UpdateSubarrayStats(&l, nums[i]);
            UpdateSubarrayStats(&r, nums[j]);
        }
        return std::max(l.max_len, r.max_len);
    }
private:
    void UpdateSubarrayStats(Stats *s, int arr_memb) {
        if (!s)
            return;
        if (arr_memb == 0) {
            s->ss_neg = false;
            s->ls_neg = false;
            s->ss_len = 0;
            s->ls_len = 0;
        } else if (arr_memb < 0) {
            ++(s->ls_len);
            s->ls_neg = !(s->ls_neg);
            s->ss_len = s->ss_neg ? s->ss_len + 1 : 1;
            s->ss_neg = !(s->ss_neg);
        } else {  // pos
            ++(s->ls_len);
            s->ss_len = s->ss_neg ? 1 : s->ss_len + 1;
        }
        if (!(s->ss_neg))
            s->max_len = std::max(s->ss_len, s->max_len);
        if (!(s->ls_neg))
            s->max_len = std::max(s->ls_len, s->max_len);
    }
};

//// end solution


int main() {
    std::vector<int> v1 {1, -2, -3, 4};            // 4
    std::vector<int> v2 {0, 1, -2, -3, -4};        // 3
    std::vector<int> v3 {-1, -2, -3, 0, 1};        // 2
    std::vector<int> v4 {-1, 2};                   // 1
    std::vector<int> v5 {5, -20, -20, -39, -5, 0, 0, 0, 36, -32,
                         0, -7, -10, -7, 21, 20, -12, -34, 26, 2};  // 8
    // std::vector<int> v6 {-2, 3, 1, 1, 1, -4};      // 24
    // std::vector<int> v7 {-2, 3, 1, 0, 1, -4};      // 3
    // std::vector<int> v8 {-2, 3, -4, 0, 5, 5};      // 25
    // std::vector<int> v9 {1, 0, -1, 2, 3, -5, -2};  // 60

    Solution s;

    std::cout << "v1: " << s.getMaxLen(v1) << std::endl;
    std::cout << "v2: " << s.getMaxLen(v2) << std::endl;
    std::cout << "v3: " << s.getMaxLen(v3) << std::endl;
    std::cout << "v4: " << s.getMaxLen(v4) << std::endl;
    std::cout << "v5: " << s.getMaxLen(v5) << std::endl;
    // std::cout << "v6: " << s.getMaxLen(v6) << std::endl;
    // std::cout << "v7: " << s.getMaxLen(v7) << std::endl;
    // std::cout << "v8: " << s.getMaxLen(v8) << std::endl;
    // std::cout << "v9: " << s.getMaxLen(v9) << std::endl;
}
