#include <iostream>
#include <vector>


// Time to complete: 3.5 hrs

// Needed to research:
//   - std::map methods

//// Begin solution, results at https://leetcode.com/submissions/detail/740530934/


#include <map>
#include <algorithm>


class Solution {
public:
    // 0 <= s.length <= 5 * 10^4
    // s consists of English letters, digits, symbols and spaces
    // Given a string s, find the length of the longest substring without
    //   repeating characters.
    int lengthOfLongestSubstring(const std::string &s) {
        const int s_sz (s.size());
        if (s_sz < 2)
            return s_sz;
        int max_ss_sz {0};  // max substring length
        std::map<char, int> ss_indices;  // substring char: index in s
        for (int i {0}, ss_sz {0}; i < s_sz; ++i, ss_sz = 0) {
            ss_indices[s[i]] = i;  // update if present, insert if not
            for (int j {i}; j >= 0 && j == ss_indices[s[j]]; --j)
                ++ss_sz;
            max_ss_sz = std::max(max_ss_sz, ss_sz);
        }
        return max_ss_sz;
    };
};

//// end solution


int main() {
    const std::string s1 {"abcabcbb"};
    const std::string s2 {"bbbbb"};
    const std::string s3 {"pwwkew"};
    const std::string s4 {" "};
    const std::string s5 {"dvdf"};
    const std::string s6 {"asjrgapa"};
    const std::string s7 {"aabaab!bb"};
    const std::string s8 {"uqinntq"};
    const std::string s9 {"au"};

    Solution solution;

    std::cout << "solution.lengthOfLongestSubstring(\"" << s1 << "\"): " <<
        solution.lengthOfLongestSubstring(s1) << '\n';
    // 3 ("abc")

    std::cout << "solution.lengthOfLongestSubstring(\"" << s2 << "\"): " <<
        solution.lengthOfLongestSubstring(s2) << '\n';
    // 1 ("b")

    std::cout << "solution.lengthOfLongestSubstring(\"" << s3 << "\"): " <<
        solution.lengthOfLongestSubstring(s3) << '\n';
    // 3 ("wke")

    std::cout << "solution.lengthOfLongestSubstring(\"" << s4 << "\"): " <<
        solution.lengthOfLongestSubstring(s4) << '\n';
    // 1 (" ")

    std::cout << "solution.lengthOfLongestSubstring(\"" << s5 << "\"): " <<
        solution.lengthOfLongestSubstring(s5) << '\n';
    // 3 ("vdf")

    std::cout << "solution.lengthOfLongestSubstring(\"" << s6 << "\"): " <<
        solution.lengthOfLongestSubstring(s6) << '\n';
    // 6 ("sjrgap")

    std::cout << "solution.lengthOfLongestSubstring(\"" << s7 << "\"): " <<
        solution.lengthOfLongestSubstring(s7) << '\n';
    // 3 ("ab!")

    std::cout << "solution.lengthOfLongestSubstring(\"" << s8 << "\"): " <<
        solution.lengthOfLongestSubstring(s8) << '\n';
    // 4 ("uqin")

    std::cout << "solution.lengthOfLongestSubstring(\"" << s9 << "\"): " <<
        solution.lengthOfLongestSubstring(s9) << '\n';
    // 2 ("au")
}
