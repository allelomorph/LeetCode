#include <iostream>
#include <string>


// Time to complete: 60 mins

// Needed to research:
//   - std::isspace

//// Begin solution, results at https://leetcode.com/submissions/detail/738114674/


#include <cctype>  // isspace
#include <cstdlib>  // div
#include <algorithm>  // swap


class Solution {
    // reverse the order of characters in each word within a sentence while
    //   still preserving whitespace and initial word order
    // 1 <= s.length <= 5 * 10^4
    // s contains printable ASCII characters.
    // s does not contain any leading or trailing spaces.
    // there is at least one word in s.
    // all the words in s are separated by a single space.
public:
    std::string reverseWords(std::string s) {
        const int s_sz (s.size());
        // C-like access to allow jumping ahead after reversed word
        for (int i {0}; i < s_sz;) {
            reverseWord(s, i);
            ++i;  // always one space
        }
        return s;
    }
private:
    void reverseWord(std::string &s, int &i) {
        int j {i};
        while (s[i] && !std::isspace(s[i])) ++i;
        const int word_sz {i - j};
        // for even lengths, i starts at rightmost index of left half, j
        //    leftmost of right half
        // for odd lengths, center is ignored and i and j start to either side
        auto dv = std::div(word_sz, 2);
        j += (dv.quot - 1);
        int k {(dv.rem == 0) ? j + 1 : j + 2};
        for (; k - j < word_sz; --j, ++k) {
            std::swap(s[j], s[k]);
        }
    }
};



//// end solution


int main() {
    std::string s1 {"Let's take LeetCode contest"};
    std::string s2 {"God Ding"};

    Solution solution;

    std::cout << "solution.reverseWords(" << s1 << "): ";
    s1 = solution.reverseWords(s1);
    std::cout << s1 << '\n';
    // "s'teL ekat edoCteeL tsetnoc"

    std::cout << "solution.reverseWords(" << s2 << "): ";
    s2 = solution.reverseWords(s2);
    std::cout << s2 << '\n';
    // "doG gniD"
}
