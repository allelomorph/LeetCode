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


// Time to complete: 30 mins

// Needed to research:

//// Begin solution, results at https://leetcode.com/submissions/detail/743114933/


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
    // the number of nodes in both lists is in the range [0, 50].
    // -100 <= Node.val <= 100
    // both list1 and list2 are sorted in increasing order.
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        // Given the heads of two sorted linked lists list1 and list2,
        //   merges them into one sorted list. The new list is comprised
        //   of the original nodes and is not newly allocated.
        //
        // Returns the head of the merged linked list
        ListNode *merge {nullptr};
        if (list1 == nullptr) {
            merge = list2;
        } else if (list2 == nullptr) {
            merge = list1;
        } else {
            ListNode *l1_temp {list1};
            ListNode *l2_temp {list2};
            if (l1_temp->val <= l2_temp->val) {
                merge = l1_temp;
                l1_temp = l1_temp->next;
            } else {
                merge = l2_temp;
                l2_temp = l2_temp->next;
            }
            ListNode *merge_temp {merge};
            while (merge_temp) {
                if (!l1_temp && l2_temp) {
                    merge_temp->next = l2_temp;
                    l2_temp = l2_temp->next;
                } else if (l1_temp && !l2_temp) {
                    merge_temp->next = l1_temp;
                    l1_temp = l1_temp->next;
                } else if (!l1_temp && !l2_temp) {
                    merge_temp->next = nullptr;
                } else if (l1_temp->val <= l2_temp->val) {
                    merge_temp->next = l1_temp;
                    l1_temp = l1_temp->next;
                } else {
                    merge_temp->next = l2_temp;
                    l2_temp = l2_temp->next;
                }
                merge_temp = merge_temp->next;
            }
        }
        return merge;
    }
};


//// end solution

int main() {
    // list1 = [1,2,4], list2 = [1,3,4]
    ListNode *list1_1 {new ListNode(4)};
    list1_1 = new ListNode(2, list1_1);
    list1_1 = new ListNode(1, list1_1);

    ListNode *list2_1 {new ListNode(4)};
    list2_1 = new ListNode(3, list2_1);
    list2_1 = new ListNode(1, list2_1);

    // list1 = [], list2 = []
    ListNode *list1_2 {nullptr};

    ListNode *list2_2 {nullptr};

    // list1 = [], list2 = [0]
    ListNode *list1_3 {nullptr};

    ListNode *list2_3 {new ListNode(0)};

    Solution solution;

    std::cout << "solution.mergeTwoLists(" << PrintableList(list1_1) << ", " <<
        PrintableList(list2_1) << "): " <<
        PrintableList(solution.mergeTwoLists(list1_1, list2_1)) << '\n';
    // [1,1,2,3,4,4]

    std::cout << "solution.mergeTwoLists(" << PrintableList(list1_2) << ", " <<
        PrintableList(list2_2) << "): " <<
        PrintableList(solution.mergeTwoLists(list1_2, list2_2)) << '\n';
    // []

    std::cout << "solution.mergeTwoLists(" << PrintableList(list1_3) << ", " <<
        PrintableList(list2_3) << "): " <<
        PrintableList(solution.mergeTwoLists(list1_3, list2_3)) << '\n';
    // [0]
}
