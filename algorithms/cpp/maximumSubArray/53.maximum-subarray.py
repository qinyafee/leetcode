# https://leetcode.cn/problems/maximum-subarray/description/


from typing import List

"""
对于数组里的一个整数，它只有两种选择： 1、加入之前的SubArray；2. 自己另起一个SubArray。
1.状态定义 f[i]， 表示以 a[i] 结尾的最大连续子序列和.
2.状态转移方程 f[i] = max(f[i-1], 0) + a[i]
3.初始化 f[0] = a[0]
4.结果 max(f[i]), f[0], f[1], ..., f[n-1] 中的最大值
"""


# 时间复杂度O(n)， 空间复杂度O(1)
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        if not nums:
            return 0
        localmax = globalmax = nums[0]
        for num in nums[1:]:
            localmax = max(0, localmax) + num
            globalmax = max(globalmax, localmax)

        return globalmax
