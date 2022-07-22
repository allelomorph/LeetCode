#!/usr/bin/python3


# Time to complete: 2 hrs

# Needed to research:
# -

# Note: very poor performance: 27.72 percentile for speed, 6.92 percentile for
#   memory - consider refactoring

#### Begin solution, results at https://leetcode.com/submissions/detail/741310612/


class Solution:
    """
    """
    # 1 <= s1.length, s2.length <= 104
    # s1 and s2 consist of lowercase English letters.
    def checkInclusion(self, s1: str, s2: str) -> bool:
        """Given two strings s1 and s2, return true if s2 contains a
        permutation of s1, or false otherwise.
        """
        # create profile dict to match against:
        #   keys: unique chars in s1, values: count of appearances
        profile = {}
        for c in s1:
            if c in profile:
                profile[c] += 1
            else:
                profile[c] = 1
        profile_sz = len(profile)
        # print(f'profile: {profile}')
        # create similar dicts for each s2 substring with at least 1 of each
        #   unique char in s1:
        #   keys: unique chars, values: [occurance count, index of first occurance]
        candidate = {}
        for i, c in enumerate(s2):
            # print(f'c: \'{c}\': ', end='')
            if c in s1:
                if c in candidate:
                    candidate[c][0] += 1
                else:
                    candidate[c] = [1, i]
                if candidate[c][0] > profile[c]:
                    # in region of s2 with s1 chars, but count of current
                    #   no longer mathces profile: rebuild candidate from
                    #   index after first occurance of current char
                    start_j = candidate[c][1] + 1
                    candidate = {}
                    for j in range(start_j, i + 1):
                        if s2[j] not in candidate:
                            candidate[s2[j]] = [1, j]
                        else:
                            candidate[s2[j]][0] += 1
            else:
                candidate = {}
            # print(f'candidate: {candidate}')
            if len(candidate) == profile_sz:
                if all([candidate[key][0] == profile[key] for key \
                        in profile.keys()]):
                    return True
        return False


#### end solution


if __name__ == '__main__':
    s1_1, s2_1 = "ab", "eidbaooo"
    s1_2, s2_2 = "ab", "eidboaoo"
    s1_3, s2_3 = "abbcccdddd", "iiiiiiiiiacbdiiiiiiiiiidbdabcdcdciiiii"
    s1_4, s2_4 = "adc", "dcda"
    s1_5, s2_5 = "ddcda", "iiidcdaaaadciii"
    s1_6, s2_6 = "abc", "cccccbabbbaaaa"

    solution = Solution()

    print(f'solution.checkInclusion("{s1_1}", "{s2_1}"):',
          f'{solution.checkInclusion(s1_1, s2_1)}')
    # True

    print(f'solution.checkInclusion("{s1_2}", "{s2_2}"):',
          f'{solution.checkInclusion(s1_2, s2_2)}')
    # False

    print(f'solution.checkInclusion("{s1_3}", "{s2_3}"):',
          f'{solution.checkInclusion(s1_3, s2_3)}')
    # True

    print(f'solution.checkInclusion("{s1_4}", "{s2_4}"):',
          f'{solution.checkInclusion(s1_4, s2_4)}')
    # True

    print(f'solution.checkInclusion("{s1_5}", "{s2_5}"):',
          f'{solution.checkInclusion(s1_5, s2_5)}')
    # False

    print(f'solution.checkInclusion("{s1_6}", "{s2_6}"):',
          f'{solution.checkInclusion(s1_6, s2_6)}')
    # True
