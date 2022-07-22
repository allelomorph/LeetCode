#!/usr/bin/python3


from typing import List


# Time to complete: 10 mins

# Needed to research:

# Note: already solved in C++ as part of Dynamic Programming I study plan

#### Begin solution, results at https://leetcode.com/submissions/detail/744709171/


class Solution:
    """
    """
    # 1 <= nums.length <= 100
    # 0 <= nums[i] <= 400
    def rob(self, nums: List[int]) -> int:
        """Returns the maximum sum taken from any set of indices that contains
        no adjacent pairs.

        """
        nums_len = len(nums)
        if nums_len == 1:
            return nums[0]
        if nums_len == 2:
            return max(nums[0], nums[1])
        ppdp = nums[0]                 # previous previous dp
        pdp = max(nums[0], nums[1])    # previous dp
        for i in range(2, nums_len):
            dp = max(nums[i] + ppdp, pdp)
            ppdp = pdp
            pdp = dp
        return dp


#### end solution

if __name__ == '__main__':
    nums1 = [1,2,3,1]
    # 4 ([0] + [2])

    nums2 = [2,7,9,3,1]
    # 12 ([0] + [2] + [4])

    solution = Solution()

    print(f'solution.rob({nums1}):',
          f'{solution.rob(nums1)}')
    # 4 ([0] + [2])

    print(f'solution.rob({nums2}):',
          f'{solution.rob(nums2)}')
    # 12 ([0] + [2] + [4])
