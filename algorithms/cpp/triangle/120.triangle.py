# https://leetcode.cn/problems/triangle/description/
from typing import List

"""
状态定义：设状态为 f(i, j)， 最后一行元素到当前元素(i,j)的最小路径和
状态转移：f(i, j) = min (f(i + 1, j), f(i + 1, j + 1)) + a(i, j)
初始化：最后一行 f(n-1, j) = a(n-1, j)
结束条件：对于 [0][0]这个元素来说，最后状态表示的就是我们的最终答案。
"""


class Solution:
    # my impl 1
    # space O(1), time O(n^2)
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        n = len(triangle)
        # 从倒数第二层开始向上动态规划
        for i in range(n - 2, -1, -1):  # 层数从下往上遍历; range，左开右闭[s,e )
            for j in range(i + 1):  # 每层元素从左往右遍历
                # 当前节点值 += 下层左右两个相邻节点中较小的值
                triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1])
        return triangle[0][0]
