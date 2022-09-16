#include "TreeNode.hh"

using LeetCodeUtils::TreeNode;

#include <iostream>
#include <vector>


// Time to complete: ~30 mins

// Needed to research:

// Notes:
//   - struggled for some time with how this preorder method differs from the
//       LC standard level-order vector representation, in particular which
//       null children are represented


//// Begin solution, results at https://leetcode.com/submissions/detail/794258416/


#include <sstream>    // ostringstream

// number of nodes in the tree is in the range [1, 104].
// -1000 <= Node.val <= 1000
class Solution {
private:
    void tree2strTraversal(const TreeNode *root, std::ostringstream &oss) {
        if (root == nullptr)
            return;
        oss << root->val;
        if (root->left == nullptr && root->right == nullptr)
            return;
        oss << '(';
        tree2strTraversal(root->left, oss);
        oss << ')';
        if (root->right != nullptr) {
            oss << '(';
            tree2strTraversal(root->right, oss);
            oss << ')';
        }
    }
public:
    std::string tree2str(const TreeNode *root) {
        std::ostringstream result;
        tree2strTraversal(root, result);
        return result.str();
    }
};


//// end solution


int main() {
    TreeNode *root_1 = new TreeNode("[1,2,3,4]");
    TreeNode *root_2 = new TreeNode("[1,2,3,null,4]");

    Solution solution;

    std::cout << "solution.tree2str(" << root_1 << "): " <<
        solution.tree2str(root_1) <<
        " expected: " << "1(2(4))(3)" << std::endl;

    std::cout << "solution.tree2str(" << root_2 << "): " <<
        solution.tree2str(root_2) <<
        " expected: " << "1(2()(4))(3)" << std::endl;

    root_1->erase();
    root_2->erase();
}
