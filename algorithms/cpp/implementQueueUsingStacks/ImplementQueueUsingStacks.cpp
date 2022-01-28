// Source : https://leetcode.com/problems/implement-queue-using-stacks/
// Author : Hao Chen
// Date   : 2015-07-16

/********************************************************************************** 
 * 
 * Implement the following operations of a queue using stacks.
 * 
 * push(x) -- Push element x to the back of queue.
 * 
 * pop() -- Removes the element from in front of queue.
 * 
 * peek() -- Get the front element.
 * 
 * empty() -- Return whether the queue is empty.
 * 
 * Notes:
 * 
 * You must use only standard operations of a stack -- which means only push to top, 
 * peek/pop from top, size, and is empty operations are valid.

 * Depending on your language, stack may not be supported natively. You may simulate a 
 * stack by using a list or deque (double-ended queue), as long as you use only 
 * standard operations of a stack.

 * You may assume that all operations are valid (for example, no pop or peek operations 
 * will be called on an empty queue).
 *               
 **********************************************************************************/

/** 我的实现
 * 入队push时，将元素压入s1。
 * 出队/peek时，判断s2是否为空，如不为空，则直接弹出顶元素；如为空，则将s1的元素逐个“倒入”s2，把最后一个元素弹出并出队。
*/
class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {

    }
    stack<int> stk1, stk2;
    /** Push element x to the back of queue. */
    void push(int x) {
        stk1.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        //考虑异常
        if(stk1.empty() && stk2.empty()) return INT_MIN;
        if(stk2.empty()){
            while(!stk1.empty()){
                stk2.push(stk1.top());
                stk1.pop();
            }
        }
        int x = stk2.top();
        stk2.pop();
        return x;

    }
    
    /** Get the front element. */
    int peek() {
        //考虑异常
        if(stk1.empty() && stk2.empty()) return INT_MIN;        
        if(stk2.empty()){
            while(!stk1.empty()){
                stk2.push(stk1.top());
                stk1.pop();
            }
        }
        return stk2.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return stk1.empty() && stk2.empty(); //二者均为空，则空
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */



class Queue {
public:
    // Push element x to the back of queue.
    void push(int x) {
        s1.push(x);
    }

    // Removes the element from in front of queue.
    void pop(void) {
        transfer(s1, s2);
        s2.pop();
        transfer(s2, s1);
    }

    // Get the front element.
    int peek(void) {
        transfer(s1, s2);
        int ret = s2.top();
        transfer(s2, s1);
        return ret;
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return s1.empty();
    }
private:
    stack<int> s1, s2;
    void transfer(stack<int>& s1, stack<int>& s2) {
        while(!s1.empty()){
            s2.push(s1.top());
            s1.pop();
        }
    }
};

