// 回溯
// 链接：https://leetcode.cn/problems/target-sum/solution/mu-biao-he-by-leetcode-solution-o0cp/
// 链接：https://leetcode.cn/problems/target-sum/solution/mu-biao-he-by-nehzil-x5am/
// time, O(2^n), space, O(n)
class Solution {
 public:
  int count = 0;

  int findTargetSumWays(vector<int>& nums, int target) {
    backTrace(nums, target, 0, 0);
    return count;
  }

  void backTrace(vector<int>& nums, int target, int index, int sum) {
    if (index == nums.size()) {
      if (sum == target) {
        count++;
      }
    } else {
      backTrace(nums, target, index + 1, sum + nums[index]);
      backTrace(nums, target, index + 1, sum - nums[index]);
    }
  }
};

// method2: 动态规划
// 记数组的元素和为sum，添加- 号的元素之和为 neg，则其余添加 + 的元素之和为
// sum−neg，得到的表达式的结果为 (sum−neg)−neg=sum−2⋅neg=target 即 neg=(sum−target)/2

// 定义二维数组 dp，其中 dp[i][j] 表示在数组 nums 的前 i 个数中选取元素，使得这些元素之和等于 j
// 的方案数。假设数组 nums 的长度为 n，则最终答案为 dp[n][neg]。

// 当没有任何元素可以选取时，元素和只能是 0，对应的方案数是 1，因此动态规划的边界条件是：

// 当 1≤i≤n 时，对于数组 nums 中的第 i 个元素 num（i 的计数从 11 开始），遍历 0≤j≤neg，计算 dp[i][j]
// 的值：

// 如果 j < num，则不能选 num，此时有 dp[i][j]=dp[i−1][j]；
// 如果 j ≥ num，则
// 如果不选 num，方案数是 dp[i−1][j]
// 如果选num，方案数是 dp[i−1][j−num]，
// 此时有 dp[i][j]=dp[i−1][j]+dp[i−1][j−num]。

// 01背包问题详解 https://leetcode.cn/circle/article/lUki6J/
class Solution {
 public:
  int findTargetSumWays(vector<int>& nums, int target) {
    /* 在进行动态规划算法之前需要进行下面的判断和计算 */
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) {
      sum += nums[i];
    }
    int diff = sum - target;
    if (diff < 0 || diff % 2 != 0) {
      return 0;
    }
    int n = nums.size();
    int neg = diff / 2;  // neg是背包最大容量
    /* 定义dp数组 */
    vector<vector<int>> dp(n + 1, vector<int>(neg + 1));
    /* dp数组初始化 */
    dp[0][0] = 1;
    /* 遍历 */
    for (int i = 1; i <= n; i++) {      // 先遍历物品
      for (int j = 0; j <= neg; j++) {  // 再遍历背包容量
        dp[i][j] = dp[i - 1][j];
        /* 如果背包剩余j的容量大于放的物品nums[i-1]则就可以将物品nums[i-1]放入背包中 */
        if (j >= nums[i - 1]) {
          dp[i][j] += dp[i - 1][j - nums[i - 1]];
        }
      }
    }
    return dp[n][neg];
  }
};

// Source : https://leetcode.com/problems/target-sum/
// Author : Bhavesh Mandhan
// Date   : 2020-10-21

/**********************************************************************************
 * You are given a list of non-negative integers, a1, a2, ..., an, and a target, S.
 * Now you have 2 symbols + and -. For each integer, you should choose one from + and -
 * as its new symbol.
 *
 * Find out how many ways to assign symbols to make sum of integers equal to target S.
 *
 * 	For example, given array nums is [1, 1, 1, 1, 1], S is 3.
 *
 * 	There are 5 ways to assign symbols to make the sum of nums be target 3.
 *
 * 	-1+1+1+1+1 = 3
 * 	+1-1+1+1+1 = 3
 * 	+1+1-1+1+1 = 3
 * 	+1+1+1-1+1 = 3
 * 	+1+1+1+1-1 = 3

***********************************************************************************/

class Solution {
 public:
  int findTargetSumWays(vector<int>& nums, int S) {
    long int i, j, n, tot = 0, sum, zero = 0;
    n = nums.size();
    for (i = 0; i < n; i++) {
      tot += nums[i];
      if (nums[i] == 0) {
        zero++;
      }
    }
    if ((S + tot) % 2 != 0 || S > tot) {
      return 0;
    }
    sum = (S + tot) / 2;
    int dp[n + 1][sum + 1];
    for (i = 1; i <= sum; i++) {
      dp[0][i] = 0;
    }
    for (i = 0; i <= n; i++) {
      dp[i][0] = 1;
    }
    for (i = 1; i <= n; i++) {
      for (j = 1; j <= sum; j++) {
        if (nums[i - 1] == 0 || nums[i - 1] > j) {
          dp[i][j] = dp[i - 1][j];
        } else {
          dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i - 1]];
        }
      }
    }
    return pow(2, zero) * dp[n][sum];
  }
};
