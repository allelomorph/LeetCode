#include <iostream>
#include <vector>


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
                                                       right(right) {}
};


// Time to complete: 30 mins

// Needed to research:

//// Begin solution, results at https://leetcode.com/submissions/detail/746542528/


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
public:
    std::vector<int> rightSideView(TreeNode* root) {
        const int height {treeHeight(root, 0)};
        std::vector<int> values(height, 0);
        for (int i {0}; i <= height; ++i)
            nodeValuesInLevel(root, i, values, i);
        return values;
    }

    // static, as also used in local test printing functions
    static int treeHeight(const TreeNode *root, const int level) {
        if (root == nullptr)
            return level;
        return std::max(treeHeight(root->left, level + 1),
                        treeHeight(root->right, level + 1));
    }

private:
    void nodeValuesInLevel(const TreeNode *root, const int frame,
                               std::vector<int> &values, const int level) {
        if (root == nullptr)
            return;
        if (frame == 1)
            values[level] = root->val;
        if (frame > 1) {
            nodeValuesInLevel(root->left, frame - 1, values, level);
            nodeValuesInLevel(root->right, frame - 1, values, level);
        }
    }
};


//// end solution


namespace Test {

template<typename T>
const std::string printableVector(std::vector<T> v) {
    std::string result;
    result.push_back('[');
    for (const auto &o: v)
        result.append(std::to_string(o) + ",");
    result.back() = ']';  // overwrite last ','
    return result;
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
    const int height {Solution::treeHeight(root, 0)};
    for (int i {1}; i <= height; ++i) {
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
    TreeNode *root1 {new TreeNode(1)};
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->right = new TreeNode(5);
    root1->right->right = new TreeNode(4);

    TreeNode *root2 {new TreeNode(1)};
    root2->right = new TreeNode(3);

    TreeNode *root3 {nullptr};

    TreeNode *root4 {new TreeNode(1)};
    root4->left = new TreeNode(2);
    root4->right = new TreeNode(3);
    root4->left->left = new TreeNode(4);

    TreeNode *root5 {new TreeNode(1)};
    root5->left = new TreeNode(2);
    root5->right = new TreeNode(3);
    root5->left->right = new TreeNode(5);

    Solution solution;

    std::cout << "solution.rightSideView(" <<
        Test::printableTreeInLevelOrder(root1) << "): " <<
        Test::printableVector(solution.rightSideView(root1)) << '\n';
    // [1,3,4]

    std::cout << "solution.rightSideView(" <<
        Test::printableTreeInLevelOrder(root2) << "): " <<
        Test::printableVector(solution.rightSideView(root2)) << '\n';
    // [1,3]

    std::cout << "solution.rightSideView(" <<
        Test::printableTreeInLevelOrder(root3) << "): " <<
        Test::printableVector(solution.rightSideView(root3)) << '\n';
    // []

    std::cout << "solution.rightSideView(" <<
        Test::printableTreeInLevelOrder(root4) << "): " <<
        Test::printableVector(solution.rightSideView(root4)) << '\n';
    // [1,3,4]

    std::cout << "solution.rightSideView(" <<
        Test::printableTreeInLevelOrder(root5) << "): " <<
        Test::printableVector(solution.rightSideView(root5)) << '\n';
    // [1,3,5]
}
