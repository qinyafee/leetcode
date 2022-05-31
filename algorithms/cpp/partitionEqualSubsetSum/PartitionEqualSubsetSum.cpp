// 转化成 0-1 背包问题，状态定义
// dp[i][j]表示从数组的 [0, i] 子区间内挑选一些正整数，每个数只能用一次，使得这些数的和恰好等于 j。
// 状态转移
// dp[i][j] = dp[i - 1][j] or dp[i - 1][j - nums[i]]， 当 j>=nums[i]
// dp[i][j] = dp[i - 1][j]                             当 j<nums[i]
// https://leetcode.cn/problems/partition-equal-subset-sum/solution/0-1-bei-bao-wen-ti-xiang-jie-zhen-dui-ben-ti-de-yo/

// 链接：https://leetcode.cn/problems/partition-equal-subset-sum/solution/fen-ge-deng-he-zi-ji-by-leetcode-solution/
// 01背包问题详解 https://leetcode.cn/circle/article/lUki6J/

// 二维动态规划
class Solution {
 public:
  bool canPartition(vector<int>& nums) {
    int n = nums.size();
    if (n < 2) {
      return false;
    }
    int sum = accumulate(nums.begin(), nums.end(), 0);  // stl
    if (sum & 1) {                                      // 奇数
      return false;
    }
    int target = sum / 2;

    // int maxNum = *max_element(nums.begin(), nums.end());
    // if (maxNum > target) {  //特判，可以去掉
    //   return false;
    // }

    vector<vector<bool>> dp(n, vector<bool>(target + 1, 0));
    for (int i = 0; i < n; i++) {
      dp[i][0] = true;
    }
    // 先填表格第 0 行，第 1 个数只能让容积为它自己的背包恰好装满
    if (nums[0] <= target) {
      dp[0][nums[0]] = true;
    }
    // 再填表格后面几行
    for (int i = 1; i < n; i++) {
      int num = nums[i];
      for (int j = 1; j <= target; j++) {
        if (j >= num) {
          dp[i][j] = dp[i - 1][j] | dp[i - 1][j - num];
        } else {
          dp[i][j] = dp[i - 1][j];
        }
      }
      // 由于状态转移方程的特殊性，提前结束，可以认为是剪枝操作
      if (dp[i][target]) {
        return true;
      }
    }
    return dp[n - 1][target];
  }
};

// 滚动数组：当前行只参考了上一行的值，因此二维状态数组可以只设置2行，使用滚动数组填表格即可；
// 滚动数组继续优化：当前行总是参考了它上面一行「头顶上」位置和「左上角」某个位置的值。
// 因此，我们可以只开一个一维数组，「从后向前」依次填表即可。
class Solution {
 public:
  bool canPartition(vector<int>& nums) {
    int n = nums.size();
    if (n < 2) {
      return false;
    }
    int sum = 0, maxNum = 0;
    for (auto& num : nums) {
      sum += num;
      maxNum = max(maxNum, num);
    }
    if (sum & 1) {
      return false;
    }
    int target = sum / 2;
    if (maxNum > target) {
      return false;
    }
    vector<int> dp(target + 1, 0);
    dp[0] = true;
    for (int i = 0; i < n; i++) {
      int num = nums[i];
      for (int j = target; j >= num; --j) {  //! 从后往前
        dp[j] |= dp[j - num];
      }
    }
    return dp[target];
  }
};

// Source : https://leetcode.com/problems/partition-equal-subset-sum/description/
// Author : Hao Chen
// Date   : 2018-06-24

/***************************************************************************************
 *
 * Given a non-empty array containing only positive integers, find if the array can be
 * partitioned into two subsets such that the sum of elements in both subsets is equal.
 *
 *
 * Note:
 *
 * Each of the array element will not exceed 100.
 * The array size will not exceed 200.
 *
 *
 *
 * Example 1:
 *
 * Input: [1, 5, 11, 5]
 *
 * Output: true
 *
 * Explanation: The array can be partitioned as [1, 5, 5] and [11].
 *
 *
 *
 * Example 2:
 *
 * Input: [1, 2, 3, 5]
 *
 * Output: false
 *
 * Explanation: The array cannot be partitioned into equal sum subsets.
 *
 ***************************************************************************************/

class Solution {
 public:
  // back tracking
  bool canPartitionRecrusion(vector<int>& nums, int half, int index) {
    for (int i = index; i < nums.size(); i++) {
      int h = half - nums[i];
      if (h < 0) return false;  // cannot found the solution
      if (h == 0) return true;  // found the solution
      if (canPartitionRecrusion(nums, h, i + 1) == true) return true;
    }
    return false;
  }

  bool canPartition(vector<int>& nums) {
    int sum = 0;
    for (auto n : nums) sum += n;
    if (sum & 1) return false;  // sum % 2 !=  1
    int half = sum / 2;

    // sort the array in descending order
    // so, the DFS could be very fast to find the answer because it's greedy.
    std::sort(nums.begin(), nums.end(), std::greater<int>());

    // go to find a path which sum is half
    return canPartitionRecrusion(nums, half, 0);
  }
};
