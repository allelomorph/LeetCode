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


template<typename T>
const std::string printableNestedVector(
    const std::vector<std::vector<T>> &nv) {
    std::string result;
    result.push_back('[');
    for (const auto &v: nv) {
        result.push_back('[');
        for (const auto &o: v) {
            result.append(std::to_string(o) + ",");
        }
        if (result.back() == ',')
            result.back() = ']';
        else
            result.push_back(']');
        result.push_back(',');
    }
    if (result.back() == ',')
        result.back() = ']';
    else
        result.push_back(']');
    return result;
}


// Time to complete: 2 hrs

// Needed to research:

//// Begin solution, results at https://leetcode.com/submissions/detail/743838909/


#include <algorithm>  // swap


class Solution {
public:
    // 1 <= nums.length <= 6
    // -10 <= nums[i] <= 10
    // all the integers of nums are unique
    // can be in any order
    /*
     * Given an array nums of distinct integers, returns all the possible
     * permutations.
     */
    std::vector<std::vector<int>> permute(const std::vector<int> &nums) {
        const int n (nums.size());
        std::vector<int> factorial {0};
        // up to 6: {0,1,2,6,24,120,720}
        for (int i {1}, fact {1}; i <= n; ++i, fact *= i)
            factorial.push_back(fact);
        std::vector<std::vector<int>> perms;
        // start with n! copies of nums
        for (int i {0}; i < factorial[n]; ++i)
            perms.push_back(std::vector<int> {nums});
        arrangePermuations(perms, factorial, 0, n, 0);
        return perms;
    }

private:
    void arrangePermuations(std::vector<std::vector<int>> &perms,
                            const std::vector<int> &factorial,
                            const int beg_i, const int level,
                            const int swap_left_i) {
        if (level == 1)
            return;
        const int next_fact {factorial[level - 1]};
        // skip first (n - 1)!
        for (int i {1}, perms_i {beg_i + next_fact}; i < level; ++i) {
            for (int j {0}; j < next_fact; ++j, ++perms_i) {
                std::swap(perms[perms_i][swap_left_i],
                          perms[perms_i][swap_left_i + i]);
            }
        }
        for (int i {0}; i < level; ++i) {
            arrangePermuations(perms, factorial, beg_i + (i * next_fact),
                               level - 1, swap_left_i + 1);
        }
    }
};


//// end solution


int main() {
    std::vector<int> v1 {1,2,3};
    std::vector<int> v2 {0,1};
    std::vector<int> v3 {1};
    std::vector<int> v4 {0,1,2};
    std::vector<int> v5 {0,1,2,3};

    Solution solution;

    std::cout << "solution.permute(" << printableVector(v1) << "): " <<
        printableNestedVector(solution.permute(v1)) << '\n';
    // [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]


    std::cout << "solution.permute(" << printableVector(v2) << "): " <<
        printableNestedVector(solution.permute(v2)) << '\n';
    // [[0,1],[1,0]]

    std::cout << "solution.permute(" << printableVector(v3) << "): " <<
        printableNestedVector(solution.permute(v3)) << '\n';
    // [[1]]

    std::cout << "solution.permute(" << printableVector(v4) << "): " <<
        printableNestedVector(solution.permute(v4)) << '\n';
    // 

    std::cout << "solution.permute(" << printableVector(v5) << "): " <<
        printableNestedVector(solution.permute(v5)) << '\n';
    //
}
