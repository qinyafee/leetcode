// 贪心
// 由于每层最多可以跳 A[i] 步， 也可以跳0或1步， 因此如果能到达最高层， 则说明每一层都可以到达。
// 从0出发， 一层一层网上跳， 看最后能不能超过最高层， 能超过， 说明能到达， 否则不能到达。

// Jump Game
// 思路1， 时间复杂度O(n)， 空间复杂度O(1)
class Solution {
 public:
  bool canJump(const vector<int>& nums) {
    int reach = 0;  // 最右能跳到哪里index
    for (int i = 0; i <= reach && reach < nums.size() - 1; ++i) {
      reach = max(reach, i + nums[i]);
    }
    return reach >= nums.size() - 1;
  }
};

// Source : https://oj.leetcode.com/problems/jump-game/
// Author : Hao Chen
// Date   : 2014-06-27

/**********************************************************************************
 *
 * Given an array of non-negative integers, you are initially positioned at the first index of the
 *array.
 *
 * Each element in the array represents your maximum jump length at that position.
 *
 * Determine if you are able to reach the last index.
 *
 * For example:
 * A = [2,3,1,1,4], return true.
 *
 * A = [3,2,1,0,4], return false.
 *
 *
 **********************************************************************************/

class Solution {
 public:
  bool canJump(int A[], int n) {
    if (n <= 0) return false;

    // the basic idea is traverse array, maintain the most far can go
    int coverPos = 0;
    // the condition i<=coverPos means traverse all of covered position
    for (int i = 0; i <= coverPos && i < n; i++) {
      if (coverPos < A[i] + i) {
        coverPos = A[i] + i;
      }

      if (coverPos >= n - 1) {
        return true;
      }
    }
    return false;
  }
};
