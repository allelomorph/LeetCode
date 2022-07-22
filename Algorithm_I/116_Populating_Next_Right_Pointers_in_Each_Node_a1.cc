#include <iostream>


class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


// Time to complete: 2 hrs

// Needed to research:
//   - static class methods
//   - reference to pointer

//// Begin solution, results at https://leetcode.com/submissions/detail/742075489/


/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    /*
     * Assumes a perfect binary tree, with all leaves are on the same level
     * every non-leaf has two children.
     *
     * Populates each next pointer to point to the next node to right in level
     * order. nullptr at end of level (rightmost node.)
     */
    Node *connect(Node *root) {
        assignNextInLevelOrder(root);
        return root;
    }

    // static, as also used in local test printing functions
    static int treeHeight(const Node *root, const int level) {
        if (root == nullptr)
            return level;
        return std::max(treeHeight(root->left, level + 1),
                        treeHeight(root->right, level + 1));
    }

private:
    void assignNextInLevel(Node *root, const int level,
                           const bool rightmost) {
        static Node *prev {nullptr};
        if (root == nullptr)
            return;
        if (level == 1) {
            if (prev != nullptr)
                prev->next = root;
            prev = rightmost ? nullptr : root;
        }
        if (level > 1) {
            assignNextInLevel(root->left, level - 1, false);
            assignNextInLevel(root->right, level - 1, rightmost);
        }
    }

    void assignNextInLevelOrder(Node *root) {
        const int height {treeHeight(root, 0)};
        for (int i {0}; i <= height; ++i) {
            assignNextInLevel(root, i, true);
        }
    }
};


//// end solution


namespace Test {

void printableTreeLevel(const Node *root, const int level,
                        std::string &result) {
    if (root == nullptr)
        return;
    if (level == 1) {
        result.append(std::to_string(root->val));
        result.push_back(',');
    }
    if (level > 1) {
        printableTreeLevel(root->left, level - 1,
                           result);
        printableTreeLevel(root->right, level - 1,
                           result);
    }
}

std::string printableTreeInLevelOrder(const Node *root) {
    std::string result;
    result.push_back('[');
    const int height {Solution::treeHeight(root, 0)};
    for (int i {0}; i <= height; ++i) {
        printableTreeLevel(root, i, result);
    }
    if (result.back() == ',')
        result.back() = ']';
    else
        result.push_back(']');
    return result;
}

std::string printableTreeViaNext(Node *root) {
    std::string result;
    result.push_back('[');
    for (Node *leftmost {root}; leftmost != nullptr;
         leftmost = leftmost->left) {
        for (Node *temp {leftmost}; temp != nullptr; temp = temp->next)
            result.append(std::to_string(temp->val) + ',');
        result.append("#,");
    }
    if (result.back() == ',')
        result.back() = ']';
    else
        result.push_back(']');
    return result;
}

}  // namespace Test



int main() {
    // perfect height of 3
    Node *root1 {new Node(1)};
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);
    root1->right->left = new Node(6);
    root1->right->right = new Node(7);

    // perfect hieght of 0
    Node *root2 {nullptr};

    Solution solution;

    std::cout << "solution.connect(" << Test::printableTreeInLevelOrder(root1) <<
        "): " << Test::printableTreeViaNext(solution.connect(root1)) << '\n';
    // [1,#,2,3,#,4,5,6,7,#]

    std::cout << "solution.connect(" << Test::printableTreeInLevelOrder(root2) <<
        "): " << Test::printableTreeViaNext(solution.connect(root2)) << '\n';
    // []
}
