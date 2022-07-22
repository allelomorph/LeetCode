#include <iostream>
#include <vector>


template<typename T>
const std::string PrintableVector(std::vector<T> v) {
    std::string result;
    result.push_back('[');
    for (const auto &o: v)
        result.append(std::to_string(o) + ",");
    result.back() = ']';  // overwrite last ','
    return result;
}


// Time to complete: 2.5 hrs

// Needed to research:

//// Begin solution, results at https://leetcode.com/submissions/detail/738675376/


class Solution {
    // 2 <= numbers.length <= 3 * 10^4
    // -1000 <= numbers[i] <= 1000
    // numbers is sorted in non-decreasing order.
    // -1000 <= target <= 1000
    // the tests are generated such that there is exactly one solution
public:
    std::vector<int> twoSum(const std::vector<int> &nums, const int target) {
        const int nums_sz (nums.size());
        int i {0};
        int j;
        // base is naive O(n^2), with 2 optimizations:
        //   - skip repeating values: nums is sorted, so repeats are in
        //   contiguous indices. plus, there is only one solution pair per
        //   vector, so if a value repeats once, that must be the solution,
        //   and if repeating more than once, can be ignored completely.
        //   - stop inner loop when sum is greater than target: again taking
        //   advantage of array being sorted
        for (bool found {false}; !found; ++i) {
            if (i + 1 < nums_sz && nums[i] == nums[i + 1]) {
                if (nums[i] + nums[i + 1] == target) {
                    ++i;
                    j = i + 1;
                    break;
                } else {
                    for (int repeat {nums[i]};
                         i < nums_sz && nums[i] == repeat; ++i) {}
                }
            }
            j = i + 1;
            while (j < nums_sz && nums[i] + nums[j] <= target) {
                if (j + 1 < nums_sz && nums[j] == nums[j + 1]) {
                    for (int repeat {nums[j]};
                         j < nums_sz && nums[j] == repeat; ++j) {}
                    continue;
                }
                found = (nums[i] + nums[j] == target);
                ++j;
            }
        }
        // result is one indexed
        return std::vector<int> {i, j};
    }
};


//// end solution


int main() {
    std::vector<int> v1 {2,7,11,15};
    std::vector<int> v2 {2,3,4};
    std::vector<int> v3 {-1,0};
    std::vector<int> v4 {0,0,0,0,0,2,3,4,9,9,9,9,9,9,9,9,9,9};
    std::vector<int> v5 {-20,-8,-1,0,0,2,3,4,9};
    std::vector<int> v6 {0,0,0,0,0,2,3,4,9,9,9,9,9,9,9,9,9,9,12,120};
    std::vector<int> v7 {1,3,4,4};
    std::vector<int> v8 {0,0,0,2,3,4,9,9,9,9,10,10,11};

    Solution solution;

    std::cout << "solution.twoSum(" << PrintableVector(v1) << ", 9): " <<
        PrintableVector(solution.twoSum(v1, 9)) << '\n';
    // [1,2]

    std::cout << "solution.twoSum(" << PrintableVector(v2) << ", 6): " <<
        PrintableVector(solution.twoSum(v2, 6)) << '\n';
    // [1,3]

    std::cout << "solution.twoSum(" << PrintableVector(v3) << ", -1): " <<
        PrintableVector(solution.twoSum(v3, -1)) << '\n';
    // [1,2]

    std::cout << "solution.twoSum(" << PrintableVector(v4) << ", 6): " <<
        PrintableVector(solution.twoSum(v4, 6)) << '\n';
    // [6,8]

    std::cout << "solution.twoSum(" << PrintableVector(v5) << ", 0): " <<
        PrintableVector(solution.twoSum(v5, 0)) << '\n';
    // [4,5]

    std::cout << "solution.twoSum(" << PrintableVector(v6) << ", 14): " <<
        PrintableVector(solution.twoSum(v6, 14)) << '\n';
    // [6,19]

    std::cout << "solution.twoSum(" << PrintableVector(v7) << ", 8): " <<
        PrintableVector(solution.twoSum(v7, 8)) << '\n';
    // [3,4]

    std::cout << "solution.twoSum(" << PrintableVector(v8) << ", 15): " <<
        PrintableVector(solution.twoSum(v8, 15)) << '\n';
    // [6,13]

}
