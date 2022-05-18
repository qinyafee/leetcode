// Insertion Sort List
// 插入排序
// 时间复杂度O(n^2)， 空间复杂度O(1)
class Solution {
 public:
  ListNode* insertionSortList(ListNode* head) {
    ListNode dummy(INT_MIN); //! 填值保证最小，永远在开头
    // dummy.next = head;
    for (ListNode* cur = head; cur != nullptr;) {
      auto pos = findInsertPos(&dummy, cur->val);
      ListNode* tmp = cur->next;
      cur->next = pos->next;
      pos->next = cur;
      cur = tmp;
    }
    return dummy.next;
  }
  ListNode* findInsertPos(ListNode* head, int x) {
    ListNode* pre = nullptr;
    for (ListNode* cur = head; cur != nullptr && cur->val <= x; pre = cur, cur = cur->next)
      ;
    return pre; // 返回最后一个 <=x的位置
  }
};

// Source : https://oj.leetcode.com/problems/insertion-sort-list/
// Author : Hao Chen
// Date   : 2014-07-19

/**********************************************************************************
 *
 * Sort a linked list using insertion sort.
 *
 **********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {
  }
};

ListNode* insertionSortList(ListNode* head) {
  // zero or one element in list
  if (head == NULL || head->next == NULL) {
    return head;
  }

  ListNode* pSorted = NULL;
  while (head != NULL) {
    /* remember the head */
    ListNode* pHead = head;
    /* trailing pointer for efficient splice */
    ListNode** ppTrail = &pSorted;

    /* pop head off list */
    head = head->next;

    /* splice head into sorted list at proper place */
    while (*ppTrail != NULL && pHead->val > (*ppTrail)->val) {
      ppTrail = &(*ppTrail)->next;
    }
    pHead->next = *ppTrail;
    *ppTrail = pHead;
  }

  return pSorted;
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

int main(int argc, char** argv) {
  int n = 10;
  if (argc > 1) {
    n = atoi(argv[1]);
  }
  srand(time(NULL));

  int* a = new int[n];
  for (int i = 0; i < n; i++) {
    a[i] = random() % n + 1;
  }

  ListNode* p = createList(a, n);
  printList(p);
  printList(insertionSortList(p));

  delete[] a;
}
