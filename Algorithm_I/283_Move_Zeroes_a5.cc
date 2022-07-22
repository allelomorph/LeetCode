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


// Time to complete: 60 mins

// Needed to research:

//// Begin solution, results at https://leetcode.com/submissions/detail/738057085/


class Solution {
    // 1 <= nums.length <= 10^4
    // -2^31 <= nums[i] <= 2^31 - 1
    // "in-place without making a copy of the array"
    // "Could you minimize the total number of operations done?"
public:
    void moveZeroes(std::vector<int> &nums) {
        const int nums_sz (nums.size());
        if (nums_sz == 1) return;
        int j {0};
        int zero_ct {0};
        // establish starting condition of nums[0] is non-zero
        for (; j < nums_sz && nums[j] == 0; ++j)
            ++zero_ct;
        // edge case of all zeroes
        if (j == nums_sz) return;
        nums[0] = nums[j++];
        int i {1};
        // count zero values and swap non-zero values into leftmost
        //   available index
        for (; i + zero_ct < nums_sz; ++i, ++j) {
            while (j < nums_sz && nums[j] == 0) {
                ++zero_ct;
                ++j;
            }
            if (j != nums_sz)
                nums[i] = nums[j];
        }
        // fill in zero values in remaining array as if shuffled to right
        for (i = nums_sz - zero_ct; i < nums_sz; ++i)
            nums[i] = 0;
    }
};


//// end solution


int main() {
    std::vector<int> v1 {0,1,0,3,12};
    std::vector<int> v2 {0};
    std::vector<int> v3 {0,0};
    std::vector<int> v4 {1,0};
    std::vector<int> v5 {0,1,0};

    Solution solution;

    std::cout << "solution.moveZeroes(" << PrintableVector(v1) << "): ";
    solution.moveZeroes(v1);
    std::cout << PrintableVector(v1) << '\n';
    // [1,3,12,0,0]

    std::cout << "solution.moveZeroes(" << PrintableVector(v2) << "): ";
    solution.moveZeroes(v2);
    std::cout << PrintableVector(v2) << '\n';
    // [0]

    std::cout << "solution.moveZeroes(" << PrintableVector(v3) << "): ";
    solution.moveZeroes(v3);
    std::cout << PrintableVector(v3) << '\n';
    // [0, 0]

    std::cout << "solution.moveZeroes(" << PrintableVector(v4) << "): ";
    solution.moveZeroes(v4);
    std::cout << PrintableVector(v4) << '\n';
    // [1, 0]

    std::cout << "solution.moveZeroes(" << PrintableVector(v5) << "): ";
    solution.moveZeroes(v5);
    std::cout << PrintableVector(v5) << '\n';
    // [1, 0, 0]
}
