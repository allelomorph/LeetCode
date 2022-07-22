#include <iostream>


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
                                                       right(right) {}
};


// Time to complete: 1.5 hrs

// Needed to research:

//// Begin solution, results at https://leetcode.com/submissions/detail/741918809/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 *                                                        right(right) {}
 * };
 */
class Solution {
    /*
     * Merges two binary trees, as if the two had been overlapped and each node
     * in the merged tree contained the sum of the the two other trees' nodes
     * at that location. In the case of only one tree having a node at that
     * location, that value goes into the merged tree.
     */
    // number of nodes in both trees is in the range [0, 2000].
    // -10^4 <= Node.val <= 10^4
public:
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2) {
        TreeNode *merge_root {nullptr};
        if (root1 && !root2)
            merge_root = new TreeNode(root1->val);
        else if (!root1 && root2)
            merge_root = new TreeNode(root2->val);
        else if (root1 && root2)
            merge_root = new TreeNode(root1->val + root2->val);
        mergeTreesPreOrder(root1, root2, merge_root);
        return merge_root;
    }
private:
    void mergeTreesPreOrder(TreeNode *root1, TreeNode *root2,
                            TreeNode *merge_root) {
        if (!merge_root)
            return;
        bool viable_r1L {(root1 && root1->left)};
        bool viable_r1R {(root1 && root1->right)};
        bool viable_r2L {(root2 && root2->left)};
        bool viable_r2R {(root2 && root2->right)};
        if (!viable_r1L && viable_r2L)
            merge_root->left = new TreeNode(root2->left->val);
        else if (viable_r1L && !viable_r2L)
            merge_root->left = new TreeNode(root1->left->val);
        else if (viable_r1L && viable_r2L)
            merge_root->left = new TreeNode(root1->left->val + root2->left->val);
        if (!viable_r1R && viable_r2R)
            merge_root->right = new TreeNode(root2->right->val);
        else if (viable_r1R && !viable_r2R)
            merge_root->right = new TreeNode(root1->right->val);
        else if (viable_r1R && viable_r2R)
            merge_root->right = new TreeNode(root1->right->val + root2->right->val);
        mergeTreesPreOrder(root1 ? root1->left : nullptr,
                           root2 ? root2->left : nullptr,
                           merge_root->left);
        mergeTreesPreOrder(root1 ? root1->right : nullptr,
                           root2 ? root2->right : nullptr,
                           merge_root->right);
    }
};


//// end solution


namespace Test {

int treeHeight(const TreeNode *root, int level) {
    if (root == nullptr)
        return level;
    return std::max(treeHeight(root->left, level + 1),
                    treeHeight(root->right, level + 1));
}

void printableTreeLevel(const TreeNode *root, const int level,
                        std::string &result, bool null_left_child) {

    if (root == nullptr) {
        if (null_left_child)
            result.append("null,");
        return;
    }
    if (level == 1) {
        result.append(std::to_string(root->val) + ",");
    }
    if (level > 1) {
        printableTreeLevel(root->left, level - 1,
                           result,
                           (root->left == nullptr && root->right != nullptr));
        printableTreeLevel(root->right, level - 1,
                           result, false);
    }
}

std::string printableTreeInLevelOrder(const TreeNode *root) {
    std::string result;
    result.push_back('[');
    const int height {treeHeight(root, 0)};
    for (int i {0}; i <= height; ++i) {
        printableTreeLevel(root, i, result, false);
    }
    if (result.back() == ',')
        result.back() = ']';
    else
        result.push_back(']');
    return result;
}


}  // namespace Test


int main() {
    TreeNode *root1_1 {new TreeNode(1)};
    root1_1->left = new TreeNode(3);
    root1_1->right = new TreeNode(2);
    root1_1->left->left = new TreeNode(5);

    TreeNode *root2_1 {new TreeNode(2)};
    root2_1->left = new TreeNode(1);
    root2_1->right = new TreeNode(3);
    root2_1->left->right = new TreeNode(4);
    root2_1->right->right = new TreeNode(7);

    TreeNode *root1_2 {new TreeNode(1)};

    TreeNode *root2_2 {new TreeNode(1)};
    root2_2->left = new TreeNode(2);

    TreeNode *root1_3 {new TreeNode(1)};

    TreeNode *root2_3 {nullptr};

    TreeNode *root1_4 {nullptr};

    TreeNode *root2_4 {nullptr};

    Solution solution;

    std::cout << "solution.mergeTrees(" << Test::printableTreeInLevelOrder(root1_1) <<
        ", " << Test::printableTreeInLevelOrder(root2_1) <<
        "): " << Test::printableTreeInLevelOrder(solution.mergeTrees(root1_1, root2_1)) << '\n';
    // [3,4,5,5,4,null,7]

    std::cout << "solution.mergeTrees(" << Test::printableTreeInLevelOrder(root1_2) <<
        ", " << Test::printableTreeInLevelOrder(root2_2) <<
        "): " << Test::printableTreeInLevelOrder(solution.mergeTrees(root1_2, root2_2)) << '\n';
    // [2,2]

    std::cout << "solution.mergeTrees(" << Test::printableTreeInLevelOrder(root1_3) <<
        ", " << Test::printableTreeInLevelOrder(root2_3) <<
        "): " << Test::printableTreeInLevelOrder(solution.mergeTrees(root1_3, root2_3)) << '\n';
    // [1]

    std::cout << "solution.mergeTrees(" << Test::printableTreeInLevelOrder(root1_4) <<
        ", " << Test::printableTreeInLevelOrder(root2_4) <<
        "): " << Test::printableTreeInLevelOrder(solution.mergeTrees(root1_4, root2_4)) << '\n';
    // []

}
