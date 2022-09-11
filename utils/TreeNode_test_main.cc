#include "TreeNode.hh"

using LeetCodeUtils::TreeNode;

#include <iostream>
#include <sstream>
#include <stdexcept>


int main() {
    TreeNode *root_1 = new TreeNode;
    std::cout << "TreeNode(): " << root_1->val << ' ' <<
        (root_1->left ? root_1->left->val : 0) << ' ' <<
        (root_1->right ? root_1->right->val : 0) << '\n';

    TreeNode *root_2 = new TreeNode(10);
    std::cout << "TreeNode(10): " << root_2->val << ' ' <<
        (root_1->left ? root_1->left->val : 0) << ' ' <<
        (root_1->right ? root_1->right->val : 0) << '\n';

    TreeNode *root_3 = new TreeNode(10, new TreeNode(8), new TreeNode(13));
    std::cout << "TreeNode(10, new TreeNode(8), new TreeNode(13)): " <<
        root_3->val << ' ' << root_3->left->val << ' ' << root_3->right->val << '\n';
    std::cout << "size: " << root_3->size() << " height: " << root_3->height() << '\n';


    try {
        TreeNode *root_4a = new TreeNode("[]");
        std::cout << root_4a << '\n';
    } catch (const std::exception &e) {
        std::cout << e.what() << " on \"[]\"\n";
    }

    try {
        TreeNode *root_4b = new TreeNode("[null]");
        std::cout << root_4b << '\n';
    } catch (const std::exception &e) {
        std::cout << e.what() << " on \"[null]\"\n";
    }

    try {
        TreeNode *root_4c = new TreeNode("[,]");
        std::cout << root_4c << '\n';
    } catch (const std::exception &e) {
        std::cout << e.what() << " on \"[,]\"\n";
    }

    try {
        TreeNode *root_4d = new TreeNode("[");
        std::cout << root_4d << '\n';
    } catch (const std::exception &e) {
        std::cout << e.what() << " on \"[\"\n";
    }

    try {
        TreeNode *root_4e = new TreeNode("]");
        std::cout << root_4e << '\n';
    } catch (const std::exception &e) {
        std::cout << e.what() << " on \"]\"\n";
    }

    try {
        TreeNode *root_4f = new TreeNode("");
        std::cout << root_4f << '\n';
    } catch (const std::exception &e) {
        std::cout << e.what() << " on \"\"\n";
    }

    try {
        TreeNode *root_4g = new TreeNode("[1,2]]");
        std::cout << root_4g << '\n';
    } catch (const std::exception &e) {
        std::cout << e.what() << " on \"[1,2]]\"\n";
    }

    try {
        TreeNode *root_4h = new TreeNode("[1,2,nul]");
        std::cout << root_4h << '\n';
    } catch (const std::exception &e) {
        std::cout << e.what() << " on \"[1,2,nul]\"\n";
    }


    TreeNode *root_5 = new TreeNode("[1,null,2]");
    std::cout << "[1,null,2]: " << root_5->val << ' ' <<
        (root_5->left ? root_5->left->val : 0) << ' ' <<
        root_5->right->val << '\n';

    TreeNode *root_6 = new TreeNode("[1,null,2,3,4]");
    std::cout << "[1,null,2,3,4]: " << root_6->val << ' ' <<
        (root_5->left ? root_5->left->val : 0) << ' ' <<
        root_6->right->val << ' ' <<
        root_6->right->left->val << ' ' << root_6->right->right->val << '\n';

    TreeNode *root_7 = new TreeNode("[1,2,3,4,null,null,7]");
    std::cout << "[1,2,3,4,null,null,7]: " << root_7->val << ' ' <<
        root_7->left->val << ' ' << root_7->right->val << ' ' <<
        root_7->left->left->val << ' ' <<
        (root_7->left->right ? root_7->left->right->val : 0) << ' ' <<
        (root_7->right->left ? root_7->right->left->val : 0) << ' ' <<
        root_7->right->right->val << '\n';
    std::cout << "size: " << root_7->size() << " height: " << root_7->height() << '\n';

    TreeNode *root_8 = new TreeNode("[1,2,3,4,5,6,7,8]");
    std::cout << "[1,2,3,4,5,6,7,8]: " << root_8->val << ' ' <<
        root_8->left->val << ' ' << root_8->right->val << ' ' <<
        root_8->left->left->val << ' ' << root_8->left->right->val << ' ' <<
        root_8->right->left->val << ' ' << root_8->right->right->val << ' ' <<
        root_8->left->left->left->val << '\n';

    std::string s1 {"[1,null,2,3,4]"};
    std::string s2 {"[1,2,3,4,null,null,7]"};
    std::string s3 {"[1,2,3,4,5,6,7,8]"};

    TreeNode *root_9 = new TreeNode(s1);
    TreeNode *root_10 = new TreeNode(s2);
    TreeNode *root_11 = new TreeNode(s3);
    std::cout << s1 << " to tree and back to string: " << root_9->str() << '\n';
    std::cout << s2 << " to tree and back to string: " << root_10->str() << '\n';
    std::cout << s3 << " to tree and back to string: " << root_11->str() << '\n';

    TreeNode *root_12 {new TreeNode(0)};
    TreeNode *root_13 {new TreeNode(0)};
    TreeNode *root_14 {nullptr};
    std::istringstream iss1 {s1};
    std::istringstream iss2 {s2};
    std::istringstream iss3 {s3};

    iss1 >> root_12;
    std::cout << s1 << " read from input stream via `>>` and then output via `<<`: " <<
        root_12 << " or with str(): " << root_12->str() << '\n';
    iss2 >> root_13;
    std::cout << s2 << " read from input stream via `>>` and then output via `<<`: " <<
        root_13 << " or with str(): " << root_13->str() << '\n';
    try {
        iss1 >> root_14;
        std::cout << s3 << " read from input stream via `>>` and then output via `<<`: " <<
            root_14 << " or with str(): " << root_14->str() << '\n';
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }

    root_1->erase();
    root_2->erase();
    root_3->erase();
    //root_4->erase();
    root_5->erase();
    root_6->erase();
    root_7->erase();
    root_8->erase();
    root_9->erase();
    root_10->erase();
    root_11->erase();
    root_12->erase();
    root_13->erase();
    //root_14->erase();
}
