// Source : https://leetcode.com/problems/contains-duplicate/
// Author : Hao Chen
// Date   : 2015-06-11

/**********************************************************************************
 *
 * Given an array of integers, find if the array contains any duplicates.
 * Your function should return true if any value appears at least twice in the array,
 * and it should return false if every element is distinct.
 *
 **********************************************************************************/
// my implm
// 方法1，用一个HashSet,不断往里面塞元素，如果发现有重复，说明存在重复。
// 时间复杂度O(n)，空间复杂度O(n)。

class Solution {
 public:
  bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> st;
    for (auto x : nums) {
      if (st.find(x) == st.end())
        st.insert(x);
      else
        return true;
    }
    return false;
  }
};
// 方法2，排序，然后从头到尾扫描，如果发现相邻两个元素相等，则存在重复。
// 时间复杂度O(nlogn)，空间复杂度O(1)。
// to do

class Solution {
 public:
  bool containsDuplicate(vector<int>& nums) {
    unordered_map<int, bool> m;
    for (auto item : nums) {
      if (m.find(item) != m.end()) return true;
      m[item] = true;
    }
    return false;
  }
};
