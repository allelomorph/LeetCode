//// Begin solution, results at https://leetcode.com/submissions/detail/688163169/

class Solution {
public:
    int fib(int n) {
        if (n == 0)
            return 0;
        if (!dp[n]) {
            for (int i {2}; i <= n; ++i) {
                if (!dp[i])
                    dp[i] = dp[i - 1] + dp[i - 2];
            }
        }
        return dp[n];
    }
private:
    // 0 <= n <= 30
    static constexpr int max_n {30};
    static int dp[max_n + 1];
};

int Solution::dp[Solution::max_n + 1] {0, 1};

//// end solution


#include <iostream>

int main() {
    Solution s;

    std::cout << "s.fib(" << 2 << "): " << s.fib(2) << std::endl;
    std::cout << "s.fib(" << 3 << "): " << s.fib(3) << std::endl;
    std::cout << "s.fib(" << 4 << "): " << s.fib(4) << std::endl;
}
