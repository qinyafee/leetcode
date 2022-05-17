// - 设定两个虚拟节点，dummyHead1用来保存小于该值的链表，dummyHead2来保存大于等于该值的链表
// - 遍历整个原始链表，将小于该值的放于dummyHead1中，其余的放置在dummyHead2中
// 遍历结束后，将dummyHead2插入到dummyHead1后面

// Partition List
// 时间复杂度O(n)， 空间复杂度O(1)
class Solution {
 public:
  ListNode* partition(ListNode* head, int x) {
    ListNode left_dummy(-1);   // 头结点
    ListNode right_dummy(-1);  // 头结点
    auto left_cur = &left_dummy;
    auto right_cur = &right_dummy;
    for (ListNode* cur = head; cur != nullptr; cur = cur->next) {
      if (cur->val < x) {
        left_cur->next = cur;
        left_cur = cur;
      } else {
        right_cur->next = cur;
        right_cur = cur;
      }
    }
    left_cur->next = right_dummy.next; //拉链
    right_cur->next = nullptr; //!
    return left_dummy.next;
  }
};

// Source : https://oj.leetcode.com/problems/partition-list/
// Author : Hao Chen
// Date   : 2014-06-21

/**********************************************************************************
 *
 * Given a linked list and a value x, partition it such that all nodes less than x come
 * before nodes greater than or equal to x.
 *
 * You should preserve the original relative order of the nodes in each of the two partitions.
 *
 * For example,
 * Given 1->4->3->2->5->2 and x = 3,
 * return 1->2->2->4->3->5.
 *
 *
 **********************************************************************************/

#include <stdio.h>

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {
  }
};

ListNode* partition(ListNode* head, int x) {
  ListNode fakeHead(0);
  fakeHead.next = head;
  head = &fakeHead;

  ListNode* pos = NULL;
  for (ListNode* p = head; p != NULL && p->next != NULL;) {
    if (!pos && p->next->val >= x) {
      pos = p;
      p = p->next;
      continue;
    }
    if (pos && p->next->val < x) {
      ListNode* pNext = p->next;
      p->next = pNext->next;
      pNext->next = pos->next;
      pos->next = pNext;
      pos = pNext;
      continue;
    }
    p = p->next;
  }

  return head->next;
}

void printList(ListNode* h) {
  while (h != NULL) {
    printf("%d ", h->val);
    h = h->next;
  }
  printf("\n");
}

ListNode* createList(int a[], int n) {
  ListNode *head = NULL, *p = NULL;
  for (int i = 0; i < n; i++) {
    if (head == NULL) {
      head = p = new ListNode(a[i]);
    } else {
      p->next = new ListNode(a[i]);
      p = p->next;
    }
  }
  return head;
}

int main() {
  // int a[] = {1}; int x =2;
  // int a[] = {2,3,1}; int x=2;
  int a[] = {3, 1, 2};
  int x = 3;
  ListNode* p = createList(a, sizeof(a) / sizeof(int));
  printList(p);
  p = partition(p, x);
  printList(p);

  return 0;
}
