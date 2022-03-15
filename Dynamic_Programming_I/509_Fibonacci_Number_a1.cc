// Problem introduced in the context of Dynamic Programming I course, so chose
//   to value time complexity over space complexity
//// Begin solution, results at https://leetcode.com/submissions/detail/660154130/


#include <map>

class Solution {
public:
    int fib(int n) {
        int res, prev1, prev2;
        try {
            // operator[] will not throw exceptions for missing keys
            res = computed_fibs.at(n);
        } catch (const std::out_of_range &oor) {
            switch (n) {
            case 0:
                computed_fibs[n] = 0;
                return 0;
                // could extend to negative by including `|| n == -1` in test
            case 1:
                computed_fibs[n] = 1;
                return 1;
            default:
                try {
                    prev1 = computed_fibs.at(n - 1);
                } catch (const std::out_of_range &oor) {
                    prev1 = fib(n - 1);
                }
                try {
                    prev2 = computed_fibs.at(n - 2);
                } catch (const std::out_of_range &oor) {
                    prev2 = fib(n - 2);
                }
                res = prev1 + prev2;
                computed_fibs[n] = res;
            }
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
