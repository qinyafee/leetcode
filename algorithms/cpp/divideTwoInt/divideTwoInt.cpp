// Divide Two Integers
// 最简单的方法， 是不断减去被除数。 在这个基础上， 可以做一点优化， 每次把被除数翻倍， 从而加速。
// 时间复杂度O(logn)， 空间复杂度O(1)
class Solution {
 public:
  int divide(int dividend, int divisor) {
    if (dividend == 0) return 0;
    if (divisor == 0) return INT_MAX;
    // 当 dividend = INT_MIN， divisor = -1时， 结果会溢出
    if (dividend == INT_MIN) {
      if (divisor == -1)
        return INT_MAX;
      else if (divisor < 0)
        return 1 + divide(dividend - divisor, divisor);
      else
        return -1 + divide((dividend + divisor), divisor);
    }
    if (divisor == INT_MIN) {
      return dividend == divisor ? 1 : 0;
    }
    int a = dividend > 0 ? dividend : -dividend;
    int b = divisor > 0 ? divisor : -divisor;
    int result = 0;
    while (a >= b) {
      int c = b;
      for (int i = 0; a >= c;) {
        a -= c;
        result += 1 << i;       // i是counter作用
        if (c < INT_MAX / 2) {  // prevent overflow
          ++i;
          c <<= 1;  // 左移1位，= 乘以2
        }
      }
    }
    // 用第一位是不是相同，判断正负号；相同是0，不同是1
    // return((dividend ^ divisor) >> 31) ? (-result) : (result);
  }
};

// clang-format off
// Source : https://oj.leetcode.com/problems/divide-two-integers/
// Author : Hao Chen
// Date   : 2014-06-20

/********************************************************************************** 
* 
* Divide two integers without using multiplication, division and mod operator.
* 
* If it is overflow, return MAX_INT. 
*
**********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#define INT_MAX     2147483647
#define INT_MIN     (-INT_MAX - 1)

int divide(int dividend, int divisor) {

    int sign = (float)dividend / divisor > 0 ? 1 : -1;
    unsigned int dvd = dividend > 0 ? dividend : -dividend;
    unsigned int dvs = divisor > 0 ? divisor : -divisor;

    unsigned int bit_num[33];
    unsigned int i=0;
    long long d = dvs;
    bit_num[i] = d;
    while( d <= dvd ){
        bit_num[++i] = d = d << 1;
    }
    i--;

    unsigned int result = 0;
    while(dvd >= dvs){
        if (dvd >= bit_num[i]){
            dvd -= bit_num[i];
            result += (1<<i);
        }else{
            i--;
        }
    }

    //becasue need to return `int`, so we need to check it is overflowed or not.
    if ( result > INT_MAX && sign > 0 ) {
        return INT_MAX;
    }
    return (int)result * sign;
}


int main()
{
    cout << "0/2=" << divide(0, 2) << endl;
    cout << "10/2=" << divide(10, 2) << endl;
    cout << "10/3=" << divide(10, 3) << endl;
    cout << "10/5=" << divide(10, 5) << endl;
    cout << "10/7=" << divide(10, 7) << endl;
    cout << "10/10=" << divide(10, 10) << endl;
    cout << "10/11=" << divide(10, 11) << endl;
    cout << "-1/1=" << divide(1, -1) << endl;
    cout << "1/-1=" << divide(1, -1) << endl;
    cout << "-1/-1=" << divide(-1, -1) << endl;
    cout << "2147483647/1=" << divide(2147483647, 1) << endl;
    cout << "-2147483647/1=" << divide(-2147483647, 1) << endl;
    cout << "2147483647/-1=" << divide(2147483647, -1) << endl;
    cout << "-2147483647/-1=" << divide(-2147483647, -1) << endl;
    cout << "2147483647/2=" << divide(2147483647, 2) << endl;
    cout << "2147483647/10=" << divide(2147483647, 10) << endl;
    cout << "-2147483648/1=" << divide(-2147483648, 1) << endl;
    cout << "-2147483648/-1=" << divide(-2147483648, -1) << endl;
}
