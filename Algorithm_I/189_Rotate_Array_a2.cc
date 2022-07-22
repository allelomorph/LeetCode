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


// Time to complete: 2.5 days (!)

// Needed to research:
//   - std::swap

//// Begin solution, results at https://leetcode.com/submissions/detail/737856025/


#include <algorithm>  // swap


class Solution {
    // 1 <= nums.length <= 10^5
    // -231 <= nums[i] <= 231 - 1
    // 0 <= k <= 105
    // Tried space O(1) time O(n) solution first, although it became quite
    //   convoluted to derive by gradually generalizing edge cases...
public:
    void rotate(std::vector<int> &nums, const int k) {
        const int nums_sz (nums.size());
        const int shift {k % nums_sz};
        if (shift == 0)
            return;

        const int back_shift {nums_sz - shift};
        int i {nums_sz - 1};
        int temp {nums[i]};
        if (back_shift <= shift) {
            for (int assign_ct {0}, origin_i {i}; assign_ct < nums_sz;) {
                // multiple small back shifts
                while (i - back_shift >= 0) {
                    i -= back_shift;
                    std::swap(temp, nums[i]);
                    ++assign_ct;
                }
                // one shift forward
                i += shift;
                // if landing on a visited index, offset one back
                if (i == origin_i) {
                    nums[i] = temp;
                    origin_i = --i;
                    temp = nums[i];
                } else {
                    std::swap(temp, nums[i]);
                }
                ++assign_ct;
            }
        } else {  // back_shift > shift
            for (int assign_ct {0}, origin_i {i}; assign_ct < nums_sz;) {
                // one back shift
                i -= back_shift;
                std::swap(temp, nums[i]);
                ++assign_ct;
                // multiple small forward shifts
                while (i + shift < back_shift) {
                    i += shift;
                    std::swap(temp, nums[i]);
                    ++assign_ct;
                }
                i += shift;
                // if landing on a visited index, offset one back
                if (i == origin_i) {
                    nums[i] = temp;
                    origin_i = --i;
                    temp = nums[i];
                } else {
                    std::swap(temp, nums[i]);
                }
                ++assign_ct;
            }
        }
    }
};


//// end solution


#include <numeric>  // iota


int main() {
    std::vector<int> v1 {1,2,3,4,5,6,7};
    std::vector<int> v2 {-1,-100,3,99};
    std::vector<int> v3 {0,1,2,3,4};
    std::vector<int> v4 {0,1,2,3,4};
    std::vector<int> v5 {0,1,2,3,4,5};
    std::vector<int> v6 {0,1,2,3,4};
    std::vector<int> v7 {0,1,2,3,4,5};
    std::vector<int> v8 {0,1,2,3,4,5};
    std::vector<int> v9 {0,1,2,3,4,5,6,7};
    std::vector<int> v10 {0,1,2,3,4,5,6,7};

    Solution solution;

    std::cout << "solution.rotate(" << PrintableVector(v1) << ", 3): ";
    solution.rotate(v1, 3);
    std::cout << PrintableVector(v1) << '\n';
    // [5,6,7,1,2,3,4]

    std::cout << "solution.rotate(" << PrintableVector(v2) << ", 2): ";
    solution.rotate(v2, 2);
    std::cout << PrintableVector(v2) << '\n';
    // [3,99,-1,-100]

    // k = 1:
    std::cout << "solution.rotate(" << PrintableVector(v3) << ", 1): ";
    solution.rotate(v3, 1);
    std::cout << PrintableVector(v3) << '\n';
    // [4,0,1,2,3]

    // k = nums.size - 1:
    std::cout << "solution.rotate(" << PrintableVector(v4) << ", 4): ";
    solution.rotate(v4, 4);
    std::cout << PrintableVector(v4) << '\n';
    // [1,2,3,4,0]

    // k = nums.size / 2 and nums.size is even:
    std::cout << "solution.rotate(" << PrintableVector(v5) << ", 3): ";
    solution.rotate(v5, 3);
    std::cout << PrintableVector(v5) << '\n';
    // [3,4,5,0,1,2]

    // k = nums.size / 2 and nums.size is odd:
    std::cout << "solution.rotate(" << PrintableVector(v6) << ", 2): ";
    solution.rotate(v6, 2);
    std::cout << PrintableVector(v6) << '\n';
    // [3,4,0,1,2]

    // 1 < k < nums.size / 2:
    std::cout << "solution.rotate(" << PrintableVector(v7) << ", 2): ";
    solution.rotate(v7, 2);
    std::cout << PrintableVector(v7) << '\n';
    // [4,5,0,1,2,3]

    // nums.size / 2 < k < nums.size - 1:
    std::cout << "solution.rotate(" << PrintableVector(v8) << ", 4): ";
    solution.rotate(v8, 4);
    std::cout << PrintableVector(v8) << '\n';
    // [2,3,4,5,0,1]

    // 1 < k < nums.size / 2:
    std::cout << "solution.rotate(" << PrintableVector(v9) << ", 3): ";
    solution.rotate(v9, 3);
    std::cout << PrintableVector(v9) << '\n';
    // [5,6,7,0,1,2,3,4]

    // 1 < k < nums.size / 2:
    std::cout << "solution.rotate(" << PrintableVector(v10) << ", 5): ";
    solution.rotate(v10, 5);
    std::cout << PrintableVector(v10) << '\n';
    // [5,6,7,0,1,2,3,4]

    const int n {100000};
    const int k {54944};
    std::vector<int> v38_simple(n);
    std::iota(v38_simple.begin(), v38_simple.end(), 0);
    solution.rotate(v38_simple, k);
    std::cout << std::boolalpha;
    std::cout << "v38_simple[0] == n - k: " <<
        (v38_simple[0] == n - k) << ": " << v38_simple[0] << '\n';
    std::cout << "v38_simple[k - 1] == n - 1: " <<
        (v38_simple[k - 1] == n - 1) << ": " << v38_simple[k - 1] << '\n';
    std::cout << "v38_simple[k] == 0: " <<
        (v38_simple[k] == 0) << ": " << v38_simple[k] << '\n';
    std::cout << "v38_simple[n - 1] == n - k - 1: " <<
        (v38_simple[n - 1] == n - k - 1) << ": " << v38_simple[n - 1] << '\n';
}
