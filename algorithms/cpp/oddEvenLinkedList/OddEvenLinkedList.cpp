
// my implm
// 创建两个新的空链表， 遍历原始链表， 把奇数位置的节点添加到第一个小链表，
// 把偶数位置的节点添加到第二个小链表。
class Solution {
 public:
  ListNode* oddEvenList(ListNode* head) {
    ListNode dummy1(-1);  //(-1, head);
    ListNode* p1 = &dummy1;
    ListNode dummy2(-1);  //(-1, head);
    ListNode* p2 = &dummy2;
    ListNode* curr = head;

    int i = 0;
    while (curr) {
      if (!(i % 2)) {  //奇数节点
        p1->next = curr;
        p1 = curr;
        curr = curr->next;
        p1->next = nullptr;
        ++i;
      } else {  //偶数节点
        p2->next = curr;
        p2 = curr;
        curr = curr->next;
        p2->next = nullptr;  // 必须在此处断开，否则偶数的test case会产生环。
        ++i;
      }
      // ++i;
      // curr = curr->next;
    }

    p1->next = dummy2.next;

    return dummy1.next;
    // p1; 3
    // p2; 2,3
  }
};

// Source : https://leetcode.com/problems/odd-even-linked-list/
// Author : Hao Chen
// Date   : 2016-01-16

/***************************************************************************************
 *
 * Given a singly linked list, group all odd nodes together followed by the even nodes.
 * Please note here we are talking about the node number and not the value in the nodes.
 *
 * You should try to do it in place. The program should run in O(1) space complexity
 * and O(nodes) time complexity.
 *
 * Example:
 * Given 1->2->3->4->5->NULL,
 * return 1->3->5->2->4->NULL.
 *
 * Note:
 * The relative order inside both the even and odd groups should remain as it was in
 * the input.
 * The first node is considered odd, the second node even and so on ...
 *
 * Credits:Special thanks to @aadarshjajodia for adding this problem and creating all
 * test cases.
 ***************************************************************************************/

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
  ListNode* oddEvenList(ListNode* head) {
    if (!head) return head;
    ListNode* pOdd = head;
    ListNode* p = head->next;
    ListNode* pNext = NULL;
    while (p && (pNext = p->next)) {
      p->next = pNext->next;
      pNext->next = pOdd->next;
      pOdd->next = pNext;

      p = p->next;
      pOdd = pOdd->next;
    }
    return head;
  }
};
