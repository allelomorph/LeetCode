#!/usr/bin/python3


# Time to complete: 3.5 hrs

# Needed to research:

#### Begin solution, results at https://leetcode.com/submissions/detail/740528683/


class Solution:
    """
    """
    # 0 <= s.length <= 5 * 10^4
    # s consists of English letters, digits, symbols and spaces
    def lengthOfLongestSubstring(self, s: str) -> int:
        """Finds the length of the longest substring without repeating
        characters.
        """
        if len(s) < 2:
            return len(s)
        ss_indices = {}  # substring char: index in s
        max_ss_len = 0
        for i, c in enumerate(s):
            ss_indices[c] = i
            ss_len = 0
            for j in range(i, -1, -1):
                if j != ss_indices[s[j]]:
                    break
                ss_len += 1
            max_ss_len = max(max_ss_len, ss_len)
        return max_ss_len


#### end solution


if __name__ == '__main__':
    s1 = "abcabcbb"
    s2 = "bbbbb"
    s3 = "pwwkew"
    s4 = " "
    s5 = "dvdf"
    s6 = "asjrgapa"
    s7 = "aabaab!bb"
    s8 = "uqinntq"
    s9 = "au"

    solution = Solution()

    print(f'solution.lengthOfLongestSubstring("{s1}"):',
          f'{solution.lengthOfLongestSubstring(s1)}')
    # 3 ("abc")

    print(f'solution.lengthOfLongestSubstring("{s2}"):',
          f'{solution.lengthOfLongestSubstring(s2)}')
    # 1 ("b")

    print(f'solution.lengthOfLongestSubstring("{s3}"):',
          f'{solution.lengthOfLongestSubstring(s3)}')
    # 3 ("wke")

    print(f'solution.lengthOfLongestSubstring("{s4}"):',
          f'{solution.lengthOfLongestSubstring(s4)}')
    # 1 (" ")

    print(f'solution.lengthOfLongestSubstring("{s5}"):',
          f'{solution.lengthOfLongestSubstring(s5)}')
    # 3 ("vdf")

    print(f'solution.lengthOfLongestSubstring("{s6}"):',
          f'{solution.lengthOfLongestSubstring(s6)}')
    # 6 ("sjrgap")


    print(f'solution.lengthOfLongestSubstring("{s7}"):',
          f'{solution.lengthOfLongestSubstring(s7)}')
    # 3 ("ab!")

    print(f'solution.lengthOfLongestSubstring("{s8}"):',
          f'{solution.lengthOfLongestSubstring(s8)}')
    # 4 ("uqin")

    print(f'solution.lengthOfLongestSubstring("{s9}"):',
          f'{solution.lengthOfLongestSubstring(s9)}')
    # 2 ("au")
