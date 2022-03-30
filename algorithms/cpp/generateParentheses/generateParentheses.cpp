// Source : https://oj.leetcode.com/problems/generate-parentheses/
// Author : Hao Chen
// Date   : 2014-06-29

/**********************************************************************************
 *
 * Given n pairs of parentheses, write a function to generate all combinations of well-formed
 *parentheses.
 *
 * For example, given n = 3, a solution set is:
 *
 * "((()))", "(()())", "(())()", "()(())", "()()()"
 *
 *
 **********************************************************************************/

#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

// my impl
// 动态规划 https://leetcode-cn.com/problems/generate-parentheses/solution/zui-jian-dan-yi-dong-de-dong-tai-gui-hua-bu-lun-da/

class Solution {
 public:
  vector<string> generateParenthesis(int n) {
    if (n == 0) return {};
    if (n == 1) return {"()"};
    vector<vector<string>> dp(n + 1);
    dp[0] = {""};
    dp[1] = {"()"};
    for (int i = 2; i <= n; i++) {
      for (int j = 0; j < i; j++) {
        for (string p : dp[j])
          for (string q : dp[i - j - 1]) {
            string str = "(" + p + ")" + q;
            dp[i].push_back(str);
          }
      }
    }
    return dp[n];
  }
};

void generator(vector<string>& result, int left, int right, string s);
vector<string> generateParenthesis(int n) {
  vector<string> result;
  string s;
  generator(result, n, n, s);
  return result;
}

void generator(vector<string>& result, int left, int right, string s) {
  if (left == 0 && right == 0) {
    result.push_back(s);
    return;
  }
  if (left > 0) {
    generator(result, left - 1, right, s + '(');
  }
  if (right > 0 && right > left) {
    generator(result, left, right - 1, s + ')');
  }
}

void printResult(vector<string>& result) {
  for (int i = 0; i < result.size(); i++) {
    cout << result[i] << endl;
  }
}

int main(int argc, char** argv) {
  int n = 3;
  if (argc > 1) {
    n = atoi(argv[1]);
  }
  vector<string> r = generateParenthesis(n);
  printResult(r);
  return 0;
}
