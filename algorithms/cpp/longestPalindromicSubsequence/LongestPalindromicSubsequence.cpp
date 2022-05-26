// Source : https://leetcode.com/problems/longest-palindromic-subsequence/
// Author : Hao Chen
// Date   : 2021-03-27

/*****************************************************************************************************
 *
 * Given a string s, find the longest palindromic subsequence's length in s.
 *
 * A subsequence is a sequence that can be derived from another sequence by deleting some or no
 * elements without changing the order of the remaining elements.
 *
 * Example 1:
 *
 * Input: s = "bbbab"
 * Output: 4
 * Explanation: One possible longest palindromic subsequence is "bbbb".
 *
 * Example 2:
 *
 * Input: s = "cbbd"
 * Output: 2
 * Explanation: One possible longest palindromic subsequence is "bb".
 *
 * Constraints:
 *
 * 	1 <= s.length <= 1000
 * 	s consists only of lowercase English letters.
 ******************************************************************************************************/

/*

   supposed s = "abbcba"

   we can have a matrix,

   - dp[i, j] is the longest from s[i] to s[j]

   - if (i == j) dp[statr, j] = 1, it means every char can be palindromic

            a b b c b a
         a  1 0 0 0 0 0
         b  0 1 0 0 0 0
         b  0 0 1 0 0 0
         c  0 0 0 1 0 0
         b  0 0 0 0 1 0
         a  0 0 0 0 0 1



  calculating from the bottom to up. (Note: only care about the top-right trangle)

            a  b  b  c  b  a
         a  1  1  2  2  3 [5]  <--  a == a , so "abbcba" comes from "bbcb" + 2
         b  0  1 [2] 2  3  3   <--  b == b , so "bb" comes from "" + 2
         b  0  0  1  1 [3] 3   <--  b == b , so "bcb" comes from "c" + 2
         c  0  0  0  1  1 [1]  <--  c != a , so "cba" comes from max("cb", "a")
         b  0  0  0  0  1 [1]  <--  b != a , so "ba" comes from max ("b", "a")
         a  0  0  0  0  0  1

  So, we can have the following formular:

       s[i] != s[j]  ==> dp[i, j] = max (dp[i+1, j], dp[i, j-1]);
       s[i] == s[j]  ==> dp[i, j] = dp[i+1, j-1] + 2;

*/

// 对比 5.Longest Palindromic Substring

// 1.状态
// f[i][j] 表示 s 的第 i 个字符到第 j 个字符组成的子串中，最长的回文序列长度是多少。

// 2.转移方程
// 2.1如果 s 的第 i 个字符和第 j 个字符相同的话
// f[i][j] = f[i + 1][j - 1] + 2

// 2.2如果 s 的第 i 个字符和第 j 个字符不同的话
// f[i][j] = max(f[i + 1][j], f[i][j - 1])

// 然后注意遍历顺序，i 从最后一个字符开始往前遍历，
// j 从 i + 1开始往后遍历，这样可以保证每个子问题都已经算好了。

// 3.初始化
// f[i][i] = 1 单个字符的最长回文序列是 1

// 4.结果
// f[0][n - 1]
// 链接：https://leetcode.cn/problems/longest-palindromic-subsequence/solution/dong-tai-gui-hua-si-yao-su-by-a380922457-3/
// time/space: O(n^2)
class Solution {
 public:
  int longestPalindromeSubseq(string s) {
    const int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = n - 1; i >= 0; --i) {
      dp[i][i] = 1;
      for (int j = i + 1; j < n; ++j) {
        if (s[i] == s[j]) {
          dp[i][j] = dp[i + 1][j - 1] + 2;
        } else {
          dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
      }
    }
    return dp[0][n - 1];
  }
};
