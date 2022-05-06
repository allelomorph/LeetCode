#include <iostream>

//// Begin solution, results at https://leetcode.com/submissions/detail/688157315/

class Solution {
public:
    int tribonacci(int n) {
        if (n == 0)
            return 0;
        if (!dp[n]) {
            for (int i {3}; i <= n; ++i) {
                if (!dp[i])
                    dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
            }
        }
        return dp[n];
    }

private:
    // 0 <= n <= 37
    static constexpr std::size_t n_max {37};
    // The answer is guaranteed to fit within a 32-bit integer, ie. answer <= 2^31 - 1.
    static int dp[n_max + 1];
};

int Solution::dp[Solution::n_max + 1] {0, 1, 1};

//// end solution

int main() {
    Solution s {};
    std::cout << s.tribonacci(3) << std::endl;
    std::cout << s.tribonacci(4) << std::endl;
    std::cout << s.tribonacci(25) << std::endl;
}
