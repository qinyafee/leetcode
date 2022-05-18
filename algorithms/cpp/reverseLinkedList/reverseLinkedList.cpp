class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    ListNode* prev = NULL;
    ListNode* cur = head;
    ListNode* tail = NULL;
    while (cur != NULL) {
      tail = cur->next;  //设置下一个节点
      cur->next = prev;  //当前节点指向上一个节点，反转
      prev = cur;        //上一个节点设置成当前节点
      cur = tail;        //处理下一个节点
    }
    return prev;
  }
};

// Source : https://leetcode.com/problems/reverse-linked-list/
// Author : Hao Chen
// Date   : 2015-06-09

/**********************************************************************************
 *
 * Reverse a singly linked list.
 *
 * click to show more hints.
 *
 * Hint:
 * A linked list can be reversed either iteratively or recursively. Could you implement both?
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
  ListNode* reverseList_iteratively(ListNode* head) {
    ListNode *h = NULL, *p = NULL;
    while (head) {
      p = head->next;
      head->next = h;
      h = head;
      head = p;
    }
    return h;
  }
  ListNode* reverseList_recursively(ListNode* head) {
    if (head == NULL || head->next == NULL) return head;
    ListNode* h = reverseList_recursively(head->next);
    head->next->next = head;
    head->next = NULL;
    return h;
  }
  ListNode* reverseList(ListNode* head) {
    return reverseList_iteratively(head);
    return reverseList_recursively(head);
  }
};
