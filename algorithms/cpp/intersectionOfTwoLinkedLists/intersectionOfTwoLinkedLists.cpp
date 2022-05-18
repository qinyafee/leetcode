// method1 用hash记录
// 时间复杂度 O(a+b)，空间复杂度 O(1)
class Solution {
 public:
  ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    unordered_set<ListNode*> visited;
    ListNode* temp = headA;
    while (temp != nullptr) {
      visited.insert(temp);
      temp = temp->next;
    }
    temp = headB;
    while (temp != nullptr) {
      if (visited.count(temp)) {  //找到重复，返回
        return temp;
      }
      temp = temp->next;
    }
    return nullptr;
  }
};

// method2 双指针
// 考虑构建两个指针A​,B 分别指向headA, headB头节点，两个指针一起走：
// 指针A先遍历完链表headA，再开始遍历链表headB，当走到node时，共走步数为：a+(b−c)
// 指针B先遍历完链表headB，再开始遍历链表headA，当走到node时，共走步数为：b+(a−c)
// 此时指针A,B 重合，并有两种情况：
// 有 公共尾部(即 c>0)：指针A,B同时指向「第一个公共节点」node 。
// 无 公共尾部(即 c=0)：指针A,B同时指向 null 。
// https://leetcode.cn/problems/intersection-of-two-linked-lists/solution/intersection-of-two-linked-lists-shuang-zhi-zhen-l/
// 时间复杂度 O(a+b)，空间复杂度 O(1)
class Solution {
 public:
  ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    ListNode *A = headA, *B = headB;
    while (A != B) {
      A = A != nullptr ? A->next : headB;
      B = B != nullptr ? B->next : headA;
    }
    return A;
  }
};

// Source : https://oj.leetcode.com/problems/intersection-of-two-linked-lists/
// Author : Hao Chen
// Date   : 2014-12-01

/**********************************************************************************
 *
 * Write a program to find the node at which the intersection of two singly linked lists begins.
 *
 * For example, the following two linked lists:
 *
 *
 *    A:          a1 → a2
 *                       ↘
 *                         c1 → c2 → c3
 *                       ↗
 *    B:     b1 → b2 → b3
 *
 * begin to intersect at node c1.
 *
 * Notes:
 *
 * If the two linked lists have no intersection at all, return null.
 * The linked lists must retain their original structure after the function returns.
 * You may assume there are no cycles anywhere in the entire linked structure.
 * Your code should preferably run in O(n) time and use only O(1) memory.
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
  ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    // caculate the length of each List
    int lenA = getListLength(headA);
    int lenB = getListLength(headB);

    if (lenA <= 0 || lenB <= 0) return NULL;

    // let List A is the longest List;
    if (lenA < lenB) {
      swap(headA, headB);
    }

    // move head of List A, make both of Lists are same length
    for (int i = 0; i < abs(lenA - lenB); i++) {
      headA = headA->next;
    }

    // synced travel both of Lists and check their nodes are same or not
    while (headA != headB) {
      headA = headA->next;
      headB = headB->next;
    }

    return headA;
  }

 private:
  inline int getListLength(ListNode* head) {
    int len = 0;
    while (head != NULL) {
      head = head->next;
      len++;
    }
    return len;
  }
};
