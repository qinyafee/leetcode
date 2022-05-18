// https://leetcode.cn/problems/excel-sheet-column-title/solution/excelbiao-lie-ming-cheng-by-leetcode-sol-hgj4/
// 26进制，
class Solution {
 public:
  string convertToTitle(int columnNumber) {
    string ans;
    while (columnNumber > 0) {
      --columnNumber;  //为了限定0<=余数<25
      char ch = columnNumber % 26 + 'A';
      ans.push_back(ch);
      columnNumber /= 26;
    }
    reverse(ans.begin(), ans.end());
    return ans;
  }
};

// Source : https://oj.leetcode.com/problems/excel-sheet-column-title/
// Author : Hao Chen
// Date   : 2014-12-25

/**********************************************************************************
 *
 * Given a positive integer, return its corresponding column title as appear in an Excel sheet.
 *
 * For example:
 *
 *     1 -> A
 *     2 -> B
 *     3 -> C
 *     ...
 *     26 -> Z
 *     27 -> AA
 *     28 -> AB
 *
 * Credits:Special thanks to @ifanchu for adding this problem and creating all test cases.
 *
 **********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

string base26_int2str(long long n) {
  string ret;
  while (n > 0) {
    char ch = 'A' + (n - 1) % 26;
    ret.insert(ret.begin(), ch);
    n -= (n - 1) % 26;
    n /= 26;
  }
  return ret;
}

long long base26_str2int(string& s) {
  long long ret = 0;
  for (int i = 0; i < s.size(); i++) {
    int n = s[i] - 'A' + 1;
    ret = ret * 26 + n;
  }
  return ret;
}

string convertToTitle(int n) {
  return base26_int2str(n);
}

int main(int argc, char** argv) {
  long long n = 27;
  if (argc > 1) {
    n = atoll(argv[1]);
  }
  string ns = base26_int2str(n);
  n = base26_str2int(ns);

  cout << n << " = " << ns << endl;

  ns = "ABCDEFG";
  if (argc > 2) {
    ns = argv[2];
  }
  cout << ns << " = " << base26_str2int(ns) << endl;
}
