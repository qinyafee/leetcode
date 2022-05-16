// 设两个指针 p , q ， 让 q 先走 n 步， 然后 p 和 q 一起走， 直到 q 走到尾节点， 删除 p->next 即可。
// Remove Nth Node From End of List
// 时间复杂度O(n)， 空间复杂度O(1)
class Solution {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy{-1, head};
    ListNode *p = &dummy, *q = &dummy;
    for (int i = 0; i < n; i++) {  // q先走n步
      q = q->next;
    }
    while (q->next != nullptr) {  // 一起走
      p = p->next;
      q = q->next;
    }
    ListNode* tmp = p->next;
    p->next = p->next->next; //!
    delete tmp;
    return dummy.next;
  }
};

// clang-format off
// Source : https://oj.leetcode.com/problems/remove-nth-node-from-end-of-list/
// Author : Hao Chen
// Date   : 2014-06-21

/********************************************************************************** 
* 
* Given a linked list, remove the nth node from the end of list and return its head.
* 
* For example,
* 
*    Given linked list: 1->2->3->4->5, and n = 2.
* 
*    After removing the second node from the end, the linked list becomes 1->2->3->5.
* 
* Note:
* Given n will always be valid.
* Try to do this in one pass.
* 
*               
**********************************************************************************/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        if (head==NULL || n<=0){
            return NULL;
        }
        ListNode fakeHead(0);
        fakeHead.next=head;
        head=&fakeHead;
        
        ListNode *p1, *p2;
        p1=p2=head;
        for(int i=0; i<n; i++){
            if (p2==NULL) return NULL;
            p2=p2->next;
        }
        while (p2->next!=NULL){
            p2=p2->next;
            p1=p1->next;
        }
        
        p1->next = p1->next->next;
        return head->next;
    }
};
