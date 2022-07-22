#include <iostream>
#include <vector>


const std::string printableVector(std::vector<std::string> v) {
    std::string result;
    result.push_back('[');
    for (const auto &s: v)
        result.append("\"" + s + "\",");
    result.back() = ']';  // overwrite last ','
    return result;
}


// Time to complete: 1 hr

// Needed to research:
//   - STL <cctype>

//// Begin solution, results at https://leetcode.com/submissions/detail/743838243/


#include <cctype>  // isalpha, toupper, tolower


class Solution {
public:
    // 1 <= s.length <= 12
    // s consists of lowercase English letters, uppercase English letters,
    //   and digits
    /*
     * Given a string s, returns a list of all possible strings created from
     * transforming every letter individually to be lowercase or uppercase.
     */
    std::vector<std::string> letterCasePermutation(std::string s) {
        std::vector<int> alpha_indices;
        const int s_len (s.length());
        for (int i {0}; i < s_len; ++i) {
            if (std::isalpha(s[i]))
                alpha_indices.push_back(i);
        }
        const int frame_limit (alpha_indices.size());  // recursions
        std::vector<std::string> perms;
        derivePermutations(perms, alpha_indices, s, frame_limit, 0);
        return perms;
    }
private:
    void derivePermutations(std::vector<std::string> &perms,
                            const std::vector<int> &alpha_indices,
                            const std::string &perm, const int frame_limit,
                            const int i) {
        if (i == frame_limit) {
            perms.push_back(perm);
            return;
        }
        std::string perm1 {perm};
        perm1[alpha_indices[i]] = std::tolower(perm1[alpha_indices[i]]);
        std::string perm2 {perm};
        perm2[alpha_indices[i]] = std::toupper(perm2[alpha_indices[i]]);

        derivePermutations(perms, alpha_indices, perm1, frame_limit, i + 1);
        derivePermutations(perms, alpha_indices, perm2, frame_limit, i + 1);
    }
};


//// end solution


int main() {
    std::string s1 = "a1b2";
    std::string s2 = "3z4";

    Solution solution;

    std::cout << "solution.letterCasePermutation(\"" << s1 <<
        "\"): " << printableVector(solution.letterCasePermutation(s1)) << '\n';
    // ["a1b2","a1B2","A1b2","A1B2"]

    std::cout << "solution.letterCasePermutation(\"" << s2 <<
        "\"): " << printableVector(solution.letterCasePermutation(s2)) << '\n';
    // ["3z4","3Z4"]

}
