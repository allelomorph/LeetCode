#include <iostream>
#include <vector>


template<typename T>
const std::string printableNestedVector(
    const std::vector<std::vector<T>> &nv) {
    std::string result;
    result.push_back('[');
    for (const auto &v: nv) {
        result.push_back('[');
        for (const auto &o: v) {
            result.append(std::to_string(o) + ",");
        }
        if (result.back() == ',')
            result.back() = ']';
        else
            result.push_back(']');
        result.push_back(',');
    }
    if (result.back() == ',')
        result.back() = ']';
    else
        result.push_back(']');
    return result;
}


// Definition for a Node.
class Node {
public:
    int val;
    std::vector<Node *> children;

    Node() {}
    Node(int v) : val(v) {}
    Node(int v, std::vector<Node *> c) : val(v), children(c) {}
};


// Time to complete: 45 mins

// Needed to research:
//   - max_element

// Notes:
//   - simply grafted conventional level-order traversal for a binary tree to N-ary
//     child list

//// Begin solution, results at https://leetcode.com/submissions/detail/791752796/


#include <algorithm>  // max


// height of the n-ary tree is less than or equal to 1000
// total number of nodes is between [0, 104]
class Solution {
private:
    int treeHeight(const Node *root) {
        if (root == nullptr)
            return 0;
        if (root->children.size() == 0)
            return 1;
        int max_subtree_height {0};
        for (const auto &child : root->children)
            max_subtree_height = std::max(max_subtree_height, treeHeight(child));
        return max_subtree_height + 1;
    }

    void levelOrderTraverse(const Node *root, int i, int row_i,
                            std::vector<int> &row_vals) {
        if (root == nullptr)
            return;
        if (i < row_i) {
            for (const auto &child: root->children)
                levelOrderTraverse(child, i + 1, row_i, row_vals);
        }
        if (i == row_i) {
            row_vals.emplace_back(root->val);
        }
    }

public:
    std::vector<std::vector<int>> levelOrder(const Node *root) {
        std::vector<std::vector<int>> result;
        int height {treeHeight(root)};
        std::vector<int> row;
        for (int i {0}; i < height; ++i) {
            levelOrderTraverse(root, 0, i, row);
            result.emplace_back(row);
            row.clear();
        }
        return result;
    }
};


//// end solution


void deleteTree(const Node *root) {
    if (root == nullptr)
        return;
    for (const auto &child: root->children)
        deleteTree(child);
    delete root;
}


int main() {
    Node *root_1 = new Node(1);
    root_1->children = std::vector<Node *> {new Node(3), new Node(2), new Node(4)};
    root_1->children[0]->children = std::vector<Node *> {new Node(5), new Node(6)};

    Node *root_2 = new Node(1);
    root_2->children = std::vector<Node *> {new Node(2), new Node(3), new Node(4), new Node(5)};
    root_2->children[1]->children = std::vector<Node *> {new Node(6), new Node(7)};
    root_2->children[2]->children = std::vector<Node *> {new Node(8)};
    root_2->children[3]->children = std::vector<Node *> {new Node(9), new Node(10)};
    root_2->children[1]->children[1]->children = std::vector<Node *> {new Node(11)};
    root_2->children[2]->children[0]->children = std::vector<Node *> {new Node(12)};
    root_2->children[3]->children[0]->children = std::vector<Node *> {new Node(13)};
    root_2->children[1]->children[1]->children[0]->children = std::vector<Node *> {new Node(14)};

    Solution solution;

    // root = [1,null,3,2,4,null,5,6]
    std::cout << "solution.levelOrder([1,null,3,2,4,null,5,6]): \n" <<
        printableNestedVector(solution.levelOrder(root_1)) << std::endl;
    // Output: [[1],[3,2,4],[5,6]]

    // Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
    std::cout << "solution.levelOrder(" <<
        "[1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]): \n" <<
        printableNestedVector(solution.levelOrder(root_2)) << std::endl;
    // Output: [[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]

    deleteTree(root_1);
    deleteTree(root_2);
}
