# https://leetcode.cn/problems/reverse-linked-list/


# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverseList(self, head: ListNode) -> ListNode:
        prev = None
        cur = head
        tail = None
        while cur:
            tail = cur.next  # 保存下一个节点
            cur.next = prev  # 反转指针方向
            prev = cur  # 前移prev指针
            cur = tail  # 前移cur指针
        return prev
