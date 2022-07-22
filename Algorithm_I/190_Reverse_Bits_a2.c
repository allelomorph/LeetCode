#include <stdio.h>
#include <stdint.h>  // uint32_t


// Time to complete: 10 mins

// Needed to research:

//// Begin solution, results at https://leetcode.com/submissions/detail/746496828/


// input must be a binary string of length 32
// how would this be optimized with bitshifting?
/*
 * Reverses the bits of a given 32 bit unsigned integer.
 */
uint32_t reverseBits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; ++i)
        result |= ((n >> i) & 1) << (31 - i);
    return result;
}


//// end solution


int main() {
    uint32_t n1 = 43261596;    // 00000010100101000001111010011100
    uint32_t n2 = 4294967293;  // 11111111111111111111111111111101

    printf("reverseBits(%u): %u\n", n1, reverseBits(n1));
    // 964176192                 (00111001011110000010100101000000)

    printf("reverseBits(%u): %u\n", n2, reverseBits(n2));
    // 3221225471                (10111111111111111111111111111111)
}
