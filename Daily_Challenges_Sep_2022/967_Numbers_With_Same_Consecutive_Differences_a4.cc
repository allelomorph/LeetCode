#include <iostream>
#include <vector>


template<typename T>
const std::string printableVector(std::vector<T> v) {
    std::string result;
    result.push_back('[');
    for (const auto &o: v)
        result.append(std::to_string(o) + ",");
    if (result.back() == ',')
        result.back() = ']';
    else
        result.push_back(']');
    return result;
}


// Time to complete: 1 hr 15 mins

// Needed to research:

// Notes:
//  - long solution time due to initial failures to build iteravely

//// Begin solution, results at https://leetcode.com/submissions/detail/790179778/


// no leading 0s allowed
// 2 <= n <= 9
// 0 <= k <= 9

class Solution {
private:
    void consecDiffBuildCandidates(std::vector<int> &nums, const int candidate,
                                   const int k, const int level, const int n) {
        if (level == n) {
            nums.emplace_back(candidate);
            return;
        }
        int digit {candidate % 10};
        if (k == 0) {
            consecDiffBuildCandidates(nums, (candidate * 10) + digit,
                                      k, level + 1, n);
            return;
        }
        if ((digit - k) > -1) {
            consecDiffBuildCandidates(nums, (candidate * 10) + (digit - k),
                                      k, level + 1, n);
        }
        if ((digit + k) < 10) {
            consecDiffBuildCandidates(nums, (candidate * 10) + (digit + k),
                                      k, level + 1, n);
        }
    }
public:
    std::vector<int> numsSameConsecDiff(const int n, const int k) {
        std::vector<int> nums {};
        for (short digit {1}; digit < 10; ++digit)
            consecDiffBuildCandidates(nums, digit, k, 1, n);
        return nums;
    }
};


//// end solution


int main() {
    Solution solution;

    // Input: n = 3, k = 7
    std::cout << "solution.numsSameConsecDiff(3, 7): \n" <<
        printableVector(solution.numsSameConsecDiff(3, 7)) << std::endl;
    // Output: [181,292,707,818,929]

    // Input: n = 2, k = 1
    std::cout << "solution.numsSameConsecDiff(2, 1): \n" <<
        printableVector(solution.numsSameConsecDiff(2, 1)) << std::endl;
    // Output: [10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98]

    // Input: n = 3, k = 1
    std::cout << "solution.numsSameConsecDiff(3, 1): \n" <<
        printableVector(solution.numsSameConsecDiff(3, 1)) << std::endl;
    // Output: [101,121,123,210,212,232,234,321,323,343,345,432,434,454,456,
    //          543,545,565,567,654,656,676,678,765,767,787,789,876,878,898,
    //          987,989

    // Input: n = 2, k = 0
    std::cout << "solution.numsSameConsecDiff(2, 0): \n" <<
        printableVector(solution.numsSameConsecDiff(2, 0)) << std::endl;
    // Output: [11,22,33,44,55,66,77,88,99]
}
