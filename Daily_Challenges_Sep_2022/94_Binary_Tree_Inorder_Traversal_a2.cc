#include "TreeNode.hh"

using LeetCodeUtils::TreeNode;

#include <iostream>
#include <vector>


// Time to complete: ~2 hrs before looking for solutions

// Needed to research:
//   - https://www.techiedelight.com/inorder-tree-traversal-iterative-recursive

// Notes:
//   - recursive much faster at 3ms vs 11ms for iterative:
//       https://leetcode.com/submissions/detail/794504940/


//// Begin solution, results at https://leetcode.com/submissions/detail/794518033/


// number of nodes in the tree is in the range [0, 100]
// -100 <= Node.val <= 100
// Follow-up: iterative solution
class Solution {
private:
    void inorderTraversalRecursion(const TreeNode *root, std::vector<int> &v) {
        if (root == nullptr)
            return;
        inorderTraversalRecursion(root->left, v);
        v.emplace_back(root->val);
        inorderTraversalRecursion(root->right, v);
    }

    void inorderTraversalIteration(TreeNode *root, std::vector<int> &v) {
        std::stack<TreeNode *> stk {};
        for (TreeNode *curr {root}; !stk.empty() || curr != nullptr;) {
            if (curr != nullptr) {
                stk.emplace(curr);
                curr = curr->left;
            } else {
                curr = stk.top();
                stk.pop();
                v.emplace_back(curr->val);
                curr = curr->right;
            }
        }
    }

public:
    std::vector<int> inorderTraversal(const TreeNode *root) {
        std::vector<int> result;
        // inorderTraversalRecursion(root, result);
        inorderTraversalIteration(const_cast<TreeNode *>(root), result);
        return result;
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
