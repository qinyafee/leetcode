# https://leetcode.cn/problems/implement-queue-using-stacks/
"""
我的实现
入队push时，将元素压入s1。
出队/peek时，判断s2是否为空，如不为空，则直接弹出顶元素；如为空，则将s1的元素逐个“倒入”s2，把最后一个元素弹出并出队。
"""


class MyQueue:
    def __init__(self):
        self.stk1 = []  # 主栈，用于压入新元素
        self.stk2 = []  # 辅助栈，用于弹出队列头部元素

    def push(self, x: int) -> None:
        """将元素压入队列尾部"""
        self.stk1.append(x)

    def pop(self) -> int:
        """弹出队列头部元素"""
        if self.empty():
            return None  # 可根据需求改为 raise Exception("Queue is empty")
        self._transfer_if_needed()  # 确保 stk2 有元素
        return self.stk2.pop()

    def peek(self) -> int:
        """查看队列头部元素（不弹出）"""
        if self.empty():
            return None  # 可根据需求改为 raise Exception("Queue is empty")
        self._transfer_if_needed()  # 确保 stk2 有元素
        return self.stk2[-1]

    def empty(self) -> bool:
        """判断队列是否为空"""
        return not self.stk1 and not self.stk2

    def _transfer_if_needed(self):
        """当 stk2 为空时，将 stk1 元素反向倒入 stk2"""
        if not self.stk2:
            while self.stk1:
                self.stk2.append(self.stk1.pop())


# Your MyQueue object will be instantiated and called as such:
# obj = MyQueue()
# obj.push(x)
# param_2 = obj.pop()
# param_3 = obj.peek()
# param_4 = obj.empty()
