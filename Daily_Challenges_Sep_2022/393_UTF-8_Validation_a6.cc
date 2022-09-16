#include <iostream>
#include <vector>

#include "vector_stream_ops.hh"


// Time to complete: 1.5 hrs

// Needed to research:

// Notes:

//// Begin solution, results at https://leetcode.com/submissions/detail/799243063/


#include <cstdint>  // uint8_t uint32_t


// 1 <= data.length <= 2 * 10^4
// 0 <= data[i] <= 255
class Solution {
public:
    bool validUtf8(std::vector<int>& data) {
        uint32_t data_sz (data.size());
        for (uint32_t i {0}, follow_byte_ct {0};
             i < data_sz; follow_byte_ct = 0) {
            if (!(data[i] & 1 << 7)) {  // single byte encoding 0XXXXXXX ?
                ++i;
                continue;
            }
            for (uint8_t j {6}; j > 2 && (data[i] & 1 << j);
                 --j, ++follow_byte_ct) {}
            if (follow_byte_ct == 0 || follow_byte_ct > 3 ||
                follow_byte_ct > data_sz - i - 1)
                return false;
            for (uint8_t j {1}; j <= follow_byte_ct; ++j) {
                if (((data[i + j] >> 6) & 2) != 2)  // is follow byte 10XXXXXX ?
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
