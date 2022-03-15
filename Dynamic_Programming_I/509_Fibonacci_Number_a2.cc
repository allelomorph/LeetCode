// Problem introduced in the context of Dynamic Programming I course, so chose
//   to value time complexity over space complexity
//// Begin solution, results at https://leetcode.com/submissions/detail/660163386/


#include <map>

class Solution {
public:
    int fib(int n) {
        if (n == 0)
            return 0;
        // operator[] will not throw exceptions for missing keys
        // instead it will return int with default value 0
        int res {computed_fibs[n]};
        if (!res) {
            // could extend to negative by including `|| n == -1` in test
            if (n == 1) {
                computed_fibs[n] = 1;
                return 1;
            }
            int prev1 {computed_fibs[n - 1]};
            if (!prev1 && n - 1 != 0)
                prev1 = fib(n - 1);
            int prev2 {computed_fibs[n - 2]};
            if (!prev2 && n - 2 != 0)
                prev2 = fib(n - 2);
            res = prev1 + prev2;
            computed_fibs[n] = res;
        }
        return res;
    }
private:
    std::map<int, int> computed_fibs;
};


//// end solution


#include "UniformRandIntGen.hh"
#include <iostream>

int main() {
    Solution s;
    UniformRandIntGen<int> rng {0, 30};

    for (auto i {0}; i < 30; ++i) {
        int n {rng()};
        std::cout << "s.fib(" << n << "): " << s.fib(n) << std::endl;
    }
}
