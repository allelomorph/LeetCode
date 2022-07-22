#include <iostream>
#include <vector>


//// Begin solution, results at https://leetcode.com/submissions/detail/736219876/


class Solution {
    // 1 <= nums.length <= 10^4
    // -10^4 <= nums[i] <= 10^4
    // nums contains unique values sorted in ascending order.
    // -10^4 <= target <= 10^4
    // must write an algorithm with O(log n) runtime complexity
public:
    int searchInsert(const std::vector<int> &nums, int target) {
        // As with problem #278, can be similar to a non-recursive
        //   binary search
        int lo {0};
        int hi (nums.size() - 1);
        // leveraging limited size of ints in nums to use simpler
        //   calculation of mid, otherwise lo + ((hi - lo) / 2) to
        //   avoid overflow
        int mid;
        while (lo <= hi) {
            mid = (lo + hi) / 2;
            if (target == nums[mid])
                return mid;
            if (target < nums[mid]) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return (target < nums[mid]) ? mid : mid + 1;
    }
};


//// end solution

int main() {
    std::vector<int> v1 {1,3,5,6};

    Solution solution;

    std::cout << "solution.searchInsert(v1, 5): " <<
        solution.searchInsert(v1, 5) << '\n';
    // 2
    std::cout << "solution.searchInsert(v1, 2): " <<
        solution.searchInsert(v1, 2) << '\n';
    // 1
    std::cout << "solution.searchInsert(v1, 7): " <<
        solution.searchInsert(v1, 7) << '\n';
    // 4
    std::cout << "solution.searchInsert(v1, 0): " <<
        solution.searchInsert(v1, 0) << '\n';
    // 0
}
