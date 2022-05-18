// Source : https://leetcode.com/problems/palindrome-linked-list/
// Author : Hao Chen
// Date   : 2015-07-17

/**********************************************************************************
 *
 * Given a singly linked list, determine if it is a palindrome.
 *
 * Follow up:
 * Could you do it in O(n) time and O(1) space?
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
// my implm
// 首先使用快慢指针寻找中点，把后半段reverse一下，然后比较两个小链表即可。
// 时间复杂度:O(n), 空间复杂度:O(1)
class Solution {
 public:
  bool isPalindrome(ListNode* head) {
    ListNode* p1 = head;
    ListNode* middle = findMiddle(head);
    ListNode* p2 = reverseList(middle);
    //! 中间没有断开，注意终止条件
    for (; p1 != middle; p1 = p1->next, p2 = p2->next) {
      if (p1->val != p2->val) {
        return false;
      }
    }
    return true;
  }

  // 若链表有偶数个节点，则前后正好一半。
  // 若链表有奇数个节点，则中间的节点是后半部分。
  ListNode* findMiddle(ListNode* head) {
    if (head == nullptr) {
      return nullptr;
    }
    // 快慢指针
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    return slow;
  }

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