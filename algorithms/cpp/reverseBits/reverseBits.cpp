// Source : https://leetcode.com/problems/reverse-bits/
// Author : Hao Chen
// Date   : 2015-03-30

/**********************************************************************************
 *
 * Reverse bits of a given 32 bits unsigned integer.
 *
 * For example, given input 43261596 (represented in binary as 00000010100101000001111010011100),
 * return 964176192 (represented in binary as 00111001011110000010100101000000).
 *
 * Follow up:
 * If this function is called many times, how would you optimize it?
 *
 * Related problem: Reverse Integer
 *
 * Credits:Special thanks to @ts for adding this problem and creating all test cases.
 *
 **********************************************************************************/
// method1
// 从右向左把一位位取出来， 添加到新生成的整数的最低位即可。
class Solution {
 public:
  uint32_t reverseBits(uint32_t n) {
    int res = 0;
    for (int i = 0; i < 32;) {
      int flag = 1 & (n >> (i++));  // 判断第i位是否=1
      res = (res << 1) + flag;
    }
    return res;
  }
};

class Solution {
 public:
  uint32_t reverseBits(uint32_t n) {
    uint32_t ret = 0;
    for (int i = 0; i < 32; i++) {
      ret = (ret * 2) + (n & 0x1);
      n /= 2;
    }
    return ret;
  }
};

// method2 位运算分治,见其他题解
