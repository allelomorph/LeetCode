#include <iostream>


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
    if (result.back() == ',')
        result.back() = ']';
    else
        result.push_back(']');
    return result;
}


// Time to complete: 40 mins

// Needed to research:

//// Begin solution, results at https://leetcode.com/submissions/detail/738715490/


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
    // the number of nodes in the list is sz
    // 1 <= sz <= 30
    // 0 <= Node.val <= 100
    // 1 <= n <= sz
    // "Could you do this in one pass?"
public:
    ListNode *removeNthFromEnd(ListNode *head, const int n) {
        ListNode *temp;
        // space O(n) is quite wasteful, but leaning on the small max list size
        //   to attempt in one pass
        std::vector<ListNode *> pv;
        for (temp = head; temp != nullptr; temp = temp->next) {
            pv.push_back(temp);
        }
        const int sz (pv.size());
        if (n == sz) {
            delete pv[0];
            return (sz > 1) ? pv[1] : nullptr;
        }
        temp = pv[sz - n - 1];
        temp->next = (n == 1) ? nullptr : pv[sz - n + 1];
        delete pv[sz - n];
        return pv[0];
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

    // head = [1]
    ListNode *l2 {new ListNode(1)};

    // head = [1]
    ListNode *l3 {new ListNode(2)};
    l3 = new ListNode(1, l3);

    Solution solution;

    std::cout << "solution.removeNthFromEnd(" << PrintableList(l1) << ", 2): " <<
        PrintableList(solution.removeNthFromEnd(l1, 2)) << '\n';
    // [1,2,3,5]

    std::cout << "solution.removeNthFromEnd(" << PrintableList(l2) << ", 1): " <<
        PrintableList(solution.removeNthFromEnd(l2, 1)) << '\n';
    // []

    std::cout << "solution.removeNthFromEnd(" << PrintableList(l3) << ", 1): " <<
        PrintableList(solution.removeNthFromEnd(l3, 1)) << '\n';
    // [1,2]
}
