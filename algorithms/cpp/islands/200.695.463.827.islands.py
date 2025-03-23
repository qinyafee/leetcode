# 200. Number of Islands 岛屿数量, https://leetcode-cn.com/problems/number-of-islands

from typing import List


class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        # 处理空网格的情况
        if not grid:
            return 0

        rows, cols = len(grid), len(grid[0])
        count = 0

        # !嵌套
        def dfs(i, j):
            # 边界条件检查及陆地判断
            if i < 0 or j < 0 or i >= rows or j >= cols or grid[i][j] != "1":
                return

            # 标记已访问的陆地
            grid[i][j] = "2"

            dfs(i - 1, j)  # 上
            dfs(i + 1, j)  # 下
            dfs(i, j - 1)  # 左
            dfs(i, j + 1)  # 右

        for i in range(rows):
            for j in range(cols):
                if grid[i][j] == "1":
                    dfs(i, j)
                    count += 1  # 发现新岛屿时计数增加
        return count
