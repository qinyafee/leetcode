/**
/// @brief
239. 给你一个整数数组
nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的
k 个数字。滑动窗口每次只向右移动一位。 返回 滑动窗口中的最大值 。
///
 */

class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    if (k < 2) return nums;  //不是滑窗，直接返回
    vector<int> res;
    deque<int> deq;
    for (int i = 0; i < nums.size(); ++i) {
      while (!deq.empty() && nums[i] > nums[deq.back()]) {
        deq.pop_back();
      }
      //维护单调递减的双端队列
      deq.push_back(i);
      // 判断当前队列中队首是否还在滑动窗口里面
      if (deq.front() <= i - k) deq.pop_front();
      // 当窗口长度为k，开始保存当前窗口中最大值
      if (i >= k - 1) res.push_back(nums[deq.front()]);
    }
    return res;
  }
};