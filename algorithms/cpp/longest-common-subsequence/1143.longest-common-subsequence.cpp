// 1143. 最长公共子序列
// 链接：https://leetcode.cn/problems/longest-common-subsequence/solution/zui-chang-gong-gong-zi-xu-lie-by-leetcod-y7u0/

// 定义 dp[i][j] 表示 text1 前i个元素 和 text2 前j个元素 的最长公共子序列的长度。
// 状态转移方程
// dp[i][j] = dp[i-1][j-1] + 1               当text1[i-1] == text2[j-1]
// dp[i][j] = max(dp[i-1][j], dp[i][j-1])    当text1[i-1] != text2[j-1]

// 初始化
// 当 i = 0 或j = 0时，dp[i][j]表示的为空字符串和另外一个字符串的匹配, 长度=0，dp[i][j]初始化为 0.

class Solution {
 public:
  int longestCommonSubsequence(string text1, string text2) {
    const int m = text1.length(), n = text2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
      char c1 = text1.at(i - 1);
      for (int j = 1; j <= n; j++) {
        char c2 = text2.at(j - 1);
        if (c1 == c2) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }
    return dp[m][n];
  }
};
