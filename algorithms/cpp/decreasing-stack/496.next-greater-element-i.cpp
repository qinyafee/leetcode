/**
/// @brief 496. 下一个更大元素 I
/// nums1 中数字 x 的 下一个更大元素 是指 x 在 nums2 中对应位置 右侧 的 第一个 比 x 大的元素。
 */


class Solution {
 public:
  vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    std::vector<int> res;
    auto res2 = nextGreaterElementHelper(nums2);  //计算nums2单调栈
    auto idmap2 = findIndexMap(nums2);            // 计算nums2的 值->下标
    for (const auto& x : nums1) {
      auto id2 = idmap2[x];
      res.push_back(res2[id2]);
    }
    return res;
  }
  // 单调栈，存放元素值，不是下标
  // https://leetcode-cn.com/problems/next-greater-element-i/solution/dan-diao-zhan-jie-jue-next-greater-number-yi-lei-w/
  vector<int> nextGreaterElementHelper(vector<int>& nums) {
    std::vector<int> res(nums.size());
    std::stack<int> stk;
    for (int i = nums.size() - 1; i >= 0; --i) {     // 倒着入栈，其实是正着出栈
      while (!stk.empty() && nums[i] >= stk.top()) {  // 判定个子高矮，注意>=
        stk.pop();  // 矮个起开，反正也被挡着了。。。
      }
      res[i] = stk.empty() ? -1 : stk.top();  // i元素身后的第一个高个
      stk.push(nums[i]);                      // 进栈，下一轮比身高
    }
    return res;
  }
  std::unordered_map<int, int> findIndexMap(const vector<int>& nums) {
    std::unordered_map<int, int> id_map;
    for (size_t i = 0; i < nums.size(); ++i) {
      id_map[nums[i]] = i;
    }
    return id_map;
  }
};
