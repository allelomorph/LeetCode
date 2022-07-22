#include <iostream>
#include <vector>


template<typename T>
const std::string printableVector(std::vector<T> v) {
    std::string result;
    result.push_back('[');
    for (const auto &o: v)
        result.append(std::to_string(o) + ",");
    result.back() = ']';  // overwrite last ','
    return result;
}


// Time to complete: 5 mins

// Needed to research:

//// Begin solution, results at https://leetcode.com/submissions/detail/746497471/


class Solution {
public:
    // 1 <= nums.length <= 3 * 10^4
    // -3 * 10^4 <= nums[i] <= 3 * 10^4
    // must have linear runtime complexity
    // must use no more than constant extra space
    // (it's implied that the solution uses bitshifting somehow)
    /*
     * Given a non-empty array of integers nums, in which every element
     * appears twice except for one, returns that element.
     */
    int singleNumber(std::vector<int> &nums) {
        int result {0};
        // any value XOR itself will equal 0, so XORing all together leaves
        //   us with the singleton value
        for (const auto &n : nums)
            result ^= n;
        return result;
    }
};


//// end solution


int main() {
    std::vector<int> nums1 {2,2,1};
    // 1
    std::vector<int> nums2 {4,1,2,1,2};
    // 4
    std::vector<int> nums3 {1};
    // 1

    Solution solution;

    std::cout << "solution.singleNumber(" << printableVector(nums1) <<
        "): " << solution.singleNumber(nums1) << '\n';
    // 1

    std::cout << "solution.singleNumber(" << printableVector(nums2) <<
        "): " << solution.singleNumber(nums2) << '\n';
    // 4

    std::cout << "solution.singleNumber(" << printableVector(nums1) <<
        "): " << solution.singleNumber(nums1) << '\n';
    // 1
}
