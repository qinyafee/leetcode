/**
/// @brief 739. 每日温度
/// 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指在第 i 天之后，才会有更高的温度。如果气温在这之后都不会升高，请在该位置用 0 来代替。
 */

class Solution {
 public:
  vector<int> dailyTemperatures(vector<int>& nums) {
    std::vector<int> res(nums.size());
    std::stack<int> stk;
    for (int i = nums.size() - 1; i >= 0; --i) {            // 倒着入栈，其实是正着出栈
      while (!stk.empty() && nums[i] >= nums[stk.top()]) {  // 判定个子高矮，注意>=。严格单调栈
        stk.pop();  // 矮个起开，反正也被挡着了。。。
      }
      res[i] = stk.empty() ? 0 : stk.top() - i;  // i元素身后的第一个高个
      stk.push(i);                               // 进栈，下一轮比身高
    }
    return res;
  }
};