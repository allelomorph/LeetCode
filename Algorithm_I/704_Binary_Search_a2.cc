#include <vector>
#include <iostream>


//// Begin solution, results at https://leetcode.com/submissions/detail/736186049/


class Solution {
public:
    // 1 <= nums.length <= 10^4
    // -10^4 < nums[i], target < 10^4
    // All the integers in nums are unique.
    // nums is sorted in ascending order.
    int search(const std::vector<int> &nums, int target) {
        return binarySearch(nums, 0, nums.size() - 1, target);
    }

private:
    int binarySearch(const std::vector<int> &nums, int lo_i, int hi_i,
                     int target) {
        if (lo_i == hi_i) {
            if (target == nums[lo_i])
                return lo_i;
            return -1;
        }
        int mid_i {(lo_i + hi_i) / 2};
        if (target > nums[mid_i])
            return binarySearch(nums, mid_i + 1, hi_i, target);
        else
            return binarySearch(nums, lo_i, mid_i, target);
    }
};


//// end solution


int main() {
    std::vector<int> v1 {-1,0,3,5,9,12};
    std::vector<int> v2 {5};
    std::vector<int> v3 {-1};

    Solution solution;

    std::cout << "solution.search(v1, 9): " << solution.search(v1, 9) << '\n';
    // 4
    std::cout << "solution.search(v1, 2): " << solution.search(v1, 2) << '\n';
    // -1
    std::cout << "solution.search(v2, 5): " << solution.search(v2, 5) << '\n';
    // 0
    std::cout << "solution.search(v3, 2): " << solution.search(v3, 2) << '\n';
    // -1
}
