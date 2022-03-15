//// Begin solution, results at https://leetcode.com/submissions/detail/660188333/

// Problem encountered in the context of Dynamic Programming I course, so
//   elected to value time complexity over space complexity

#include <map>

class Solution {
public:
    int tribonacci(int n) {
        if (n == 0)
            return 0;
        int res {computed_tribs[n]};
        // accessing map with missing key returns default int constructor (0)
        if (!res) {
            if (n == 1 || n == 2) {
                computed_tribs[n] = 1;
                return 1;
            }
            int prev1 {computed_tribs[n - 1]};
            if (!prev1)
                prev1 = tribonacci(n - 1);
            int prev2 {computed_tribs[n - 2]};
            if (!prev2)
                prev2 = tribonacci(n - 2);
            int prev3 {computed_tribs[n - 3]};
            if (!prev3 && n != 3)
                prev3 = tribonacci(n - 3);
            res = prev1 + prev2 + prev3;
            computed_tribs[n] = res;
        }
        return res;
    }
private:
    std::map<int, int> computed_tribs;
};


//// end solution


#include "UniformRandIntGen.hh"
#include <iostream>

int main() {
    Solution s;
    UniformRandIntGen<int> rng {0, 37};

    for (int i {0}, n; i < 30; ++i) {
        n = rng();
        std::cout << "s.tribonacci(" << n << "): " << s.tribonacci(n) << std::endl;
    }
}
