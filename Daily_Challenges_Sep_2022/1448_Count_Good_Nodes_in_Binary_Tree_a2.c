#include <stdio.h>
#include <stdlib.h>  // malloc, free


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


// Time to complete: 25 mins with interruptions

// Needed to research:

// Notes:

//// Begin solution, results at https://leetcode.com/submissions/detail/789285471/


// number of nodes in the binary tree is in the range [1, 10^5]
// node values between [-10^4, 10^4]
void goodNodeRecurse(struct TreeNode *tree, int max_val,
                     unsigned short *good_node_ct) {
    if (!tree)
        return;
    if (tree->left) {
        if (tree->left->val < max_val) {
            goodNodeRecurse(tree->left, max_val, good_node_ct);
        } else {
            (*good_node_ct)++;
            goodNodeRecurse(tree->left, tree->left->val, good_node_ct);
        }
    }
    if (tree->right) {
        if (tree->right->val < max_val) {
            goodNodeRecurse(tree->right, max_val, good_node_ct);
        } else {
            (*good_node_ct)++;
            goodNodeRecurse(tree->right, tree->right->val, good_node_ct);
        }
    }
}

int goodNodes(struct TreeNode *root) {
    if (!root)
        return 0;
    unsigned short good_node_ct = 1;
    goodNodeRecurse(root, root->val, &good_node_ct);
    return good_node_ct;
}


/// end solution


struct TreeNode *newTreeNode(int val) {
    struct TreeNode *new = malloc(sizeof(struct TreeNode));
    new->val   = val;
    new->left  = NULL;
    new->right = NULL;
    return (new);
}


void deleteTree(struct TreeNode *root) {
    if (!root)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}


int main(void) {
    struct TreeNode *root_1 = newTreeNode(3);
    root_1->left         = newTreeNode(1);
    root_1->right        = newTreeNode(4);
    root_1->left->left   = newTreeNode(3);
    root_1->right->left  = newTreeNode(1);
    root_1->right->right = newTreeNode(5);

    struct TreeNode *root_2 = newTreeNode(3);
    root_2->left         = newTreeNode(3);
    root_2->left->left   = newTreeNode(4);
    root_2->left->right  = newTreeNode(2);

    struct TreeNode *root_3 = newTreeNode(1);

    // root = [3,1,4,3,null,1,5]
    printf("goodNodes([3,1,4,3,null,1,5]): %i\n", goodNodes(root_1));
    // Output: 4

    // root = [3,3,null,4,2]
    printf("goodNodes([3,3,null,4,2]): %i\n", goodNodes(root_2));
    // Output: 3

    // root = [1]
    printf("goodNodes([1]): %i\n", goodNodes(root_3));
    // Output: 1

    deleteTree(root_1);
    deleteTree(root_2);
    deleteTree(root_3);
}
