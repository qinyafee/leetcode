// 方法三：快慢指针,「Floyd 判圈算法」（又称龟兔赛跑算法）,类似142.环形链表II
// 1.数组中有一个重复的整数 <==> 链表中存在环
// 2.找到数组中的重复整数 <==> 找到链表的环入口
// 142 题中慢指针走一步 slow = slow.next ==> 本题 slow = nums[slow]
// 142 题中快指针走两步 fast = fast.next.next ==> 本题 fast = nums[nums[fast]]
// https://leetcode.cn/problems/find-the-duplicate-number/solution/287xun-zhao-zhong-fu-shu-by-kirsche/

class Solution {
 public:
  int findDuplicate(vector<int>& nums) {
    int slow = 0;
    int fast = 0;
    slow = nums[slow];
    fast = nums[nums[fast]];
    while (slow != fast) {
      slow = nums[slow];
      fast = nums[nums[fast]];
    }
    int slow2 = 0;
    while (slow != slow2) {
      slow = nums[slow];
      slow2 = nums[slow2];
    }
    return slow2;
  }
};

// Source : https://leetcode.com/problems/find-the-duplicate-number/
// Author : Hao Chen, Calinescu Valentin
// Date   : 2015-10-19

/***************************************************************************************
 *
 * Given an array nums containing n + 1 integers where each integer is between 1 and
 * n (inclusive), prove that at least one duplicate number must exist.
 * Assume that there is only one duplicate number, find the duplicate one.
 *
 * Note:
 * > You must not modify the array (assume the array is read only).
 * > You must use only constant, O(1) extra space.
 * > Your runtime complexity should be less than O(n2).
 * > There is only one duplicate number in the array, but it could be repeated more than
 *   once.
 *
 * Credits:
 * Special thanks to @jianchao.li.fighter for adding this problem and creating all test
 * cases.
 *
 ***************************************************************************************/

class Solution {
 public:
  //
  // This problem can be transfromed to "Linked List Cycle" problem.
  // There are two pointers, one goes one step, another goes two steps.
  //
  // Refer to: https://en.wikipedia.org/wiki/Cycle_detection
  //
  int findDuplicate(vector<int>& nums) {
    int n = nums.size();
    int one = n;
    int two = n;

    do {
      one = nums[one - 1];
      two = nums[nums[two - 1] - 1];
    } while (one != two);

    // find the start point of the cycle
    one = n;
    while (one != two) {
      one = nums[one - 1];
      two = nums[two - 1];
    }

    return one;
  }
};
