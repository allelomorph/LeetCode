#include <iostream>
#include <vector>


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


const std::string PrintableList(ListNode *head) {
    std::string result;
    result.push_back('[');
    while (head != nullptr) {
        result.append(std::to_string(head->val) + ",");
        head = head->next;
    }
    result.back() = ']';  // overwrite last ','
    return result;
}


// Time to complete: 20 mins

// Needed to research:

//// Begin solution, results at https://leetcode.com/submissions/detail/738695377/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
    // The number of nodes in the list is in the range [1, 100]
    // 1 <= Node.val <= 100
    // for lists with an even number of nodes, return the second middle node
public:
    ListNode *middleNode(ListNode *head) {
        ListNode *temp;
        int node_ct {0};
        for (temp = head; temp != nullptr; temp = temp->next, ++node_ct) {}
        node_ct /= 2;
        for (temp = head; node_ct != 0; temp = temp->next, --node_ct) {}
        return temp;
    }
};


//// end solution


int main() {
    // head = [1,2,3,4,5]
    ListNode *l1 {new ListNode(5)};
    l1 = new ListNode(4, l1);
    l1 = new ListNode(3, l1);
    l1 = new ListNode(2, l1);
    l1 = new ListNode(1, l1);

    // head = [1,2,3,4,5,6]
    ListNode *l2 {new ListNode(6)};
    l2 = new ListNode(5, l2);
    l2 = new ListNode(4, l2);
    l2 = new ListNode(3, l2);
    l2 = new ListNode(2, l2);
    l2 = new ListNode(1, l2);

    Solution solution;

    std::cout << "solution.middleNode(" << PrintableList(l1) << "): " <<
        solution.middleNode(l1)->val << '\n';
    // 3

    std::cout << "solution.middleNode(" << PrintableList(l2) << "): " <<
        solution.middleNode(l2)->val << '\n';
    // 4
}
