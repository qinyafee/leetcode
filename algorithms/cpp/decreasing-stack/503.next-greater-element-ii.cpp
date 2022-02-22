/**
/// @brief 503. 下一个更大元素 II
/// 给定一个循环数组 nums （ nums[nums.length - 1] 的下一个元素是 nums[0] ），返回 nums 中每个元素的
下一个更大元素 。

/// 数字 x 的 下一个更大的元素
是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出
-1 。
 */

class Solution {
 public:
  // 单调栈，存放是下标
  // https://leetcode-cn.com/problems/next-greater-element-i/solution/dan-diao-zhan-jie-jue-next-greater-number-yi-lei-w/
  vector<int> nextGreaterElements(vector<int>& nums) {
    const int N = nums.size();
    std::vector<int> res(nums.size());
    // nums.insert(nums.end(), nums.begin(), nums.end()); // 不必扩容，用除模，模拟扩容
    std::stack<int> stk;
    for (int i = 2 * N - 1; i >= 0; --i) {                // 倒着入栈，其实是正着出栈
      while (!stk.empty() && nums[i % N] >= stk.top()) {  // 判定个子高矮，注意>=
        stk.pop();  // 矮个起开，反正也被挡着了。。。
      }
      res[i % N] = stk.empty() ? -1 : stk.top();  // i元素身后的第一个高个
      stk.push(nums[i % N]);                      // 进栈，下一轮比身高
    }
    return res;
  }
};