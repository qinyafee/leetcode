// https://leetcode.cn/problems/counting-bits/solution/hen-qing-xi-de-si-lu-by-duadua/
// 对于所有的数字，只有两类：
// 奇数：二进制表示中，奇数一定比前面那个偶数多一个 1，因为多的就是最低位的 1。
// 偶数：二进制表示中，偶数中 1 的个数一定和除以 2 之后的那个数一样多。
// 因为最低位是 0，除以 2就是右移一位，也就是把那个 0 抹掉而已，所以 1 的个数是不变的。

class Solution {
 public:
  vector<int> countBits(int num) {
    vector<int> result(num + 1);
    result[0] = 0;
    for (int i = 1; i <= num; i++) {
      if (i % 2 == 1) {
        result[i] = result[i - 1] + 1;
      } else {
        result[i] = result[i / 2];
      }
    }

    return result;
  }
};

// Source : https://leetcode.com/problems/counting-bits/
// Author : Hao Chen
// Date   : 2016-05-30

/***************************************************************************************
 *
 * Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤
 * num calculate the number of 1's in their binary representation and return them as an
 * array.
 *
 * Example:
 * For num = 5 you should return [0,1,1,2,1,2].
 *
 * Follow up:
 *
 * It is very easy to come up with a solution with run time O(n*sizeof(integer)). But
 * can you do it in linear time O(n) /possibly in a single pass?
 * Space complexity should be O(n).
 * Can you do it like a boss? Do it without using any builtin function like
 * __builtin_popcount  in c++ or in any other language.
 *
 *   You should make use of what you have produced already.
 *   Divide the numbers in ranges like [2-3], [4-7], [8-15] and so on. And try to
 * generate new range from previous.
 *   Or does the odd/even status of the number help you in calculating the number of 1s?
 *
 * Credits:Special thanks to @ syedee  for adding this problem and creating all test
 * cases.
 ***************************************************************************************/

class Solution {
 public:
  /*
   * Initialization
   *
   *   bits_cnt[0] => 0000 => 0
   *   bits_cnt[1] => 0001 => 1
   *
   * if the number has 2 bits (2, 3), then we can split the binary to two parts,
   * 2 = 10 + 0  and  3= 10 + 1, then we can reuse the bits_cnt[0] and bits_cnt[1]
   *
   *   bits_cnt[2] => 0010 => 0010 + 0 => 1 + bits_cnt[0];
   *   bits_cnt[3] => 0011 => 0010 + 1 => 1 + bits_cnt[1];
   *
   * if the number has 3 bits (4,5,6,7), then we can split the binary to two parts,
   * 4 = 100 + 0,  5 = 100 + 01, 6= 100 + 10, 7 = 100 +11
   * then we can reuse the bits_cnt[0] and bits_cnt[1]
   *
   *   bits_cnt[4] => 0110 => 0100 + 00 => 1 + bits_cnt[0];
   *   bits_cnt[5] => 0101 => 0100 + 01 => 1 + bits_cnt[1];
   *   bits_cnt[6] => 0110 => 0100 + 10 => 1 + bits_cnt[2];
   *   bits_cnt[7] => 0111 => 0100 + 11 => 1 + bits_cnt[3];
   *
   * so, we can have the solution:
   *
   *   bits_cnt[x] = bits_cnt[x & (x-1) ] + 1;
   *
   */
  vector<int> countBits(int num) {
    vector<int> bits_cnt(num + 1, 0);

    for (int i = 1; i <= num; i++) {
      bits_cnt[i] = bits_cnt[i & (i - 1)] + 1;
    }
    return bits_cnt;
  }
};
