#include <iostream>

using namespace std;

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

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* cu1 = list1;
    ListNode* cu2 = list2;
    ListNode* mergeList = nullptr;

    // base case
    if (list1 == nullptr && list2 == nullptr) {
        return nullptr;
    }
    //traverse both lists and add the less node first
    while (cu1 != nullptr || cu2 != nullptr ) {
        if (cu1->val >= cu2->val) {
            //add to list
            if (mergeList == nullptr) {
                mergeList = new ListNode(cu2->val);
            } else {
                mergeList->next = new ListNode(cu2->val);
                mergeList = mergeList->next;
            }
            cu2 = cu2 ->next;
        } else {
            //add to list
            if (mergeList == nullptr) {
                mergeList = new ListNode(cu1->val);
            } else {
                mergeList->next = new ListNode(cu1->val);
                mergeList = mergeList->next;
            }
            
        }
        cu1 = cu1 ->next;
        cu2 = cu2 ->next;
    }

    return mergeList;
    }
};
