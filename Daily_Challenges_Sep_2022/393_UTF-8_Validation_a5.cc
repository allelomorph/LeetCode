#include <iostream>
#include <vector>
#include <bitset>

#include "vector_stream_ops.hh"


template<std::size_t N>
std::ostream &operator<<(std::ostream &os, const std::bitset<N> &bs) {
    int bs_sz (bs.size());
    os << '[';
    os << std::noboolalpha;
    for (int i {bs_sz - 1}; i >= 0; --i)
        os << bs[i];
    return os << ']';
}


// Time to complete: 1.5 hrs

// Needed to research:

// Notes:

//// Begin solution, results at https://leetcode.com/submissions/detail/799235270/


#include <bitset>
#include <cstdint>  // uint8_t uint32_t


// 1 <= data.length <= 2 * 10^4
// 0 <= data[i] <= 255
class Solution {
public:
    bool validUtf8(std::vector<int>& data) {
        std::bitset<8> bits;
        uint32_t data_sz (data.size());
        for (uint32_t i {0}, follow_byte_ct {0};
             i < data_sz; follow_byte_ct = 0) {
            bits = (uint8_t)data[i];
            if (!bits[7]) {  // single byte encoding 0XXXXXXX ?
                ++i;
                continue;
            }
            for (uint8_t j {6}; j > 2 && bits[j]; --j, ++follow_byte_ct) {}
            if (follow_byte_ct == 0 || follow_byte_ct > 3 ||
                follow_byte_ct > data_sz - i - 1)
                return false;
            for (uint8_t j {1}; j <= follow_byte_ct; ++j) {
                bits = (uint8_t)data[i + j];
                if (!bits[7] || bits[6])  // is follow byte 10XXXXXX ?
                    return false;
            }
            i += 1 + follow_byte_ct;
        }
        return true;
    }
};


/// end solution


int main(void) {
    std::vector<int> v1 {197,130,1};
    std::vector<int> v2 {235,140,4};
    std::vector<int> v3 {237};
    std::vector<int> v4 {145};
    std::vector<int> v5 {115,100,102,231,154,132,13,10};

    Solution solution;

    // Input: data = [197,130,1] le (11000101 10000010 00000001)
    std::cout << "solution.validUtf8(" << v1 << "): " <<
        std::boolalpha << solution.validUtf8(v1) << std::endl;
    // Output: true

    // Input: data = [235,140,4] le (11101011 10001100 00000100)
    std::cout << "solution.validUtf8(" << v2 << "): " <<
        std::boolalpha << solution.validUtf8(v2) << std::endl;
    // Output: false

    // Input: data = {237} (11101101)
    std::cout << "solution.validUtf8(" << v3 << "): " <<
        std::boolalpha << solution.validUtf8(v3) << std::endl;
    // Output: false

    // Input: data = {145} (10010001)
    std::cout << "solution.validUtf8(" << v4 << "): " <<
        std::boolalpha << solution.validUtf8(v4) << std::endl;
    // Output: false

    // Input: data = {115,100,102,231,154,132,13,10}
    //   (01110011 01100100 01100110 11100111 10011010 10000100 00001101 00001010)
    std::cout << "solution.validUtf8(" << v5 << "): " <<
        std::boolalpha << solution.validUtf8(v5) << std::endl;
    // Output: false
}
