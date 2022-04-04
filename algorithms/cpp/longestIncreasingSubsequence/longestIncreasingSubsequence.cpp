// Source : https://leetcode.com/problems/longest-increasing-subsequence/
// Author : Calinescu Valentin, Hao Chen
// Date   : 2015-11-06

/***************************************************************************************
 * 300. 最长上升子序列
 * Given an unsorted array of integers, find the length of longest increasing
 * subsequence.
 *
 * For example,
 * Given [10, 9, 2, 5, 3, 7, 101, 18],
 * The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4.
 * Note that there may be more than one LIS combination, it is only necessary for yo
 * to return the length.
 *
 * Your algorithm should run in O(n2) complexity.
 *
 * Follow up: Could you improve it to O(n log n) time complexity?
 *
 * Credits:
 * Special thanks to @pbrother for adding this problem and creating all test cases.
 *
 ***************************************************************************************/
// my impl
// 维护一个单调递增序列， 遍历原数组， 二分查找每一个数在单调序列中的下界， 然后替换之。
// 题目要求严格递增，所以用lower_bound
// 时间复杂度O(nlogn)， 空间复杂度O(n)
class Solution {
 public:
  // 时间复杂度O(nlogn)， 空间复杂度O(n)
  int lengthOfLIS(vector<int>& nums) {
    vector<int> res;
    for (int i = 0; i < nums.size(); ++i) {
      int insertPos = lower_bound(res, 0, res.size(), nums[i]);  //为何不是res.size()-1

      if (insertPos == res.size())  //没找到的判读
        res.push_back(nums[i]);
      else
        res[insertPos] = nums[i];
    }
    return res.size();
  }

  int lower_bound(vector<int> arr, int first, int last, int target) {
    while (first < last) {
      int mid = first + (last - first) / 2;
      if (target > arr[mid])
        first = ++mid;  //要找的是 lower_bound >=target
      else
        last = mid;
    }
    return first;
  }

  //用stl
  int lengthOfLIS2(vector<int>& nums) {
    vector<int> res;
    for (int i = 0; i < nums.size(); ++i) {
      // int insertPos = lower_bound(res, 0, res.size(), nums[i]);
      auto insertPos = std::lower_bound(res.begin(), res.end(), nums[i]);
      // int pos = insertPos- v.begin();
      if (insertPos == res.end())  //没找到的判读
        res.push_back(nums[i]);
      else
        // res[insertPos] = nums[i];
        *insertPos = nums[i];
    }
    return res.size();
  }
  //用stl2
  int lengthOfLIS3(vector<int>& nums) {
    if (nums.size() == 0) return 0;

    vector<int> f;
    f.push_back(nums[0]);

    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] > f.back())
        f.push_back(nums[i]);
      else {
        auto it = std::lower_bound(f.begin(), f.end(), nums[i]);
        if (it != f.end()) *it = nums[i];
      }
    }
    return f.size();
  }
};

// O(n^2) - dynamic programming
// dp[i] 表示以位置i结尾的子序列的最大长度。
// 需要考虑状态数组的初始化，对于每个位置，它本身其实就是一个序列，都可以初始化为 1。
// dp[j] = max(dp[j], dp[i] + 1), 其中0 <= i < j, a[i] < a[j]
class Solution2 {
 public:
  int lengthOfLIS(vector<int>& nums) {
    if (nums.empty()) return 0;
    // f[i]表示以i结尾的最长递增子序列的长度
    vector<int> f(nums.size(), 1);
    int global = 1;
    for (int j = 1; j < nums.size(); ++j) {
      for (int i = 0; i < j; ++i) {
        if (nums[i] < nums[j]) {
          f[j] = max(f[j], f[i] + 1);
        }
      }
      global = max(global, f[j]);
    }
    return global;
  }
};

class Solution {
 public:
  /*
   * Solution 1 - O(N^2)
   * =========
   *
   * LIS - longest increasing subsequence
   *
   * We iterate through the elements to find the LIS that ends with the current element.
   * To do that we need to look at all of the previous elements and find one smaller than
   * the current one so that we can add the current one to the sequence terminated in the
   * smaller one. The length of the LIS ending in the current element is the length of the
   * LIS ending in the smaller one + 1. To find the maximum current LIS we need to use the
   * maximum previous LIS that satisfies the conditions.
   *
   */
  vector<int> longest_LIS;
  int lengthOfLIS(vector<int>& nums) {
    int answer = 0;
    if (nums.size()) {
      longest_LIS.push_back(1);
      answer = 1;
      for (int i = 1; i < nums.size(); i++) {
        int maximum = 1;
        for (int j = 0; j < longest_LIS.size(); j++)
          if (nums[i] > nums[j]) maximum = max(maximum, longest_LIS[j] + 1);
        longest_LIS.push_back(maximum);
        answer = max(maximum, answer);
      }
    }
    return answer;
  }
  /*
   * Solution 2 - O(N * logN)
   * =========
   *
   * LIS - longest increasing subsequence
   *
   * We iterate through the elements to find the position of the current element in the
   * current LIS. After we find its position we change the LIS replacing the next biggest
   * element with the current one or increase the size of the sequence if the current element
   * is bigger than the biggest one. This way we keep the LIS with the smallest possible
   * elements. By keeping any other LIS we can encounter an element that could have been added
   * to the LIS with the smallest elements, but can't be added to the current one, therefore
   * missing the solution.
   *
   */
  vector<int> longest_subsequence;  // the LIS
  vector<int> nums;
  int binary_search(int number) {
    int start = 0, end = longest_subsequence.size() - 1;
    if (start == end) {
      if (number > longest_subsequence[start])
        return start + 1;
      else
        return start;
    }
    while (start < end) {
      if (start == end - 1) {
        if (number > longest_subsequence[start] && number <= longest_subsequence[end])
          return end;
        else if (number <= longest_subsequence[start])
          return start;
        else
          return end + 1;
      }
      int middle = (start + end + 1) / 2;
      if (longest_subsequence[middle] < number)
        start = middle;
      else
        end = middle;
    }
  }
  int lengthOfLIS(vector<int>& nums) {
    int answer = 0;
    if (nums.size()) {
      answer = 1;
      longest_subsequence.push_back(nums[0]);
      for (int i = 1; i < nums.size(); i++) {
        int position = binary_search(nums[i]);
        if (position == longest_subsequence.size())
          longest_subsequence.push_back(nums[i]);
        else
          longest_subsequence[position] = nums[i];
        answer = max(answer, position + 1);
      }
    }
    return answer;
  }
};
