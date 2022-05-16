#include <vector>
#include <iostream>


//// Begin solution, results at https://leetcode.com/submissions/detail/698879454/


#include <algorithm>  // max


class Solution {
public:
    int getMaxLen(const std::vector<int> &nums) {
        // 1 <= nums.size() <= 10^5
        // -10^9 <= nums[i] <= 10^9
        int n (nums.size());
                                    // -1 index values are sentinels meaning "unset"
        int beg_i {-1};             // candidate subarray start index
        int f_neg_i {-1};           // index of first negative value in candiate subarray
        int l_neg_i {-1};           // index of last negative value in candiate subarray
        int neg_ct {};              // count of negative values in candidate subarray
        int max_sl {};              // max subarray length
        for (int i {}; i < n; ++i) {
            if (nums[i] == 0) {
                if (beg_i != -1) {
                    max_sl = std::max(max_sl,
                                      MaxPosSubarray(beg_i, i - 1, f_neg_i,
                                                     l_neg_i, neg_ct));
                }
                beg_i = f_neg_i = l_neg_i = -1;
                neg_ct = 0;
                continue;
            }
            if (beg_i == -1)
                beg_i = i;
            if (nums[i] < 0) {
                ++neg_ct;
                if (f_neg_i == -1)
                    f_neg_i = i;
                l_neg_i = i;
            }
        }
        if (beg_i != -1) {
            max_sl = std::max(max_sl,
                              MaxPosSubarray(beg_i, n - 1, f_neg_i,
                                             l_neg_i, neg_ct));
        }
        return max_sl;
    }
private:
    int MaxPosSubarray(const int beg_i, const int end_i,
                       const int f_neg_i, const int l_neg_i,
                       const int neg_ct) {
        if (neg_ct % 2 == 0)
            return end_i + 1 - beg_i;
        return std::max(l_neg_i - beg_i, end_i - f_neg_i);
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
    Solution s;

    std::cout << "v1: " << s.getMaxLen(v1) << std::endl;
    std::cout << "v2: " << s.getMaxLen(v2) << std::endl;
    std::cout << "v3: " << s.getMaxLen(v3) << std::endl;
    std::cout << "v4: " << s.getMaxLen(v4) << std::endl;
    std::cout << "v5: " << s.getMaxLen(v5) << std::endl;
}
