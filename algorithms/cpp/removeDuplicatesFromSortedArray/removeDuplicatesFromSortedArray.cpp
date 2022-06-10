// Source : https://oj.leetcode.com/problems/remove-duplicates-from-sorted-array/
// Author : Hao Chen
// Date   : 2014-06-22

/**********************************************************************************
 *
 * Given a sorted array, remove the duplicates in place such that each element appear
 * only once and return the new length.
 *
 * Do not allocate extra space for another array, you must do this in place with constant memory.
 *
 * For example,
 * Given input array A = [1,1,2],
 *
 * Your function should return length = 2, and A is now [1,2].
 *
 *
 **********************************************************************************/
// my implm
// 双指针
class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) {
      return 0;
    }
    int i = 0;  //输出结果index
    for (int j = 1; j < nums.size(); ++j) {
      if (nums[i] == nums[j]) {
        continue;
      } else {
        nums[++i] = nums[j];
      }
    }
    return i + 1;
  }
};

// 变种：如果数组未排序，输出结果数组。[1,3,4,2,2,2,1,5] ->[1, 3, 4, 2, 5]
// 哈希+双指针
void removeDuplicates(vector<int>& nums) {
  unordered_set<int> st;

  int i = 0;
  for (int j = 0; j < nums.size(); ++j) {
    if (st.find(nums[j]) != st.end()) {
      continue;
    } else {
      st.insert(nums[j]);
      nums[i++] = nums[j];
    }
  }
  nums.erase(nums.begin() + i, nums.end());
  // for (const auto &x : nums) {
  //   cout << x << ", ";
  // }
}

class Solution {
 public:
  int removeDuplicates(int A[], int n) {
    if (n <= 1) return n;

    int pos = 0;
    for (int i = 0; i < n - 1; i++) {
      if (A[i] != A[i + 1]) {
        A[++pos] = A[i + 1];
      }
    }
    return pos + 1;
  }
};
