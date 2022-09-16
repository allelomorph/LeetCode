#include <iostream>

#include "TreeNode.hh"

using TreeNode = LeetCodeUtils::TreeNode;


// Time to complete: 1.5 hrs

// Needed to research:

// Notes:
//   - At first tried to build record of node value instances from leaves back
//       to root, returning a list of maps/arrays
//   - Performance was middling, are there any optimizations that do not
//       require copying the array `paths` at every recursion? When checking for
//       permutations of path values it seems difficult to not record all instances...

//// Begin solution, results at https://leetcode.com/submissions/detail/800641712/


#include <array>
#include <cstdint>


// number of nodes in the tree is in the range [1, 10^5].
// 1 <= Node.val <= 9
class Solution {
private:
    int tracePathValues(const TreeNode *root, std::array<uint32_t, 10> path) {
        if (root == nullptr)
            return 0;
        ++path[root->val];
        // only check pseudopalindrome at leaf
        if (root->left == nullptr && root->right == nullptr) {
            bool odd_ct_found {false};
            // pseudopalindromes can only have one value appear an odd number of times
            for (const auto &instances : path) {
                if (instances % 2 != 0) {
                    if (odd_ct_found)
                        return 0;
                    else
                        odd_ct_found = true;
                }
            }
            return 1;
        }
        return tracePathValues(root->left, path) + tracePathValues(root->right, path);
    }
public:
    int pseudoPalindromicPaths (const TreeNode *root) {
        return tracePathValues(root, std::array<uint32_t, 10> {});
    }
};


/// end solution


int main(void) {
    Solution solution;

    // Input: root = [2,3,1,3,1,null,1]
    TreeNode *root1 {new TreeNode("[2,3,1,3,1,null,1]")};
    std::cout << "solution.pseudoPalindromicPaths(" << root1 << "): " <<
        solution.pseudoPalindromicPaths(root1) << " expected: 2" << std::endl;
    // Output: 2

    // Input: root = [2,1,1,1,3,null,null,null,null,null,1]
    TreeNode *root2 {new TreeNode("[2,1,1,1,3,null,null,null,null,null,1]")};
    std::cout << "solution.pseudoPalindromicPaths(" << root2 << "): " <<
        solution.pseudoPalindromicPaths(root2) << " expected: 1" << std::endl;
    // Output: 1

    // Input: root = [9]
    TreeNode *root3 {new TreeNode("[9]")};
    std::cout << "solution.pseudoPalindromicPaths(" << root3 << "): " <<
        solution.pseudoPalindromicPaths(root3) << " expected: 1" << std::endl;
    // Output: 1

}
