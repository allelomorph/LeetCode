#include <vector>
#include <iostream>


// See discussion at https://medium.com/algorithms-and-leetcode/best-time-to-buy-sell-stocks-on-leetcode-the-ultimate-guide-ce420259b323


//// Begin solution, results at https://leetcode.com/submissions/detail/699767325/


#include <algorithm>  // max


class Solution {
public:
    int maxProfit(const std::vector<int> &prices) {
        // 1 <= prices.size() <= 3 * 10^4
        // 0 <= prices[i] <= 10^4
        int n (prices.size());
        int profit {};
        for (int i {1}; i < n; ++i)
            profit += std::max(prices[i] - prices[i - 1], 0);
        return profit;
    }
};


//// end solution


int main() {
    std::vector<int> v1 {7, 1, 5, 3, 6, 4};  // 7
    std::vector<int> v2 {1, 2, 3, 4, 5};    // 4
    std::vector<int> v3 {7, 6, 4, 3, 1};    // 0
    Solution s;

    std::cout << "v1: " << s.maxProfit(v1) << std::endl;
    std::cout << "v2: " << s.maxProfit(v2) << std::endl;
    std::cout << "v3: " << s.maxProfit(v3) << std::endl;
}
