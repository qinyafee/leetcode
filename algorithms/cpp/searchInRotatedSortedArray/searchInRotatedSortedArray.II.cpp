// Source : https://oj.leetcode.com/problems/search-in-rotated-sorted-array-ii/
// Author : Hao Chen
// Date   : 2014-06-29

/**********************************************************************************
 *
 * Follow up for "Search in Rotated Sorted Array":
 * What if duplicates are allowed?
 *
 * Would this affect the run-time complexity? How and why?
 *
 * Write a function to determine if a given target is in the array.
 *
 **********************************************************************************/

// Using the same idea "Search in Rotated Sorted Array"
// but need be very careful about the following cases:
//   [3,3,3,4,5,6,3,3]
//   [3,3,3,3,1,3]
// After split, you don't know which part is rotated and which part is not.
// So, you have to skip the ducplication
//   [3,3,3,4,5,6,3,3]
//          ^       ^
//   [3,3,3,3,1,3]
//            ^ ^

// my implm
// 允许重复元素， 则上一题【33.不允许重复】中。如果 A[left] <= A[mid] ,那么 [left,mid]
// 为递增序列的假设就不能成立了， 比如 [1,3,1,1,1] 。
// 既然 A[left] <= A[mid] 不能确定递增，那就把它拆分成两个条件：
//  若 A[left] < A[mid] ， 则区间 [left,mid] 一定递增
//  若 A[left] == A[mid] 确定不了， 那就 left++ ，往下看一步即可。

class Solution {
 public:
  bool search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
      const int mid = left + (right - left) / 2;
      if (nums[mid] == target) {
        return true;
      }
      if (nums[left] < nums[mid]) {                        // 左边有序
        if (nums[left] <= target && target < nums[mid]) {  // target 在左边
          right = mid - 1;
        } else {
          left = mid + 1;
        }
      } else if (nums[left] > nums[mid]) {                  // 右边有序
        if (nums[mid] < target && target <= nums[right]) {  // target 在右边
          left = mid + 1;
        } else {
          right = mid - 1;
        }
      } else {
				++left; // 不能判断哪边有序，跳过重复
			}
    }
    return false;
  }
};

class Solution {
 public:
  bool search(int A[], int n, int key) {
    if (n <= 0) return false;

    if (n == 1) {
      return (A[0] == key) ? true : false;
    }
    int low = 0, high = n - 1;
    while (low <= high) {
      if (A[low] < A[high] && (key < A[low] || key > A[high])) {
        return false;
      }

      // if dupilicates, remove the duplication
      while (low < high && A[low] == A[high]) {
        low++;
      }

      int mid = low + (high - low) / 2;
      if (A[mid] == key) return true;

      // the target in non-rotated array
      if (A[low] < A[mid] && key >= A[low] && key < A[mid]) {
        high = mid - 1;
        continue;
      }
      // the target in non-rotated array
      if (A[mid] < A[high] && key > A[mid] && key <= A[high]) {
        low = mid + 1;
        continue;
      }
      // the target in rotated array
      if (A[low] > A[mid]) {
        high = mid - 1;
        continue;
      }
      // the target in rotated array
      if (A[mid] > A[high]) {
        low = mid + 1;
        continue;
      }

      // reach here means nothing found.
      low++;
    }
    return false;
  }
};
