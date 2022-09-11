#ifndef LC_TREENODE_HH
#define LC_TREENODE_HH


#include <string>
#include <stdexcept>
#include <queue>
#include <sstream>
#include <string>
#include <cstdint>    // uint32_t
#include <iostream>


namespace LeetCodeUtils {


class TreeNode {
public:
    int       val   {0};
    TreeNode *left  {nullptr};
    TreeNode *right {nullptr};

    TreeNode() {}
    TreeNode(int x) : val(x) {}
    TreeNode(int x, TreeNode *l, TreeNode *r):
        val(x), left(l), right(r) {}

    void erase(bool delete_root = true) { deleteTree(this, delete_root); }

    // ~TreeNode() { erase(false); }

    unsigned int size() { return treeSize(this); }

    unsigned int height() { return treeHeight(this); }

    TreeNode(std::string s) {
        try {
            treeFromString(s, this);
        } catch (const std::exception &e) {
            erase(false);  // root is automatically deleted when `new` constructor fails
            throw;
        }
    }

    std::string str() { return stringFromTree(this); }

private:
    void deleteTree(const TreeNode *root, bool delete_root);

    uint32_t treeSize(const TreeNode *root);

    uint32_t treeHeight(const TreeNode *root);

    bool deserializeNode(TreeNode *node, std::queue<TreeNode *> &q,
                         std::istringstream &iss, bool left);

    void treeFromString(std::string &s, TreeNode *root);

    void stringFromTreeRecursion(const TreeNode *root, std::ostringstream &oss,
                                 const uint32_t level, const uint32_t target,
                                 uint32_t &visited, const uint32_t node_ct);

    std::string stringFromTree(const TreeNode *root);

    friend std::ostream &operator<<(std::ostream &os, TreeNode &root);
    friend std::ostream &operator<<(std::ostream &os, TreeNode *root);

    friend std::istream &operator>>(std::istream &is, TreeNode &root);
    friend std::istream &operator>>(std::istream &is, TreeNode *root);
};


}  // namespace LeetCodeUtils


#endif  // LC_TREENODE_HH




// TBD: Use STL smart pointers to move away from manual use of `new` and
// `delete`. std::shared_ptr seems to work best for the node members, with
// std::unique_ptr used when declaring the root. With this method, the tree
// will automatically deallocate, but so far seems hard to reconcile with being
// backward compatible with the default `TreeNode`. For example, `.reset()` or
// `= std::shared_ptr<TreeNode>` is needed when reassigning `left` or `right`.


/*
TreeNode.hh:

#include <memory>  // shared_ptr

class TreeNode {
public:
    int                       val   {0};
    std::shared_ptr<TreeNode> left  {nullptr};
    std::shared_ptr<TreeNode> right {nullptr};

    TreeNode() {}
    TreeNode(int x) : val(x) {}
    TreeNode(int x, TreeNode *l, TreeNode *r):
        val(x), left(l), right(r) {}

    void set_left(TreeNode *root) { this->left.reset(root); }
    void set_right(TreeNode *root) { this->right.reset(root); }
};


main.cc:

#include <memory>  // unique_ptr

int main() {
    std::unique_ptr<TreeNode> root_1(new TreeNode);
    std::cout << root_1->val << ' ' <<
        root_1->left << ' ' << root_1->right << '\n';

    std::unique_ptr<TreeNode> root_2(new TreeNode(10));
    std::cout << root_2->val << ' ' <<
        root_2->left << ' ' << root_2->right << '\n';

    std::unique_ptr<TreeNode> root_3(new TreeNode(10));
    // root_3->set_left(new TreeNode(8));
    // root_3->set_right(new TreeNode(13));
    root_3->left =  std::shared_ptr<TreeNode> (new TreeNode(8));
    root_3->right = std::shared_ptr<TreeNode> (new TreeNode(13));

    std::cout << root_3->val << ' ' <<
        root_3->left->val << ' ' << root_3->right->val << '\n';
}
*/
