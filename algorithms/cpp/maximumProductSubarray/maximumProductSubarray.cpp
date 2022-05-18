// Source : https://oj.leetcode.com/problems/maximum-product-subarray/
// Author : Hao Chen
// Date   : 2014-10-09

/**********************************************************************************
 *
 * Find the contiguous subarray within an array (containing at least one number)
 * which has the largest product.
 *
 * For example, given the array [2,3,-2,4],
 * the contiguous subarray [2,3] has the largest product = 6.
 *
 * More examples:
 *
 *   Input: arr[] = {6, -3, -10, 0, 2}
 *   Output:   180  // The subarray is {6, -3, -10}
 *
 *   Input: arr[] = {-1, -3, -10, 0, 60}
 *   Output:   60  // The subarray is {60}
 *
 *   Input: arr[] = {-2, -3, 0, -2, -40}
 *   Output:   80  // The subarray is {-2, -40}
 *
 **********************************************************************************/
// my implm
// 这题跟“最大连续子序列和”非常类似，仅仅有一个小细节需要注意，就是负负得正，两个负数的乘积是正数
// 因此我们不仅要跟踪最大值， 还要跟踪最小值。
// ma[i] = max(ma[i-1]*a[i], a[i], mi[i-1]*a[i])
// mi[i] = min(ma[i-1]*a[i], a[i], mi[i-1]*a[i])
class Solution {
 public:
  // 时间复杂度O(n)， 空间复杂度O(1)
  int maxProduct(vector<int>& nums) {
    const int N = nums.size();
    if (N == 0) return 0;

    int ma = nums[0];  // local max
    int mi = nums[0];  // local min
    int global = nums[0];
    for (int i = 1; i < N; ++i) {
      int temp = ma; /** 易错点！！必须用temp*/
      ma = max(max(ma * nums[i], nums[i]), mi * nums[i]);
      mi = min(min(temp * nums[i], nums[i]), mi * nums[i]);
      global = max(global, ma);
    }

    return global;
  }
};

#include <algorithm>
#include <iostream>
using namespace std;

int max(int x, int y) {
  return x > y ? x : y;
}
int min(int x, int y) {
  return x < y ? x : y;
}
int max(int x, int y, int z) {
  return max(x, max(y, z));
}
int min(int x, int y, int z) {
  return min(x, min(y, z));
}

// The idea is similar with "Find the subarray wich has the largest sum"
// (See: http://en.wikipedia.org/wiki/Maximum_subarray_problem)
//
// The only thing to note here is, maximum product can also be obtained by minimum (negative)
// product ending with the previous element multiplied by this element. For example, in array {12,
// 2, -3, -5, -6, -2}, when we are at element -2, the maximum product is multiplication of, minimum
// product ending with -6 and -2.
//
int maxProduct(int A[], int n) {
  // To remember the max/min product for previous position
  int maxPrev = A[0], minPrev = A[0];
  // To remember the max/min product for current position
  int maxHere = A[0], minHere = A[0];
  // Overall maximum product
  int maxProd = A[0];

  for (int i = 1; i < n; i++) {
    maxHere = max(maxPrev * A[i], minPrev * A[i], A[i]);
    minHere = min(maxPrev * A[i], minPrev * A[i], A[i]);
    // Keep tracking the overall maximum product
    maxProd = max(maxHere, maxProd);
    // Shift the current max/min product to previous variables
    maxPrev = maxHere;
    minPrev = minHere;
  }
  return maxProd;
}

#define TEST(a) cout << maxProduct(a, sizeof(a) / sizeof(int)) << endl
int main() {
  int o[] = {2, 3, -2, 4};
  TEST(o);

  int a[] = {-4, -3};
  TEST(a);

  int b[] = {-1, -1};
  TEST(b);

  int c[] = {-1, 0, -2};
  TEST(c);
}
