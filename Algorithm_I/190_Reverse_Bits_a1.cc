#include <iostream>


// Time to complete: 5 mins

// Needed to research:

//// Begin solution, results at https://leetcode.com/submissions/detail/746496538/


#include <bitset>


class Solution {
public:
    // input must be a binary string of length 32
    // how would this be optimized with bitshifting?
    /*
     * Reverses the bits of a given 32 bit unsigned integer.
     */
    uint32_t reverseBits(uint32_t n) {
        std::bitset<32> n_bits(n);
        std::bitset<32> result;
        for (int i {0}, j {31}; i < 32; ++i, --j)
            result[j] = n_bits[i];
        return uint32_t(result.to_ulong());
    }
};


//// end solution


int main() {
    uint32_t n1 {43261596};    // 00000010100101000001111010011100
    uint32_t n2 {4294967293};  // 11111111111111111111111111111101

    Solution solution;

    std::cout << "solution.reverseBits(" << n1 <<
        "): " << solution.reverseBits(n1) << '\n';
    // 964176192                 (00111001011110000010100101000000)

    std::cout << "solution.reverseBits(" << n2 <<
        "): " << solution.reverseBits(n2) << '\n';
    // 3221225471                (10111111111111111111111111111111)
}
