// 方法1： 创建一个长度为 sizeof(int) 的数组 count[sizeof(int)] ， count[i] 表示在 i位
// 出现的1的次数。 如果 count[i] 是3的整数倍， 则忽略； 否则就把该位取出来组成答案。
// 方法1， 时间复杂度O(n)， 空间复杂度O(1)
class Solution {
 public:
  int singleNumber(vector<int>& nums) {
    const int W = sizeof(int) * 8;  // 一个整数的bit数， 即整数字长
    int count[W];                   // count[i]表示在在i位出现的1的次数
    fill_n(&count[0], W, 0);
    for (int i = 0; i < nums.size(); i++) {
      for (int j = 0; j < W; j++) {
        count[j] += (nums[i] >> j) & 1;
        count[j] %= 3;
      }
    }
    int result = 0;
    for (int i = 0; i < W; i++) {
      result += (count[i] << i);
    }
    return result;
  }
};

// 方法2： 位操作
// 用 one 记录到当前处理的元素为止， 二进制1出现“1次”（ mod 3 之后的 1） 的有哪些二进制位；
// 用 two 记录到当前计算的变量为止， 二进制1出现“2次”（ mod 3 之后的 2） 的有哪些二进制位。
// 当 one 和 two 中的某一位同时为1时表示该二进制位上1出现了3次， 此时需要清零。
// 即用二进制模拟三进制运算。 最终 one 记录的是最终结果。
// 方法2， 时间复杂度O(n)， 空间复杂度O(1)
class Solution {
 public:
  int singleNumber(vector<int>& nums) {
    int one = 0, two = 0, three = 0;
    for (int i : nums) {
      two |= (one & i); // 1出现2次的位
      one ^= i; // 1出现1次的位
      three = ~(one & two); //出现三次，清零
      one &= three;
      two &= three;
    }
    return one;
  }
};
// Source : https://oj.leetcode.com/problems/single-number-ii/
// Author : Hao Chen
// Date   : 2014-06-17

/**********************************************************************************
 *
 * Given an array of integers, every element appears three times except for one. Find that single
 *one.
 *
 * Note:
 * Your algorithm should have a linear runtime complexity. Could you implement it without using
 *extra memory?
 *
 *
 **********************************************************************************/

class Solution {
 public:
  Solution() {
    srand(time(0));
  }

  // random invoker
  int singleNumber(int A[], int n) {
    if (rand() % 2) {
      return singleNumber_1(A, n);
    }
    return singleNumber_2(A, n);
  }

  /*
   *  This solution is clear & straightforward implementation.
   *
   *  We use an array of 32 length(e.g. count[32]) to count the the bits for all of numbers.
   *
   *  Because the same number appear 3 times, which means the sum of i-th bits for all numbers
   * should be 3 times.
   *
   *  In other word, the sum of the i-th bits mod 3, it must be 0 or 1. 1 means that is the single
   * number bit.
   *
   * This solution can be easy to extend to "every element appears k times except for one."
   *
   */
  int singleNumber_1(int A[], int n) {
    int count[32] = {0};
    int result = 0;
    for (int i = 0; i < 32; i++) {
      for (int j = 0; j < n; j++) {
        if ((A[j] >> i) & 1) {
          count[i]++;
        }
      }
      result |= ((count[i] % 3) << i);
    }
    return result;
  }

  /*
   *   The following solution is popular solution on Internet, but it looks it's not easy to
   * understand.
   *
   *   Actually, it just optimizes the above soultion.
   *
   *   Let's see how it improve the above.
   *
   *   We use three bitmasks,
   *    1) `ones`     as a bitmask which represents the i-th bit had appeared once.
   *    2) `twos`     as a bitmask which represents the i-th bit had appeared twice.
   *    3) `threes`   as a bit mask which represents the i-th bit had appeared three times.
   *
   *    When the i-th bit had appeared for the third time, clear the i-th bit of both `ones` and
   * `twos` to 0. The final answer will be the value of `ones`
   *
   */
  int singleNumber_2(int A[], int n) {
    int ones = 0, twos = 0, threes = 0;
    for (int i = 0; i < n; i++) {
      // `ones & A[i]` the result is the bitmask which the bits appeared twice
      twos |= ones & A[i];
      // XOR means remove the bit which appeared twice int `ones`
      ones ^= A[i];
      // count the `three`
      threes = ones & twos;
      // clear the `ones` and `twos` if the i-th bit had appeared three times.
      ones &= ~threes;
      twos &= ~threes;
    }
    return ones;
  }
};
