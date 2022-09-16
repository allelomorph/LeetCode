#include "TreeNode.hh"

using LeetCodeUtils::TreeNode;

#include <iostream>
#include <vector>


// Time to complete: 1 hr (!)

// Needed to research:
//   - emplace_back vs push_back
//   - refresh on level order traversal, before abandoning

// Notes:
//   - does not manage memory leaks from pruned nodes / returning nullptr from pruneTree

//// Begin solution, results at https://leetcode.com/submissions/detail/790032750/


// number of nodes in the tree is in the range [1, 200].
// Node.val is either 0 or 1.
// test program seems to use smart pointers, no explicit deletion of tree is necessary (?)
class Solution {
private:
    bool treeContainsOne(TreeNode *root) {
        if (root == nullptr)
            return false;
        if (root->val == 1)
            return true;
        return treeContainsOne(root->left) || treeContainsOne(root->right);
    }

    void pruneTreeTraverse(TreeNode *root) {
        if (root == nullptr)
            return;
        if (root->left && !treeContainsOne(root->left))
            root->left = nullptr;
        if (root->right && !treeContainsOne(root->right))
            root->right = nullptr;
        pruneTreeTraverse(root->left);
        pruneTreeTraverse(root->right);
    }

public:
    TreeNode *pruneTree(TreeNode *root) {
        if (!treeContainsOne(root))
            return nullptr;
        pruneTreeTraverse(root);
        return root;
    }
};


//// end solution


int main() {
    TreeNode *root_1 = new TreeNode("[1,null,0,0,1]");
    TreeNode *root_2 = new TreeNode("[1,0,1,0,0,0,1]");
    TreeNode *root_3 = new TreeNode("[1,1,0,1,1,0,1,0]");

    Solution solution;

    std::cout << "solution.pruneTree(" << root_1 << "): " <<
        solution.pruneTree(root_1) <<
        " expected: " << "[1,null,0,null,1]" << std::endl;

    std::cout << "solution.pruneTree(" << root_2 << "): " <<
        solution.pruneTree(root_2) <<
        " expected: " << "[1,null,1,null,1]" << std::endl;

    std::cout << "solution.pruneTree(" << root_3 << "): " <<
        solution.pruneTree(root_3) <<
        " expected: " << "[1,1,0,1,1,null,1]" << std::endl;

    root_1->erase();
    root_2->erase();
    root_3->erase();
}
