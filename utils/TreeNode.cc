#include "TreeNode.hh"


#include <algorithm>  // max
#include <queue>
#include <sstream>
#include <stdexcept>
#include <cstring>    // strcmp
#include <cctype>     // isdigit
#include <string>     // getline
#include <cstdint>    // uint32_t


namespace LeetCodeUtils {


void TreeNode::deleteTree(const TreeNode *root, bool delete_root) {
    if (root == nullptr)
        return;
    deleteTree(root->left, delete_root);
    deleteTree(root->right, delete_root);
    if (root != this || delete_root)
        delete root;
}

uint32_t TreeNode::treeSize(const TreeNode *root) {
    if (root == nullptr)
        return 0;
    return 1 + treeSize(root->left) + treeSize(root->right);
}

uint32_t TreeNode::treeHeight(const TreeNode *root) {
    if (root == nullptr)
        return 0;
    return 1 + std::max(treeHeight(root->left), treeHeight(root->right));
}

bool TreeNode::deserializeNode(TreeNode *node, std::queue<TreeNode *> &q,
                               std::istringstream &iss, bool left) {
    char buff[5] {};
    char c (iss.get()), peek;
    if (iss.eof())
        return false;
    switch (c) {
    case ']':
        c = iss.get();
        if (!iss.eof())
            throw std::invalid_argument("trailing chars after ending ']'");
        return false;
    case ',':
        peek = iss.peek();
        if (peek == 'n') {
            iss.read(buff, 4);
            if (strcmp(buff, "null") != 0)
                throw std::invalid_argument(
                    "string format error reading \"null\"");
        } else if (peek == '-' || std::isdigit(peek)) {
            if (left) {
                node->left = new TreeNode;
                iss >> node->left->val;
                q.emplace(node->left);
            } else {
                node->right = new TreeNode;
                iss >> node->right->val;
                q.emplace(node->right);
            }
        } else {
            throw std::invalid_argument("string format error reading node");
        }
        return true;
    default:
        throw std::invalid_argument("string format error reading ','");
        break;
    }
    return false;
}

void TreeNode::treeFromString(std::string &s, TreeNode *root) {
    if (root == nullptr)
        return;
    // LC format is "[x,y,z,null]" with node values in level order
    std::istringstream iss {s};
    if (iss.get() != '[')
        throw std::invalid_argument("string format error reading '['");
    char peek (iss.peek());
    if (peek == ']')
        throw std::length_error("empty tree representation \"[]\"");
    else if (peek == '-' || std::isdigit(peek))
        iss >> root->val;
    else
        throw std::invalid_argument("string format error reading root");
    std::queue<TreeNode *> q;
    q.emplace(root);
    TreeNode *curr;
    while (q.size() > 0) {
        curr = q.front();
        q.pop();
        if (!deserializeNode(curr, q, iss, true) ||
            !deserializeNode(curr, q, iss, false))
            return;
    }
}

void TreeNode::stringFromTreeRecursion(const TreeNode *root, std::ostringstream &oss,
                                       const uint32_t level, const uint32_t target,
                                       uint32_t &visited, const uint32_t node_ct) {
    if (visited == node_ct)
        return;
    if (level == target) {
        if (root == nullptr) {
            oss << "null";
        } else {
            oss << root->val;
            ++visited;
        }
        if (visited < node_ct)
            oss << ',';
    }
    if (root != nullptr) {
        stringFromTreeRecursion(root->left, oss,
                                level + 1, target, visited, node_ct);
        stringFromTreeRecursion(root->right, oss,
                                level + 1, target, visited, node_ct);
    }
}

std::string TreeNode::stringFromTree(const TreeNode *root) {
    // format is "[x,y,z,null]" with node values in level order
    uint32_t height {treeHeight(root)};
    uint32_t node_ct {treeSize(root)};
    uint32_t visited {0};
    std::ostringstream oss;
    oss << '[';
    for (uint32_t i {0}; i < height; ++i)
        stringFromTreeRecursion(root, oss, 0, i, visited, node_ct);
    oss << ']';
    return oss.str();
}


std::ostream &operator<<(std::ostream &os, TreeNode &root) {
    // root not const as `this` discards qualifiers
    return os << root.str();
}


std::ostream &operator<<(std::ostream &os, TreeNode *root) {
    // root not const as `this` discards qualifiers
    return operator<<(os, *root);
}


std::istream &operator>>(std::istream &is, TreeNode &root) {
        // ensure leading whitespace skipped
	is >> std::ws;
        // grab level order array representation string
	std::string tree_str;
        std::getline(is, tree_str, ']');
	if (!is.good())
            return is;  // throw exception?
        // replace trailing delimiter
        tree_str.push_back(']');
        // empty target tree
        if (root.size())
            root.erase(false);
        // deserialize tree
        try {
            root.treeFromString(tree_str, &root);
        } catch (const std::exception &e) {
            root.erase(false);
            throw;
        }
	return is;
}


std::istream &operator>>(std::istream &is, TreeNode *root) {
    if (root == nullptr)
        throw std::invalid_argument("cannot stream into nullptr");
    return operator>>(is, *root);
}


}  // namespace LeetCodeUtils
