// Source : https://oj.leetcode.com/problems/decode-ways/
// Author : Hao Chen
// Date   : 2014-07-16

/**********************************************************************************
 *
 * A message containing letters from A-Z is being encoded to numbers using the following mapping:
 *
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 *
 * Given an encoded message containing digits, determine the total number of ways to decode it.
 *
 * For example,
 * Given encoded message "12",
 * it could be decoded as "AB" (1 2) or "L" (12).
 *
 * The number of ways decoding "12" is 2.
 *
 *
 **********************************************************************************/
// my implm
/**
动态规划，和Climbing Stairs思路类似，但是分情况比较细。
dp为str[0....i]的译码方法总数
1.
if(s[i]=='0')
  if(s[i - 1] == '1' || s[i - 1] == '2')
    dp[i] = dp[i-2]; //因为s[i-1]+s[i]被唯一译码，所以不增加方法数量
  else
    return 0; //整个str无法被译码
2.
else if(s[i-1]=='1') // 此时s[i]！='0'
  dp[i] = dp[i-1] + dp[i-2]; //s[i-1]+s[i]合并译码的数量=dp[i-2]；s[i-1]+s[i]分开译码的数量=dp[i-1]
3.
else if(s[i-1]=='2') // 此时s[i]！='0'
  if('1' <= s[i] <= '6')
    dp[i] = dp[i-1] + dp[i-2];
//s[i-1]+s[i]合并译码的数量=dp[i-2]；s[i-1]+s[i]分开译码的数量=dp[i-1] else dp[i] = dp[i-1];

dp仅和前两项有关，单变量替换dp数组，空间复杂度从O(n)降到O(1)
https://leetcode-cn.com/problems/decode-ways/solution/c-wo-ren-wei-hen-jian-dan-zhi-guan-de-jie-fa-by-pr/
*/
class Solution {
 public:
  int numDecodings(string s) {
    if (s[0] == '0') return 0;
    int pre = 1, curr = 1;  // dp[-1] = dp[0] = 1
    for (int i = 1; i < s.size(); i++) {
      int tmp = curr; /** 易错点*/
      if (s[i] == '0')
        if (s[i - 1] == '1' || s[i - 1] == '2')
          curr = pre;
        else
          return 0;
      else if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] >= '1' && s[i] <= '6'))
        curr = curr + pre;
      pre = tmp;
    }
    return curr;
  }

  //用数组，，不好设计，没调通
  // int numDecodings(string s) {
  //     if(s.empty() || s[0]=='0')
  //         return 0;

  //     const int N = s.size();
  //     vector<int> f(N,0);
  //     f[0]=1;
  //     if(N==1) return 1;

  //     if((s[0]=='1' && s[1] !='0') || (s[0]=='2' && '1'<= s[1]&& s[1]<='6'))
  //         f[1]=2;

  //     for(int i = 2; i < N; ++i){
  //         if(s[i]=='0'){
  //             //1. s[i-1]+s[i]被唯一解码，所以 f[i] = f[i-2]
  //             if(s[i-1]=='1' || s[i-1]=='2')
  //                 f[i] = f[i-2];
  //             else
  //                 return 0;
  //         }
  //         //2. s[i-1]=='1'，则 f[i] = f[i-1] +f[i-2]
  //         //3. s[i-2]=='2'&& '1'<= s[i] <='6'，则 f[i] = f[i-1] +f[i-2]
  //         else if(s[i-1]=='1' || (s[i-1]=='2' && '1'<= s[i]&& s[i]<='6')){
  //             f[i] = f[i-1] +f[i-2];
  //         }
  //     }
  //     return f[N-1];
  // }
};

#include <string.h>
#include <iostream>
#include <string>
using namespace std;

// Count[i] = Count[i-1]              if S[i-1] is a valid char (not '0')
//         = Count[i-1]+ Count[i-2]  if S[i-1] and S[i-2] together is still a valid char (10 to 26).

int check(char ch) {
  // check 0 or not
  return (!isdigit(ch) || ch == '0') ? 0 : 1;
}

int check(char ch1, char ch2) {
  // check it's between 10 and 26
  return (ch1 == '1' || (ch1 == '2' && ch2 <= '6')) ? 1 : 0;
}

int numDecodings(string s) {
  if (s.size() <= 0) return 0;
  if (s.size() == 1) return check(s[0]);

  int* dp = new int[s.size()];
  memset(dp, 0, s.size() * sizeof(int));

  dp[0] = check(s[0]);
  dp[1] = check(s[0]) * check(s[1]) + check(s[0], s[1]);
  for (int i = 2; i < s.size(); i++) {
    if (!isdigit(s[i])) break;
    if (check(s[i])) {
      dp[i] = dp[i - 1];
    }
    if (check(s[i - 1], s[i])) {
      dp[i] += dp[i - 2];
    }
  }
  int result = dp[s.size() - 1];
  delete[] dp;
  return result;
}

int main(int argc, char** argv) {
  string s = "123";
  if (argc > 1) {
    s = argv[1];
  }
  cout << "\"" << s << "\" : " << numDecodings(s) << endl;
  return 0;
}
