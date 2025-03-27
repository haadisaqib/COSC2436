#include <iostream>


struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };

class Solution {
public:
    int length(ListNode* head1) {
        ListNode* temp1 = head1;
        //base case
        int counter1 = 0;
        while(temp1 != nullptr) {
            temp1 = temp1->next;
            counter1++;
        }
        return counter1;
    }

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int alen = length(headA);
        int blen = length(headB);
        ListNode* temp1 = headA;
        ListNode* temp2 = headB;

        //compare and move by diff
        if (alen>blen) {
            int diff = alen - blen;
            for(int i = 0; i < diff; i++) {
                temp1 = temp1->next;
            }
        } else if (blen>alen) {
            int diff = blen - alen;
            for(int i = 0; i < diff; i++) {
                temp2 = temp2->next;
            }
        } else if (blen == alen){
            int diff = 0;
        }

        //traverse and check for match
        while(temp1 != nullptr && temp2 != nullptr) {
            if (temp1 == temp2) {
                return temp1;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        return nullptr;
    }
};