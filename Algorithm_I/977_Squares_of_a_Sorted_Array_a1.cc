#include <iostream>
#include <vector>


// Time to complete: about 1 hour

// Needed to research:
//   - STL map
//   - STL set
//   - set into vector


//// Begin solution, results at https://leetcode.com/submissions/detail/736853081/


class Solution {
    // 1 <= nums.length <= 10^4
    // -10^4 <= nums[i] <= 10^4
    // nums is sorted in increasing order
public:
    std::vector<int> sortedSquares(const std::vector<int> &nums) {
        int nums_sz (nums.size());
        int fnn_i {0};  // index of first non-negative
        for (; fnn_i < nums_sz && nums[fnn_i] < 0; ++fnn_i) {}
        std::vector<int> squares;
        // begin from first non-negative value in nums, sort results by
        //   interleaving squares of positives and negatives
        for (int i {fnn_i - 1}, j {fnn_i}, k {0}; k < nums_sz; ++k) {
            if (i >= 0 && j >= nums_sz) {
                squares.push_back(nums[i] * nums[i]);
                --i;
            } else if (j < nums_sz && i < 0) {
                squares.push_back(nums[j] * nums[j]);
                ++j;
            } else if (-nums[i] <= nums[j]) {
                squares.push_back(nums[i] * nums[i]);
                --i;
            } else {
                squares.push_back(nums[j] * nums[j]);
                ++j;
            }
        }
        return squares;
    }
};


//// end solution


template<typename T>
const std::string PrintableVector(std::vector<T> v) {
    std::string result;
    result.push_back('[');
    for (const auto &o: v)
        result.append(std::to_string(o) + ",");
    result.back() = ']';  // overwrite last ','
    return result;
}


int main() {
    std::vector<int> v1 {-4,-1,0,3,10};
    std::vector<int> v2 {-7,-3,2,3,11};

    Solution solution;

    std::cout << "solution(" << PrintableVector(v1) << "): " <<
        PrintableVector(solution.sortedSquares(v1)) << '\n';
    // [0,1,9,16,100]
    std::cout << "solution(" << PrintableVector(v2) << "): " <<
        PrintableVector(solution.sortedSquares(v2)) << '\n';
    // [4,9,9,49,121]
}
