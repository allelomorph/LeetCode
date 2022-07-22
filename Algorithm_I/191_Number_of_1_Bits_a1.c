#include <stdio.h>
#include <stdint.h>


// Time to complete: (copied from example)

// Needed to research:

// Note: As noted in 191_Number_of_1_Bits_a1.cc, this can be solved in one
//   line by calling gcc builtin __builtin_popcount. Obviously using a single
//   CPU instruction with POPCNT is best, but for the purposes of better
//   learning bitshifting, here instead is a solution found at
//   https://stackoverflow.com/a/9947906.

//// Begin solution, results at https://leetcode.com/submissions/detail/745610360/


// input must be a binary string of length 32.
// how to best optimize this function?
/*
 * Returns the number of '1' bits in an unsigned integer (also known as
 * the Hamming weight.)
 */
int hammingWeight(uint32_t n) {
    // We can consider each bit in n as a one-bit integer indicating how many
    //   bits are set in that bit.

    // 0xAAAAAAAA = 10101010...10101010
    // 0x55555555 = 01010101...01010101
    n = ((n & 0xAAAAAAAA) >> 1) + (n & 0x55555555);
    // Now every two bits are a two bit integer indicating how many bits were
    //   orignally set in those two bits.

    // 0xCCCCCCCC = 11001100...11001100
    // 0x33333333 = 00110011...00110011
    n = ((n & 0xCCCCCCCC) >> 2) + (n & 0x33333333);
    // Same again at every 4...

    // 0xF0F0F0F0 = 11110000...11110000
    // 0x0F0F0F0F = 00001111...00001111
    n = ((n & 0xF0F0F0F0) >> 4) + (n & 0x0F0F0F0F);
    // 8...

    n = ((n & 0xFF00FF00) >> 8) + (n & 0x00FF00FF);
    // 16...

    n = ((n & 0xFFFF0000) >> 16) + (n & 0x0000FFFF);
    // and finally 32, for our return value.

    return (int)n;
}


//// end solution


int main(void) {
    uint32_t n1 = 11;
    uint32_t n2 = 128;
    uint32_t n3 = 4294967293;

    printf("hammingWeight(%u): %i\n", n1, hammingWeight(n1));
    // 3 (00000000000000000000000000001011)

    printf("hammingWeight(%u): %i\n", n2, hammingWeight(n2));
    // 1 (00000000000000000000000010000000)

    printf("hammingWeight(%u): %i\n", n3, hammingWeight(n3));
    // 31 (11111111111111111111111111111101)
}
