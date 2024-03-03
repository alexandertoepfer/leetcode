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
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode();
        ListNode* dummy = head;
        int carry = 0;
        while (l1 != NULL || l2 != NULL || carry ) {
            // Sum of both digits 0 < sum < 19
            int sum = 0;
            if (l1 != NULL) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL) {
                sum += l2->val;
                l2 = l2->next;
            }
            sum += carry;
            // Carry for next round when sum > 9
            carry = sum / 10;
            ListNode* node = new ListNode(sum % 10);
            dummy->next= node;
            dummy = dummy->next;
        }
        // Remove empty node at head
        dummy = head;
        head = head->next;
        delete dummy;
        return head;
    }
};
