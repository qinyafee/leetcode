// https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/solution/fu-xue-ming-zhu-di-gui-die-dai-yi-pian-t-wy0h/
// 1.递归版， 时间复杂度O(n)， 空间复杂度O(1)
class Solution {
 public:
  ListNode* deleteDuplicates(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {  //递归终止条件
      return head;
    }
    ListNode* p = head->next;
    if (head->val == p->val) {
      while (p != nullptr && head->val == p->val) {
        ListNode* tmp = p;
        p = p->next;
        delete tmp;
      }
      delete head;
      return deleteDuplicates(p);
    } else {
      head->next = deleteDuplicates(head->next);  //递归调用下一个节点，和head拉链
      return head;
    }
  }
};

// 2.迭代版
class Solution {
 public:
  ListNode* deleteDuplicates(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode dummy(0);
    dummy.next = head;
    ListNode* pre = &dummy;
    ListNode* cur = head;
    while (cur) {
      bool dupicated = false;
      // 跳过当前的重复节点，使得cur指向当前重复元素的最后一个位置
      while (cur->next && cur->val == cur->next->val) {
        dupicated = true;
        ListNode* tmp = cur;
        cur = cur->next;
        delete tmp;
      }
      if (pre->next == cur) {  // pre和cur之间没有重复节点，pre后移
        pre = pre->next;
      } else {
        // pre->next指向cur的下一个位置（相当于跳过了当前的重复元素）
        // 但是pre不移动，pre->next仍然指向已经遍历的链表结尾,因为后面cur可能依然重复
        pre->next = cur->next;
      }
      ListNode* tmp = cur;
      cur = cur->next; // cur都会后移
      if (dupicated) {  // 删除重复的最后一个元素
        delete tmp;
      }
    }
    return dummy.next;
  }
};

// Source : https://oj.leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
// Author : Hao Chen
// Date   : 2014-06-25

/**********************************************************************************
 *
 * Given a sorted linked list, delete all nodes that have duplicate numbers,
 * leaving only distinct numbers from the original list.
 *
 * For example,
 * Given 1->2->3->3->4->4->5, return 1->2->5.
 * Given 1->1->1->2->3, return 2->3.
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

ListNode* deleteDuplicates(ListNode* head) {
  ListNode fake(-1);
  fake.next = head;
  head = &fake;

  ListNode* tail = head;

  bool dup = false;
  for (ListNode* p = head->next; p && p->next; p = p->next) {
    if (dup == false && p->val == p->next->val) {
      dup = true;
      continue;
    }
    if (dup == true && p->val != p->next->val) {
      dup = false;
      tail->next = p->next;
      continue;
    }
    if (dup == false) {
      tail = p;
    }
  }
  if (dup == true) {
    tail->next = NULL;
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
  int a[] = {1, 1, 2, 3, 3};
  int b[] = {1, 1, 1};
  int c[] = {1, 2, 3};
  int d[] = {3};

  printList(deleteDuplicates(createList(a, sizeof(a) / sizeof(int))));
  printList(deleteDuplicates(createList(b, sizeof(b) / sizeof(int))));
  printList(deleteDuplicates(createList(c, sizeof(c) / sizeof(int))));
  printList(deleteDuplicates(createList(d, sizeof(d) / sizeof(int))));
  return 0;
}
