// Source : https://oj.leetcode.com/problems/climbing-stairs/
// Author : Hao Chen
// Date   : 2014-06-27

/**********************************************************************************
 *
 * You are climbing a stair case. It takes n steps to reach to the top.
 *
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 *
 *
 **********************************************************************************/
// my implm
// 1.动态规划：f(n)=f(n-1)+f(n-2)
// 2.数学公式
class Solution {
 public:
  int climbStairs(int n) {
    int prev = 0;                   // n=0，有0种方法
    int cur = 1;                    // n=1, 有一种方法
    for (int i = 1; i <= n; ++i) {  // 注意 <=
      int tmp = cur;
      cur += prev;
      prev = tmp;
    }
    return cur;
  }

  int climbStairs2(int n) {
    if (n < 2) return 1;
    int prev = 1;  //和书上不一样，他的更好理解。
    int curr = 1;
    for (int i = 1; i < n; ++i) {
      int tmp = curr;
      curr = prev + tmp;
      prev = tmp;
    }
    return curr;
  }

  // int climbStairs3(int n) {
  //     if(n < 2) return 1;
  //     vector<int> dp(n,0);
  //     dp[0]=1;
  //     dp[1]=2;
  //     for(int i = 2; i < n; ++i){
  //         dp[i] = dp[i-1] + dp[i-2];
  //     }
  //     return dp[n-1];
  // }
};

// Problem2 变态跳台阶
// 一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。

// 分析
// 易知 f(n)=f(n-1)+f(n-2)+……f(1)
// f(n-1)=f(n-2)+……f(1)
// 两式相减得f(n)=2f(n-1)

class Solution {
 public:
  int jumpFloorII(int number) {
    if (number <= 0) {
      return -1;
    } else if (number == 1) {
      return 1;
    } else {
      { return 2 * jumpFloorII(number - 1); }
    }
  }
};

// 爬楼梯变种总结
// https://blog.csdn.net/wjhshuai/article/details/68952756
// 上n个台阶，每次一步或两步，求走法数量，简单DP。
// 上一题变形，最多只能连续走m次两步。依然DP，dp[i][j]表示到第i级台阶，前面连续走了j次两步的走法数量。写出转移方程，面试官没有让写代码。

// clang-format off
class Solution {
public:
    
    int climbStairs(int n) {
       if (n<=3) return n;
       int a[2]={2,3};
       for(int i=4; i<=n; i++){
           int t = a[0] + a[1];
           a[0] = a[1];
           a[1] = t;
       }
       return a[1];
    }
    //Time too long
    int climbStairs2(int n) {
        if (n<=3) return n;
        return climbStairs(n-1) + climbStairs(n-2);
    }
};
