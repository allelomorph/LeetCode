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


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// Time to complete: 2.5 hr

// Needed to research:
//   - refresh on map, map comarator

// Notes:

//// Begin solution, results at https://leetcode.com/submissions/detail/791663243/


#include <map>
#include <algorithm>  // sort


// tree node count in the range [1, 1000].
// 0 <= Node.val <= 1000
class Solution {
private:
    struct GridCoords {
        int col;
        int row;
    };

    struct GridCoordsCompare {
        bool operator()(const GridCoords &lhs, const GridCoords &rhs) const {
            // order by column, then row
            if (lhs.col == rhs.col)
                return lhs.row < rhs.row;
            return lhs.col < rhs.col;
        }
    };

    void vertTraversal(const TreeNode *root,
                       std::map<GridCoords, std::vector<int>, GridCoordsCompare> &vals_by_coords,
                       const int row, const int col) {
        if (root == nullptr)
            return;
        vals_by_coords[{col, row}].emplace_back(root->val);
        vertTraversal(root->left, vals_by_coords, row + 1, col - 1);
        vertTraversal(root->right, vals_by_coords, row + 1, col + 1);
    }

public:
    std::vector<std::vector<int>> verticalTraversal(const TreeNode *root) {
        if (root == nullptr)
            return std::vector<std::vector<int>> {};
        std::map<GridCoords, std::vector<int>, GridCoordsCompare> vals_by_coords;
        vertTraversal(root, vals_by_coords, 0, 0);
        std::vector<std::vector<int>> result {};
        std::vector<int> temp;
        int col_i {vals_by_coords.begin()->first.col};
        for (auto &pair : vals_by_coords) {
            if (pair.first.col != col_i) {
                result.emplace_back(temp);
                temp.clear();
                col_i = pair.first.col;
            }
            //std::cout << "[" << pair.first.col << ", " << pair.first.row << "]: [";
            if (pair.second.size() > 1)
                std::sort(pair.second.begin(), pair.second.end());
            for (auto &n : pair.second) {
                //std::cout << n << ' ';
                temp.emplace_back(n);
            }
            //std::cout << "]\n";
        }
        result.emplace_back(temp);
        return result;
    }
};


//// end solution


void deleteTree(struct TreeNode *root) {
    if (root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}


int main() {
    TreeNode *root_1 {
        new TreeNode(3, new TreeNode(9),
                     new TreeNode(20, new TreeNode(15), new TreeNode(7)))};

    TreeNode *root_2 {
        new TreeNode(1, new TreeNode(2, new TreeNode(4), new TreeNode(5)),
                     new TreeNode(3, new TreeNode(6), new TreeNode(7)))};

    TreeNode *root_3 {
        new TreeNode(1, new TreeNode(2, new TreeNode(4), new TreeNode(6)),
                     new TreeNode(3, new TreeNode(5), new TreeNode(7)))};

    TreeNode *root_4 {
        new TreeNode(3, new TreeNode(1, new TreeNode(0), new TreeNode(2)),
                     new TreeNode(4, new TreeNode(2), nullptr))};

    TreeNode *root_5 {new TreeNode(0, new TreeNode(7), new TreeNode(1))};
    root_5->left->right = new TreeNode(10);
    root_5->left->right->left = new TreeNode(11);
    root_5->left->right->left->left = new TreeNode(13);
    root_5->right->left = new TreeNode(2, new TreeNode(3), new TreeNode(14));
    root_5->right->left->left->right = new TreeNode(
        4, new TreeNode(12), new TreeNode(5, new TreeNode(6), new TreeNode(9)));
    root_5->right->left->left->right->right->left->left = new TreeNode(8);


    Solution solution;

    // root = [3,9,20,null,null,15,7]
    std::cout << "solution.verticalTraversal([3,9,20,null,null,15,7]): \n" <<
        printableNestedVector(solution.verticalTraversal(root_1)) << std::endl;
    // Output: [[9],[3,15],[20],[7]]

    // root = [1,2,3,4,5,6,7]
    std::cout << "solution.verticalTraversal([1,2,3,4,5,6,7]): \n" <<
        printableNestedVector(solution.verticalTraversal(root_2)) << std::endl;
    // Output: [[4],[2],[1,5,6],[3],[7]]

    // root = [1,2,3,4,6,5,7]
    std::cout << "solution.verticalTraversal([1,2,3,4,6,5,7]): \n" <<
        printableNestedVector(solution.verticalTraversal(root_3)) << std::endl;
    // Output: [[4],[2],[1,5,6],[3],[7]]

    // root = [3,1,4,0,2,2]
    std::cout << "solution.verticalTraversal([3,1,4,0,2,2]): \n" <<
        printableNestedVector(solution.verticalTraversal(root_4)) << std::endl;
    // Output: [[0],[1],[3,2,2],[4]]

    // [0,7,1,null,10,2,null,11,null,3,14,13,null,null,4,null,null,null,null,12,5,null,null,6,9,8]
    std::cout << "solution.verticalTraversal(" <<
        "[0,7,1,null,10,2,null,11,null,3,14,13,null,null,4,null,null,null,null,12,5,null,null,6,9,8]" <<
        "): \n" << printableNestedVector(solution.verticalTraversal(root_5)) << std::endl;
    // [[13],[7,3,11,12,8],[0,2,10,4,6],[1,14,5],[9]]

    deleteTree(root_1);
    deleteTree(root_2);
    deleteTree(root_3);
    deleteTree(root_4);
    deleteTree(root_5);
}
