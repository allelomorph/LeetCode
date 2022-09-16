#include <iostream>
#include <vector>

#include "vector_stream_ops.hh"


// Time to complete: 1 hr

// Needed to research:

// Notes:

//// Begin solution, results at https://leetcode.com/submissions/detail/800159255/


#include <algorithm>  // sort
#include <cstdint>    // uint32_t
#include <queue>

// 1 <= changed.length <= 10^5
// 0 <= changed[i] <= 10^5
// not specified: values in original unique?
// not specified: allowed to sort changed in place?
class Solution {
public:
    std::vector<int> findOriginalArray(std::vector<int> &changed) {
        std::vector<int> result;
        uint32_t c_sz (changed.size());
        if (c_sz % 2 != 0)  // doubled array must have even number elements
            return result;
        std::sort(changed.begin(), changed.end());
        result.emplace_back(changed[0]);
        std::queue<int> unmatched;
        unmatched.emplace(changed[0]);
        for (uint32_t i {1}; i < c_sz; ++i) {
            if (unmatched.size() == 0 || changed[i] != unmatched.front() * 2) {
                result.emplace_back(changed[i]);
                unmatched.emplace(changed[i]);
            } else {
                unmatched.pop();
            }
        }
        if (result.size() != c_sz / 2)
            return std::vector<int> {};
        return result;
    }
};


/// end solution


int main(void) {
    std::vector<int> v1 {1,3,4,2,6,8};
    std::vector<int> v2 {6,3,0,1};
    std::vector<int> v3 {1};
    std::vector<int> v4 {0,0,0,0};

    Solution solution;

    // Input: changed = [1,3,4,2,6,8]
    std::cout << "solution.findOriginalArray(" << v1 << "): " <<
        solution.findOriginalArray(v1) << " expected: [1,3,4]" << std::endl;
    // Output: [1,3,4] (or [4,3,1] or [3,1,4])

    // Input: changed = [6,3,0,1]
    std::cout << "solution.findOriginalArray(" << v2 << "): " <<
        solution.findOriginalArray(v2) << " expected: []" << std::endl;
    // Output: []

    // Input: changed = [1]
    std::cout << "solution.findOriginalArray(" << v3 << "): " <<
        solution.findOriginalArray(v3) << " expected: []" << std::endl;
    // Output: []

    // Input: changed = [0,0,0,0]
    std::cout << "solution.findOriginalArray(" << v4 << "): " <<
        solution.findOriginalArray(v4) << " expected: [0,0]" << std::endl;
    // Output: [0,0]
}
