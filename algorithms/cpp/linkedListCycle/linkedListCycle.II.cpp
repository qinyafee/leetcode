// Source : https://oj.leetcode.com/problems/linked-list-cycle-ii/
// Author : Hao Chen
// Date   : 2014-07-03

/**********************************************************************************
 *
 * Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
 *
 * Follow up:
 * Can you solve it without using extra space?
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

// my implm Floyd 判圈算法
// 分析见：
// https://leetcode-cn.com/problems/linked-list-cycle-ii/solution/huan-xing-lian-biao-ii-by-leetcode-solution/
class Solution {
 public:
  ListNode* detectCycle(ListNode* head) {
		auto slow = head;
		auto fast = head;
		while(fast != nullptr && fast->next != nullptr){
			slow = slow->next;
			fast = fast->next->next;
			if(slow == fast){
				auto slow2 = head;
				while(slow != slow2){
					slow = slow->next;
					slow2 = slow2->next;
				}
				return slow2;
			}
		}
		return nullptr;
  }
};

class Solution {
 private:
  ListNode *p1, *p2;

 public:
  bool hasCycle(ListNode* head) {
    if (head == NULL) return false;
    p1 = head;
    p2 = head;

    while (p1 != NULL && p2 != NULL) {
      p1 = p1->next;

      if (p2->next == NULL) return false;

      p2 = p2->next->next;

      if (p1 == p2) return true;
    }

    return false;
  }

  /*
   * So, the idea is:
   *   1) Using the cycle-chcking algorithm.
   *   2) Once p1 and p1 meet, then reset p1 to head, and move p1 & p2 synchronously
   *      until p1 and p2 meet again, that place is the cycle's start-point
   */
  ListNode* detectCycle(ListNode* head) {
    if (hasCycle(head) == false) {
      return NULL;
    }

    p1 = head;

    while (p1 != p2) {
      p1 = p1->next;
      p2 = p2->next;
    }

    return p1;
  }
};
