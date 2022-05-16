#include <vector>
#include <iostream>


//// Begin solution, results at https://leetcode.com/submissions/detail/699535575/


class Solution {
public:
    const std::vector<int> getRow(const int rowIndex) {
        // 0 <= rowIndex <= 33
        std::vector<int> pt_row;  // row in Pascal's triangle with rowIndex + 1 members
        pt_row.push_back(1);
        for (int i {0}; i < rowIndex; ++i) {
            for (int j {i}; j > 0; --j) {
                pt_row[j] += pt_row[j - 1];
            }
            pt_row.push_back(1);
        }
        return pt_row;
    }
};


//// end solution


void PrintVector(const std::vector<int> &v) {
    std::cout << "{ ";
    for (const auto &num : v)
        std::cout << num << ' ';
    std::cout << " }";
}


int main() {
    Solution s;

    std::cout << "(5): ";
    PrintVector(s.getRow(5));
    std::cout << std::endl;
    std::cout << "(3): ";
    PrintVector(s.getRow(3));
    std::cout << std::endl;
    std::cout << "(0): ";
    PrintVector(s.getRow(0));
    std::cout << std::endl;
    std::cout << "(1): ";
    PrintVector(s.getRow(1));
    std::cout << std::endl;
}
