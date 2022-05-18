// Source : https://leetcode.com/problems/contains-duplicate-iii/
// Author : Hao Chen
// Date   : 2015-06-12

/**********************************************************************************
 *
 * Given an array of integers, find out whether there are two distinct indices i and j
 * in the array such that the difference between nums[i] and nums[j] is at most t and
 * the difference between i and j is at most k.
 *
 **********************************************************************************/
// method1 滑动窗口+bst(std::set)
// 维护k大小的bst，找到|nums[j]-num[i]|<=t
// https://leetcode-cn.com/problems/contains-duplicate-iii/solution/jian-dan-yi-dong-de-cjie-fa-by-zhu-que-3-4p53/
class Solution {
 public:
  bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    // 滑动窗口
    set<long> st;  // long 防溢出
    for (int i = 0; i < nums.size(); ++i) {
      // 1.找到nums[j]>=nums[i]-t的数中最小的数j
      auto j = st.lower_bound(long(nums[i]) - t);
      // 2.从|nums[j]-num[i]|<=t 推导得 i-t <= j <= i+t，满足即可
      if (j != st.end() && *j <= long(nums[i]) + t) {
        return true;
      }
      st.insert(nums[i]);
      if (st.size() > k) {
        st.erase(nums[i - k]);  //删除滑窗第一个元素
      }
    }
    return false;
  }
};

// method2 桶排序
// to do

class Solution {
 public:
  bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    if (nums.size() < 2 || k == 0) return false;
    int low = 0;
    // maintain a sliding window
    set<long long> window;
    for (int i = 0; i < nums.size(); i++) {
      // make sure window size <= k
      if (i - low > k) {
        window.erase(nums[low]);
        low++;
      }

      // lower_bound() is the key,
      // it returns an iterator pointing to the first element >= val
      auto it = window.lower_bound((long long)nums[i] - (long long)t);
      if (it != window.end() && abs((long long)nums[i] - *it) <= (long long)t) {
        return true;
      }
      window.insert(nums[i]);
    }
    return false;
  }
};
