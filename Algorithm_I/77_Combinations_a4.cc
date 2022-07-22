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


// Time to complete: 3.5 hrs including failed attempts

// Needed to research:

// Note: failed attemtps include a3, which was accepted but had terrible
//   performance - it was much like a4 except it copied combo vectors for every
//   recursion frame

//// Begin solution, results at https://leetcode.com/submissions/detail/744013489/


class Solution {
public:
    // 1 <= n <= 20
    // 1 <= k <= n
    /*
     * Given two integers n and k, return all possible combinations of k
     * numbers of the range [1, n].
     */
    std::vector<std::vector<int>> combine(const int n, const int k) {
        std::vector<std::vector<int>> combos;
        std::vector<int> combo(k, 0);
        for (int i {1}; i <= n; ++i) {
            recursiveCombination(combos, combo, 0, i, k, n);
        }
        return combos;
    }
private:
    void recursiveCombination(std::vector<std::vector<int>> &combos,
                              std::vector<int> &combo, const int combo_i,
                              const int combo_elem, const int k, const int n) {
        if (combo_i == k)
            return;
        combo[combo_i] = combo_elem;
        for (int i {combo_elem + 1}; i <= n; ++i)
            recursiveCombination(combos, combo, combo_i + 1, i, k, n);
        if (combo_i == k - 1)
            combos.push_back(combo);
    }
};


//// end solution


int main() {
    const int n1 {4};
    const int k1 {2};

    const int n2 {1};
    const int k2 {1};

    const int n3 {5};
    const int k3 {1};

    const int n4 {5};
    const int k4 {2};

    const int n5 {5};
    const int k5 {3};

    const int n6 {5};
    const int k6 {4};

    const int n7 {5};
    const int k7 {5};

    const int n8 {4};
    const int k8 {3};

    Solution solution;

    std::cout << "solution.permute(" << n1 << ", " << k1 << "): " <<
        printableNestedVector(solution.combine(n1, k1)) << '\n';
    // [[2,4], [3,4], [2,3], [1,2], [1,3], [1,4]]

    std::cout << "solution.permute(" << n2 << ", " << k2 << "): " <<
        printableNestedVector(solution.combine(n2, k2)) << '\n';
    // [[1]]

    std::cout << "solution.permute(" << n3 << ", " << k3 << "): " <<
        printableNestedVector(solution.combine(n3, k3)) << '\n';
    //

    std::cout << "solution.permute(" << n4 << ", " << k4 << "): " <<
        printableNestedVector(solution.combine(n4, k4)) << '\n';
    //

    std::cout << "solution.permute(" << n5 << ", " << k5 << "): " <<
        printableNestedVector(solution.combine(n5, k5)) << '\n';
    //

    std::cout << "solution.permute(" << n6 << ", " << k6 << "): " <<
        printableNestedVector(solution.combine(n6, k6)) << '\n';
    //

    std::cout << "solution.permute(" << n7 << ", " << k7 << "): " <<
        printableNestedVector(solution.combine(n7, k7)) << '\n';
    //

    std::cout << "solution.permute(" << n8 << ", " << k8 << "): " <<
        printableNestedVector(solution.combine(n8, k8)) << '\n';
    // [[1,2,3],[1,2,4],[1,3,4],[2,3,4]]

}
