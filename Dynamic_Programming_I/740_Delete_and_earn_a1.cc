#include <vector>
#include <iostream>


//// Begin solution, results at https://leetcode.com/submissions/detail/662736567/


#include <algorithm>  // max
#include <map>


class Solution {
public:
    int deleteAndEarn(std::vector<int> &nums) {
        // As redundant apprearances of a value in nums can count together
        //   towards a potential total, or be all eliminated together when a
        //   value +-1 is deleted, we can group them into a map, which when
        //   traversed also allows us to consider values in sorted order.
        // nt = "nums totals" keys: integers in nums, values: key * total appearances in nums
        std::map<int, int> nt;
        for (auto &n : nums)
            nt[n] += n;
        // 1 <= nums.length <= 2 * 10^4
        int nt_sz (nt.size());

        auto it {nt.begin()};
        auto pair1 {*it};
        int dp {pair1.second};   // dp for current key in nt
        if (nt_sz == 1)
            return dp;

        auto pair2 {*(++it)};
        int key {pair2.first};   // current key in nt
        int pkey {pair1.first};  // previous key
        int pdp {dp};            // previous dp
        if (pkey == key - 1)
            dp = std::max(pdp, pair2.second);
        else
            dp = pdp + pair2.second;
        if (nt_sz == 2)
            return dp;

        ++it;
        for (int ppdp; it != nt.end(); ++it) {
            ppdp = pdp;
            pdp = dp;
            pkey = key;
            key = it->first;
            if (pkey == key - 1) {
                dp = std::max(pdp, ppdp + it->second);
            } else {
                dp = pdp + it->second;
            }
        }
        return dp;
    }
};


//// end solution


int main() {
    // map 2:2, 3:3, 4:4
    std::vector<int> v1 {3, 4, 2};           // 6
    // map 2:4, 3:9, 4:4
    std::vector<int> v2 {2, 2, 3, 3, 3, 4};  // 9
    Solution s;
    std::cout << s.deleteAndEarn(v1) << std::endl;
    std::cout << s.deleteAndEarn(v2) << std::endl;
}
