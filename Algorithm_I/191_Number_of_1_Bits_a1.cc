#include <iostream>


// Time to complete: 5 mins

// Needed to research:

// Note: Was already familiar with STL bitsets from designing a integer
//   compresion scheme for serializing a binary tree in LC 449.
//
//   In Ubuntu 20.04, gcc C++ bitset.count uses __builtin_popcountl, a
//   relative of __builtin_popcount, a gcc builtin which calls the assembly
//   POPCNT. So for C++, C, and ASM, this can be solved trivially by knowing
//   the proper command, which may bypass the LeetCode intention of solving
//   this with bitshifting.
//
//   In researching __builtin_popcount, found that as of C++20 one could use
//   std::popcount from <bits> as well.

//// Begin solution, results at https://leetcode.com/submissions/detail/745608732/


#include <bitset>


class Solution {
public:
    // input must be a binary string of length 32.
    // how to best optimize this function?
    /*
     * Returns the number of '1' bits in an unsigned integer (also known as
     * the Hamming weight.)
     */
    int hammingWeight(uint32_t n) {
        return std::bitset<32>(n).count();
    }
};


//// end solution


int main() {
    uint32_t n1 {11};
    uint32_t n2 {128};
    uint32_t n3 {4294967293};

    Solution solution;

    std::cout << std::boolalpha;

    std::cout << "solution.hammingWeight(" << n1 <<
        "): " << solution.hammingWeight(n1) << '\n';
    // 3 (00000000000000000000000000001011)

    std::cout << "solution.hammingWeight(" << n2 <<
        "): " << solution.hammingWeight(n2) << '\n';
    // 1 (00000000000000000000000010000000)

    std::cout << "solution.hammingWeight(" << n3 <<
        "): " << solution.hammingWeight(n3) << '\n';
    // 31 (11111111111111111111111111111101)
}
