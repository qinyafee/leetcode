# https://leetcode.cn/problems/valid-palindrome/


class Solution:
    # 时间复杂度O(n)， 空间复杂度O(1)【不增加额外存储，best practice】
    def isPalindrome(self, s: str) -> bool:
        left, right = 0, len(s) - 1
        while left < right:
            # 跳过非字母数字字符，移动左指针
            while left < right and not s[left].isalnum():
                left += 1
            # 跳过非字母数字字符，移动右指针
            while left < right and not s[right].isalnum():
                right -= 1
            # 比较字符（忽略大小写）
            if s[left].lower() != s[right].lower():
                return False
            # 移动指针继续比较
            left += 1
            right -= 1
        return True
