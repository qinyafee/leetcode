// 本题的意思是， 从1到n的整数， 其中某个数丢失了， 替代它的是0。 要我们找出这个丢失的数。
// 方法1， 我们可以用公式计算出从1到n的和，减去实际数组的总和， 差值就是那个丢失的数。
class Solution {
 public:
  int missingNumber(vector<int>& nums) {
    const int n = nums.size();
    const int total = n * (n + 1) / 2;
    int sums = 0;
    for (int i = 0; i < n; i++) {
      sums += nums[i];
    }
    return total - sums;
  }
};

// 方法2， 利用异或位运算， 把数组中的每一个数， 与1到n进行按位异或， 最后剩下的， 就是丢失的数。
// 方法3， 二分查找。

// Source : https://leetcode.com/problems/missing-number/
// Author : Hao Chen
// Date   : 2015-10-22

/***************************************************************************************
 *
 * Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the
 * one that is missing from the array.
 *
 * For example,
 * Given nums = [0, 1, 3] return 2.
 *
 * Note:
 * Your algorithm should run in linear runtime complexity. Could you implement it using
 * only constant extra space complexity?
 *
 * Credits:Special thanks to @jianchao.li.fighter for adding this problem and creating
 * all test cases.
 *
 ***************************************************************************************/

class Solution {
 public:
  // This problem can be converted to the classic problem --
  //    `There is an array, all of numbers except one appears twice, and that one only appears once`
  // It means, we can combin two arrays together, one is [1..n], another one is `nums`.
  // Then, you know, we can use the XOR solve this problem.

  int missingNumber01(vector<int>& nums) {
    int result = 0;
    for (int i = 0; i < nums.size(); i++) {
      result ^= nums[i];
    }
    for (int i = 1; i <= nums.size(); i++) {
      result ^= (i);
    }
    return result;
  }

  // We can simplify the previous solution as below
  int missingNumber02(vector<int>& nums) {
    int result = 0;
    for (int i = 0; i < nums.size(); i++) {
      result = result ^ (i + 1) ^ nums[i];
    }
    return result;
  }

  int missingNumber(vector<int>& nums) {
    // By Leetcode running result, they all are same performance
    return missingNumber02(nums);  // 36ms
    return missingNumber01(nums);  // 36ms
  }
};
