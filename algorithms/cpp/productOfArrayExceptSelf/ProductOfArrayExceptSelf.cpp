// Source : https://leetcode.com/problems/product-of-array-except-self/
// Author : Hao Chen
// Date   : 2015-07-17

/**********************************************************************************
 *
 * Given an array of n integers where n > 1, nums, return an array output such that
 * output[i] is equal to the product of all the elements of nums except nums[i].
 *
 * Solve it without division and in O(n).
 *
 * For example, given [1,2,3,4], return [24,12,8,6].
 *
 * Follow up:
 * Could you solve it with constant space complexity? (Note: The output array does not
 * count as extra space for the purpose of space complexity analysis.)
 *
 **********************************************************************************/

// my implm
// 两次遍历，一次正向(a[i]前面所有元素乘积)，一次反向(a[i]后面所有元素乘积)。
// nums=[a1,a2,a3,a4]
// 正向：[1, a1, a1*a2, a1*a2*a3]
// 反向：[a2*a3*a4, a3*a4, a4, 1]
// 两个数组一一对应相乘， 即可得到最终结果 [a2*a3*a4, a1*a3*a4, a1*a2*a4, a1*a2*a3]

class Solution {
 public:
  //时间O(n)，空间O(1)
  vector<int> productExceptSelf(vector<int>& nums) {
    const int n = nums.size();
    vector<int> res(n, 1);
    for (int i = 1; i < n; ++i) {
      res[i] = nums[i - 1] * res[i - 1];
    }

    int factor = 1; //一个整数代替反向遍历的数组。
    for (int i = n - 2; i >= 0; --i) {
      factor *= nums[i + 1];
      res[i] *= factor;
    }
    return res;
  }

  //时间O(n)，空间O(n)
  vector<int> productExceptSelf2(vector<int>& nums) {
    const int n = nums.size();
    vector<int> prev(n, 1);
    vector<int> tail(n, 1);
    vector<int> res(n, 1);
    for (int i = 1; i < n; ++i) {
      prev[i] = nums[i - 1] * prev[i - 1];
    }
    for (int i = n - 2; i >= 0; --i) {
      tail[i] = nums[i + 1] * tail[i + 1];
    }
    for (int i = 0; i < n; ++i) {
      res[i] = prev[i] * tail[i];
    }
    return res;
  }
};

class Solution {
 public:
  vector<int> productExceptSelf(vector<int>& nums) {
    int len = nums.size();
    vector<int> result(len, 1);

    // from the left to right
    for (int i = 1; i < len; i++) {
      result[i] = result[i - 1] * nums[i - 1];
    }
    // from the right to left
    int factorial = 1;
    for (int i = len - 2; i >= 0; i--) {
      factorial *= nums[i + 1];
      result[i] *= factorial;
    }
    return result;
  }
};
