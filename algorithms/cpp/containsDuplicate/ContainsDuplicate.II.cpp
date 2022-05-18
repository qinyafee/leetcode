// Source : https://leetcode.com/problems/contains-duplicate-ii/
// Author : Hao Chen
// Date   : 2015-06-12

/**********************************************************************************
 *
 * Given an array of integers and an integer k, find out whether there there are
 * two distinct indices i and j in the array such that nums[i] = nums[j] and
 * the difference between i and j is at most k.
 *
 *
 **********************************************************************************/
// 维护一个HashMap,key为元素，value为下标，将数组中的元素不断添加进这个HashMap。
// 碰到重复时，计算二者的下标距离，如果距离小于或等于k，则返回true；
// 如果直到数组扫描完，距离都大于k，则返回false。
class Solution {
 public:
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> mp;
    for (int i = 0; i < nums.size(); i++) {
      const int x = nums[i];
      if (mp.find(x) != mp.end() && i - mp[x] <= k) {
        return true;
      }
      mp[x] = i;  // 替换掉index
    }
    return false;
  }
};