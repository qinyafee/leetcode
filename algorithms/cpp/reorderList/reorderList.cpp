// 可以找到中间节点， 断开， 把后半截单链表reverse一下， 再合并两个单链表。
// Reorder List
// 时间复杂度O(n)， 空间复杂度O(1)
class Solution {
 public:
  void reorderList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return;
    ListNode *slow = head, *fast = head, *prev = nullptr;
    while (fast && fast->next) {
      prev = slow;
      slow = slow->next;
      fast = fast->next->next;
    }
    prev->next = nullptr;  // cut at middle
    slow = reverseList(slow);
    // merge two lists
    ListNode* curr = head;
    while (curr->next) {
      ListNode* tmp = curr->next;
      curr->next = slow;
      slow = slow->next;
      curr->next->next = tmp;
      curr = tmp;
    }
    curr->next = slow;
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

// Source : https://oj.leetcode.com/problems/reorder-list/
// Author : Hao Chen
// Date   : 2014-06-17

/**********************************************************************************
 *
 * Given a singly linked list L: L0→L1→…→Ln-1→Ln,
 * reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
 *
 * You must do this in-place without altering the nodes' values.
 *
 * For example,
 * Given {1,2,3,4}, reorder it to {1,4,2,3}.
 *
 *
 **********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
/**
 * Definition for singly-linked list.
 */
class ListNode {
 public:
  int val;
  ListNode* next;
  ListNode() : val(0), next(NULL) {
  }
  ListNode(int x) : val(x), next(NULL) {
  }
};

class Solution {
 public:
  void reorderList(ListNode* head) {
    ListNode* pMid = findMidPos(head);
    pMid = reverseList(pMid);
    head = Merge(head, pMid);
  }

 private:
  ListNode* findMidPos(ListNode* head) {
    ListNode *p1, *p2, *p = NULL;
    p1 = p2 = head;

    while (p1 != NULL && p2 != NULL && p2->next != NULL) {
      p = p1;
      p1 = p1->next;
      p2 = p2->next->next;
    }

    if (p != NULL) {
      p->next = NULL;
    }

    return p1;
  }

  ListNode* reverseList(ListNode* head) {
    ListNode* h = NULL;
    ListNode* p;
    while (head != NULL) {
      p = head;
      head = head->next;
      p->next = h;
      h = p;
    }
    return h;
  }

  ListNode* Merge(ListNode* h1, ListNode* h2) {
    ListNode *p1 = h1, *p2 = h2, *p1nxt, *p2nxt;
    while (p1 != NULL && p2 != NULL) {
      p1nxt = p1->next;
      p2nxt = p2->next;

      p1->next = p2;
      p2->next = p1nxt;

      if (p1nxt == NULL) {
        p2->next = p2nxt;
        break;
      }
      p1 = p1nxt;
      p2 = p2nxt;
    }
  }
};

void printList(ListNode* h) {
  while (h != NULL) {
    printf("%d->", h->val);
    h = h->next;
  }
  printf("nil\n");
}

int main(int argc, char** argv) {
  int size = atoi(argv[1]);
  ListNode* n = new ListNode[size];

  for (int i = 0; i < size; i++) {
    n[i].val = i;
    if (i + 1 < size) {
      n[i].next = &n[i + 1];
    }
  }

  Solution s;
  s.reorderList(&n[0]);
  printList(&n[0]);

  return 0;
}
