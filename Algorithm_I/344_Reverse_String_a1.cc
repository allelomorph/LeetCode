#include <iostream>
#include <vector>


template<typename T>
const std::string PrintableVector(std::vector<T> v) {
    std::string result;
    result.push_back('[');
    for (const auto &o: v)
        result.append(std::to_string(o) + ",");
    result.back() = ']';  // overwrite last ','
    return result;
}


// Time to complete: 30 mins

// Needed to research:
//   - std::div

//// Begin solution, results at https://leetcode.com/submissions/detail/738074737/


#include <cstdlib>  // div
#include <algorithm>  // swap


class Solution {
    // "in-place with O(1) extra memory"
    // 1 <= s.length <= 10^5
    // s[i] is a printable ascii character (each byte can be considered
    //   individually rather than as part of a Unicode character)
public:
    void reverseString(std::vector<char> &s) {
        int s_sz (s.size());
        int i, j;
        auto dv = std::div(s_sz, 2);
        // for even lengths, i starts at rightmost index of left half, j
        //    leftmost of right half
        // for odd lengths, center is ignored and i and j start to either side
        i = dv.quot - 1;
        j = (dv.rem == 0) ? i + 1 : i + 2;
        for (; i >= 0 && j < s_sz; --i, ++j)
            std::swap(s[i], s[j]);
    }
};


//// end solution


int main() {
    //                     0   1   2   3   4   5
    std::vector<char> v1 {'h','e','l','l','o'};
    std::vector<char> v2 {'H','a','n','n','a','h'};

    Solution solution;

    std::cout << "solution.reverseString(" << PrintableVector(v1) << "): ";
    solution.reverseString(v1);
    std::cout << PrintableVector(v1) << '\n';

    std::cout << "solution.reverseString(" << PrintableVector(v2) << "): ";
    solution.reverseString(v2);
    std::cout << PrintableVector(v2) << '\n';

}
