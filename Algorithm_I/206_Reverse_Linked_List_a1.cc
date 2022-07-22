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


// Time to complete: 15 mins

// Needed to research:

//// Begin solution, results at https://leetcode.com/submissions/detail/743086894/


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
    // the number of nodes in the list is the range [0, 5000].
    // -5000 <= Node.val <= 5000
public:
    ListNode* reverseList(ListNode* head) {
        // Given the head of a singly linked list, reverses the list, and returns
        //   the reversed list.
        if (head == nullptr)
            return head;
        ListNode *prev {nullptr};
        for (ListNode *curr {head}, *next {head->next}; curr != nullptr;) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
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

    // head = [1,2]
    ListNode *l2 {new ListNode(2)};
    l2 = new ListNode(1, l2);

    // head = []
    ListNode *l3 {nullptr};

    Solution solution;

    std::cout << "solution.reverseList(" << PrintableList(l1) << "): " <<
        PrintableList(solution.reverseList(l1)) << '\n';
    // [5,4,3,2,1]

    std::cout << "solution.reverseList(" << PrintableList(l2) << "): " <<
        PrintableList(solution.reverseList(l2)) << '\n';
    // [2,1]

    std::cout << "solution.reverseList(" << PrintableList(l3) << "): " <<
        PrintableList(solution.reverseList(l3)) << '\n';
    // []
}
