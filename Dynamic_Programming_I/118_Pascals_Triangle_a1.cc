#include <vector>
#include <iostream>


//// Begin solution, results at https://leetcode.com/submissions/detail/699215561/


class Solution {
public:
    const std::vector<std::vector<int>> generate(const int numRows) {
        // 1 <= numRows <= 30
        std::vector<std::vector<int>> pt { {1} };   // Pascal's triangle
        if (numRows == 1)
            return pt;
        pt.push_back(std::vector<int> {1, 1});
        for (auto i {2}; i < numRows; ++i) {
            pt.push_back(std::vector<int> {{1}});
            const int sz (pt[i - 1].size());
            for (int j {1}; j < sz; ++j) {
                pt[i].push_back(pt[i - 1][j] + pt[i - 1][j - 1]);
            }
            pt[i].push_back(1);
        }
        return pt;
    }
};


//// end solution


void PrintNestedIntVector(const std::vector<std::vector<int>> &nv) {
    std::cout << "{ ";
    for (const auto &v : nv) {
        std::cout << "{ ";
        for (const auto &num : v)
            std::cout << num << ' ';
        std::cout << " }";
    }
    std::cout << " }";
}


int main() {
    Solution s;

    std::cout << "(5): ";
    PrintNestedIntVector(s.generate(5));
    std::cout << std::endl;
    std::cout << "(1): ";
    PrintNestedIntVector(s.generate(1));
    std::cout << std::endl;
}
