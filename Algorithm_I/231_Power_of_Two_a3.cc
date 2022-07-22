#include <iostream>


// Time to complete: 15 mins

// Needed to research:

// Note: Attempt #1 missed 0 as edge case, and #2 underflowed when trying to
//   subtract from INT_MIN

//// Begin solution, results at https://leetcode.com/submissions/detail/745614187/


class Solution {
public:
    // -2^31 <= n <= 2^31 - 1
    // possible without loops/recursion?
    /*
     * Given an integer n, returns true if it is a power of two, false if not.
     */
    bool isPowerOfTwo(int n) {
        return (n > 0 && (n & (n - 1)) == 0);
    }
};


//// end solution


#include <limits>


int main() {
    int n1 {1};
    int n2 {16};
    int n3 {3};
    int n4 {0};
    int n5 {-2};
    int n6 {std::numeric_limits<int>::min()};
    int n7 {std::numeric_limits<int>::max()};

    Solution solution;

    std::cout << std::boolalpha;

    std::cout << "solution.isPowerOfTwo(" << n1 <<
        "): " << solution.isPowerOfTwo(n1) << '\n';
    // true (2^0)

    std::cout << "solution.isPowerOfTwo(" << n2 <<
        "): " << solution.isPowerOfTwo(n2) << '\n';
    // true (2^4)

    std::cout << "solution.isPowerOfTwo(" << n3 <<
        "): " << solution.isPowerOfTwo(n3) << '\n';
    // false

    std::cout << "solution.isPowerOfTwo(" << n4 <<
        "): " << solution.isPowerOfTwo(n4) << '\n';
    // false

    std::cout << "solution.isPowerOfTwo(" << n5 <<
        "): " << solution.isPowerOfTwo(n5) << '\n';
    // false

    std::cout << "solution.isPowerOfTwo(" << n6 <<
        "): " << solution.isPowerOfTwo(n6) << '\n';
    // false

    std::cout << "solution.isPowerOfTwo(" << n7 <<
        "): " << solution.isPowerOfTwo(n7) << '\n';
    // false
}
