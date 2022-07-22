#include <vector>
#include <iostream>


// See discussion at https://medium.com/algorithms-and-leetcode/best-time-to-buy-sell-stocks-on-leetcode-the-ultimate-guide-ce420259b323

//// Begin solution, results at https://leetcode.com/submissions/detail/699182618/


#include <algorithm>  // max, min


class Solution {
public:
    int maxProfit(const std::vector<int> &prices) {
        // 1 <= prices.size() <= 10^5
        // 0 <= prices[i] <= 10^4
        const int n (prices.size());
        if (n == 1)
            return 0;
        int min_price {prices[0]};
        int max_profit {0};
        for (auto i {1}; i < n; ++i) {
            min_price = std::min(min_price, prices[i]);
            max_profit = std::max(max_profit, prices[i] - min_price);
        }
        return max_profit;
    }
};


//// end solution


int main() {
    std::vector<int> v1 {7, 1, 5, 3, 6, 4};        // 5 ([5]:6 - [2]:1)
    std::vector<int> v2 {7, 6, 4, 3, 1};           // 0 (price never raises)
    Solution s;

    std::cout << "v1: " << s.maxProfit(v1) << std::endl;
    std::cout << "v2: " << s.maxProfit(v2) << std::endl;
}
