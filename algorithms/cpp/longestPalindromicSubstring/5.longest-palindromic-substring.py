# https://leetcode.cn/problems/longest-palindromic-substring/

import numpy as np

"""my implm
动规，时间复杂度O(n^2)， 空间复杂度O(n^2)
设状态为 f(i,j) ， 表示区间[i,j]是否为回文串
状态转移方程为:
1. f[i][j] = true, i=j;
2. f[i][j] = (s[i]==s[j]), j=i+1;
3. f[i][j] = (s[i]==s[j] && f[i+1][j-1]), j>i+1;"""


class Solution:
    # 时间复杂度 O(n^2)，空间复杂度 O(n^2)
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        if n == 0:
            return ""
        #!运行超时
        dp = np.full((n, n), False, dtype=bool)  # 初始化 NumPy 布尔矩阵
        np.fill_diagonal(dp, True)  # case1 对角线填充 True
        max_len = 1
        start = 0
        for j in range(n):
            for i in range(j):  # 区间[i,j]
                # if j == i + 1 and s[i] == s[j]: #case2
                #     dp[i][j] = True
                # if j > i+1 and dp[i+1][j-1] and s[i] == s[j]: #case3
                #     dp[i][j] = True
                # case2 + case3，可换成下面一行
                dp[i][j] = (s[i] == s[j]) and (j - i < 2 or dp[i + 1][j - 1])
                if dp[i][j] and max_len < j - i + 1:
                    start = i
                    max_len = j - i + 1
        return s[start : start + max_len]
