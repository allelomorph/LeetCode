#include <vector>
#include <iostream>


//// Begin solution, results at https://leetcode.com/submissions/detail/697099977/


#include <algorithm>  // max, min


class Solution {
public:
    int maxSubarraySumCircular(std::vector<int> &nums) {
        // n == nums.length
        // 1 <= n <= 3 * 104
        int n (nums.size());
        if (n == 1)
            return nums[0];
        // Can work with a circular array by considering indices 0 through
        //   (2n)-2, within which all possible subarrays of up to n members
        //   can be found.
        // Conceptually simplest solution is looping once through nums, running
        //   a maxSubarraySum subroutine for the next n members in a circular
        //   traversal, and then taking the max of those n maximums. This
        //   however is potentially O(n^2) in time.
        // For an O(n) time solution, research shows that there are few ready
        //   alternatives to Kadane's algorithm.
        int max_st {nums[0]};   // overall maxmium subarray total
        int min_st {nums[0]};   // overall minimum subarray total
        int sum {nums[0]};      // sum of all members
        // Using single traversal to take max, min, and sum
        for (int i {1}, curr_max_st {nums[0]}, curr_min_st {nums[0]};
             i < n; ++i) {
            curr_max_st = std::max(nums[i], curr_max_st + nums[i]);
            max_st = std::max(curr_max_st, max_st);
            curr_min_st = std::min(nums[i], curr_min_st + nums[i]);
            min_st = std::min(curr_min_st, min_st);
            sum += nums[i];
        }
        // Only edge case where max > sum - min:
        if (max_st < 0 && sum == min_st)
            return max_st;
        // Normal conclusion to Kadane's algo
        return std::max(max_st, sum - min_st);
    }
};

//// end solution


int main() {
    std::vector<int> v1 {1, -2, 3, -2};     // 3
    std::vector<int> v2 {5, -3, 5};         // 10
    std::vector<int> v3 {-3, -2, -3};       // -2
    std::vector<int> v4 {3, 1, 3, 2, 6};    // 15
    std::vector<int> v5 {0, 5, 8, -9, 9, -7, 3, -2};    // 16
    Solution s;

    std::cout << "v1: " << s.maxSubarraySumCircular(v1) << std::endl;
    std::cout << "v2: " << s.maxSubarraySumCircular(v2) << std::endl;
    std::cout << "v3: " << s.maxSubarraySumCircular(v3) << std::endl;
    std::cout << "v4: " << s.maxSubarraySumCircular(v4) << std::endl;
    std::cout << "v5: " << s.maxSubarraySumCircular(v5) << std::endl;
}
