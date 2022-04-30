// Source : https://oj.leetcode.com/problems/sqrtx/
// Author : Hao Chen
// Date   : 2014-08-26

/**********************************************************************************
 *
 * Implement int sqrt(int x).
 *
 * Compute and return the square root of x.
 *
 **********************************************************************************/

#include <stdlib.h>
#include <iostream>
using namespace std;

// my implm
class Solution {
 public:
  //二分法
  int mySqrt(int x) {
    if (x < 2) return x;
    int low = 1, high = x / 2;
    int last_mid;  //记录最近一次mid

    while (low <= high) {
      const int mid = low + (high - low) / 2;
      if (x / mid > mid) {  // 不要用 x > mid * mid， 会溢出
        low = mid + 1;
        last_mid = mid;
      } else if (x / mid < mid) {
        high = mid - 1;
      } else {
        return mid;
      }
    }
    return last_mid;
  }
};

int sqrt(int x) {
  if (x <= 0) return 0;

  // the sqrt is not greater than x/2+1
  int e = x / 2 + 1;
  int s = 0;
  // binary search
  while (s <= e) {
    int mid = s + (e - s) / 2;
    long long sq = (long long)mid * (long long)mid;
    if (sq == x) return mid;
    if (sq < x) {
      s = mid + 1;
    } else {
      e = mid - 1;
    }
  }
  return e;
}

// http://en.wikipedia.org/wiki/Newton%27s_method
int sqrt_nt(int x) {
  if (x == 0) return 0;
  double last = 0;
  double res = 1;
  while (res != last) {
    last = res;
    res = (res + x / res) / 2;
  }
  return int(res);
}

int main(int argc, char** argv) {
  int n = 2;
  if (argc > 1) {
    n = atoi(argv[1]);
  }
  cout << "sqrt(" << n << ") = " << sqrt(n) << endl;
  return 0;
}

/********************** *****************************/
/** 实现 double sqrt(int N, double precision)*/

//原文链接：https://blog.csdn.net/xusiwei1236/article/details/25657611
double Sqrt(double A) {
  // 当A>1时，才有 0<=√A<=A。
  // 写成0<=√A<=A+k，令t=√A，则 0<=t<=t^2+k，推导出k>=1/4时恒成立。
  double a = 0.0； // a是左边界，left
	double b = A + 0.25;  // b = A 是错误的右边界
  double m = 0.0;
  // while(b - a > 2*DBL_EPSILON) { // sometimes dead cycle when m==a or m==b.
  for (;;) {
    m = a + (b - a) / 2;
    if (m - a < DBL_EPSILON || b - m < DBL_EPSILON) {  // 和 DBL_MAX 对应，precision误差
      break;
    }
    // 零点定理：若f(x)在(a,b)连续，且f(a)f(b)<0，则f(0)在(a, b)内有零点。
    if ((m * m - A) * (a * a - A) < 0) {  // 注意这种写法可能会溢出
      b = m;
    } else{
      a = m;
		}
  }
  return m;
}

// 不太对
// https://blog.csdn.net/qq_34269988/article/details/97179601
double getSqrt(int x, double precision) {
  double left = 0, right = x;
  while (1) {
    double mid = left + (right - left) / 2;
    if (abs(x / mid - mid) < precision)
      return mid;
    else if (x / mid > mid)
      left = mid + 1;
    else
      right = mid - 1;
  }
}

//我的实现,可以进一步优化
double sqrt(int N, double precision) {
  int i = 0;
  while (i * i <= N && (i + 1) * (i + 1) < N) ++i;

  if (i * i == N) return (double)i;

  double low = 0.0, high = 1.0;
  double t = bst(low, high, i, N);
  return i + t;
}
double bst(double low, double high, int i, int N) {
  double f1 = abs((i + low) * (i + low) - N);
  double f2 = abs((i + high) * (i + high) - N);
  double ratio = f1 / f2;
  double mid = (high - low) / 2;
  while (f > precision) {
    if (ration >= 1) mid = low + (high - mid) / 2;
    if (ration < 1) mid = low + (mid - low) / 2;
  }
  return mid;
}
