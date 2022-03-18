//// Begin solution, results at https://leetcode.com/submissions/detail/661411713/

// testing a pattern that seems to have emerged while looking for patterns in
//   brute force solutions up to n = 6: the results seem to be fibonacci(n + 1)

class Solution {
public:
    int climbStairs(int n) {
        // would establish invariant here that 1 <= n <= 45, but omitting
        //   exceptions for efficiency
        return fib(n + 1);
    }
private:
    // leveraging knowledge of input space being 1 <= n <= 45
    static constexpr int max_n {46};
    // C-like array over std:array for smallest footprint possible
    int computed_results[max_n + 1] {};  // defaults to 0
    int fib(int n) {
        int res {computed_results[n]};
        if (!res) {
            if (n == 1 || n == 2) {
                computed_results[n] = 1;
                return 1;
            }
            int prev1 {fib(n - 1)};
            int prev2 {fib(n - 2)};
            res = prev1 + prev2;
            computed_results[n] = res;
        }
        return res;
    }
};


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
