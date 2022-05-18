// https://leetcode.cn/problems/minimum-size-subarray-sum/solution/chang-du-zui-xiao-de-zi-shu-zu-by-leetcode-solutio/
// 双指针，滑窗

// 初始状态下，left, right都指向下标 0，sum = 0;
// 每一轮迭代，将 nums[right] 加到 sum
// 如果 sum≥s，则更新子数组的最小长度（right - left + 1）
// 然后将 sum 中减去并将 left, left 右移，直到 sum<s，在此过程中同样更新子数组的最小长度。
// 在每一轮迭代的最后，将 right 右移。

// 时间复杂度：O(n)
class Solution {
 public:
  int minSubArrayLen(int s, vector<int>& nums) {
    const int N = nums.size();
    if (N == 0) {
      return 0;
    }
    int ans = INT_MAX;
    int left = 0, right = 0;
    int sum = 0;
    while (right < N) {
      sum += nums[right];
      while (sum >= s) {
        ans = min(ans, right - left + 1);
        sum -= nums[left];
        left++;
      }
      right++;
    }
    return ans == INT_MAX ? 0 : ans;
  }
};

// Source : https://leetcode.com/problems/minimum-size-subarray-sum/
// Author : Hao Chen
// Date   : 2015-06-09

/**********************************************************************************
 *
 * Given an array of n positive integers and a positive integer s, find the minimal length of a
 *subarray of which the sum ≥ s. If there isn't one, return 0 instead.
 *
 * For example, given the array [2,3,1,2,4,3] and s = 7,
 * the subarray [4,3] has the minimal length under the problem constraint.
 *
 * click to show more practice.
 *
 * More practice:
 *
 * If you have figured out the O(n) solution, try coding another solution of which the time
 *complexity is O(n log n).
 *
 * Credits:Special thanks to @Freezen for adding this problem and creating all test cases.
 *
 **********************************************************************************/

class Solution {
 public:
  int minSubArrayLen(int s, vector<int>& nums) {
    int min = nums.size();
    int begin = 0, end = 0;
    int sum = 0;
    bool has = false;

    for (int i = 0; i < nums.size(); i++, end++) {
      sum += nums[i];

      while (sum >= s && begin <= end) {
        // the 1 is minial length, just return
        if (begin == end) return 1;

        if (end - begin + 1 < min) {
          min = end - begin + 1;
          has = true;
        }
        // move the begin
        sum -= nums[begin++];
      }
    }

    return has ? min : 0;
  }
};
