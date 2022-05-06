//// Begin solution, results at https://leetcode.com/submissions/detail/689860859/

// Tested via manually derived solutions up to n = 8: the possible combinations
//   of steps, or climbStairs(n), equals the value at n + 1 if that was the
//   index in an array of positive fibonacci numbers.


class Solution {
public:
    int climbStairs(int n) {
        // Input known to be 1 <= n <= 45, no need to establish invariant
        return fib(n + 1);
    }
private:
    // 1 <= n <= 45
    static constexpr int max_n {45};
    static int dp[max_n + 2];  // +1 for 0, +1 for fib(45 + 1)

    int fib(int n) {
        if (n && !dp[n])
            dp[n] = fib(n - 1) + fib(n - 2);
        return dp[n];
    }
};


int Solution::dp[Solution::max_n + 2] {0, 1};


//// end solution


#include "UniformRandIntGen.hh"
#include <iostream>

int main() {
    Solution s;
    UniformRandIntGen<int> rng {1, 45};

    for (int i {0}, n; i < 30; ++i) {
        n = rng();
        std::cout << "s.climbStairs(" << n << "): " << s.climbStairs(n) << std::endl;
    }
}
