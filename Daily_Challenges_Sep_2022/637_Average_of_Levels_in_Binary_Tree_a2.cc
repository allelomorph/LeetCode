#include "TreeNode.hh"
#include "stringFromVector.hh"

using LeetCodeUtils::TreeNode;
using LeetCodeUtils::stringFromVector;

#include <iostream>
#include <vector>


// Time to complete: ~1 hr

// Needed to research:

// Notes:

//// Begin solution, results at https://leetcode.com/submissions/detail/790032750/


// node count is in the range [1, 10^4]
// -2^31 <= Node.val <= 2^31 - 1

class Solution {
public:
    std::vector<double> averageOfLevels(const TreeNode *root) {
        std::vector<double> lvl_avgs {};
        std::vector<unsigned short> lvl_node_cts {};
        levelAverageTraversal(root, 0, lvl_avgs, lvl_node_cts);
        for (unsigned int i {0}; i < lvl_avgs.size(); ++i)
            lvl_avgs[i] /= lvl_node_cts[i];
        return lvl_avgs;
    }
private:
    void levelAverageTraversal(const TreeNode *root, const unsigned short level,
                               std::vector<double> &lvl_avgs,
                               std::vector<unsigned short> &lvl_node_cts) {
        if (root == nullptr)
            return;
        if (lvl_avgs.size() == level)
            lvl_avgs.emplace_back(root->val);
        else
            lvl_avgs[level] += root->val;
        if (lvl_node_cts.size() == level)
            lvl_node_cts.emplace_back(1);
        else
            ++(lvl_node_cts[level]);
        levelAverageTraversal(root->left, level + 1, lvl_avgs, lvl_node_cts);
        levelAverageTraversal(root->right, level + 1, lvl_avgs, lvl_node_cts);
    }
};


//// end solution


int main() {
    TreeNode *root_1 = new TreeNode("[3,9,20,null,null,15,7]");
    TreeNode *root_2 = new TreeNode("[3,9,20,15,7]");

    Solution solution;

    std::cout << "solution.averageOfLevels(" << root_1 << "): " <<
        stringFromVector(solution.averageOfLevels(root_1)) <<
        " expected: " << "[3.00000,14.50000,11.00000]" << std::endl;

    std::cout << "solution.averageOfLevels(" << root_2 << "): " <<
        stringFromVector(solution.averageOfLevels(root_2)) <<
        " expected: " << "[3.00000,14.50000,11.00000]" << std::endl;

    root_1->erase();
    root_2->erase();
}
