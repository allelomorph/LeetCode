#include <iostream>

#include "vector_stream_ops.hh"


// Time to complete: 1.25 hrs

// Needed to research:

// Notes:
//   - understood solution on first attempt, but was a bit lazy with generating
//       edge cases, requiring multiple revisions

//// Begin solution, results at https://leetcode.com/submissions/detail/800871205/


#include <cstdint>
#include <algorithm>  // sort


// 0 <= tokens.length <= 1000
// 0 <= tokens[i], power < 10^4
// not stated: is it okay to sort tokens in place?
// if current power >= tokens[i]: power -= tokens[i], ++score
// if current score >= 1: power += tokens[i], --score
// tokens can be played in any order
class Solution {
public:
    int bagOfTokensScore(std::vector<int> &tokens, int power) {
        uint32_t t_sz(tokens.size());
        if (t_sz == 0)
            return 0;
        std::sort(tokens.begin(), tokens.end());
        int score {0};
        bool score_updated;
        for (uint32_t i {0}, j {t_sz - 1}; i <= j; score_updated = false) {
            while (i < t_sz && power >= tokens[i]) {
                power -= tokens[i];
                ++score;
                score_updated = true;
                ++i;
            }
            if (score > 0 && i < j) {
                power += tokens[j];
                --score;
                score_updated = true;
                --j;
            }
            if (!score_updated)
                return score;
        }
        return score;
    }
};


/// end solution


int main(void) {
    Solution solution;
    // Input: tokens = [100], power = 50
    std::vector<int> v1 {100};
    std::cout << "solution.bagOfTokensScore(" << v1 << ", " << 50 << "): " <<
        solution.bagOfTokensScore(v1, 50) << " expected: 0" << std::endl;
    // Output: 0

    // Input: tokens = [100,200], power = 150
    std::vector<int> v2 {100,200};
    std::cout << "solution.bagOfTokensScore(" << v2 << ", " << 150 << "): " <<
        solution.bagOfTokensScore(v2, 150) << " expected: 1" << std::endl;
    // Output: 1

    // Input: tokens = [100,200,300,400], power = 200
    std::vector<int> v3 {100,200,300,400};
    std::cout << "solution.bagOfTokensScore(" << v3 << ", " << 200 << "): " <<
        solution.bagOfTokensScore(v3, 200) << " expected: 2" << std::endl;
    // Output: 2
}
