// Source : https://oj.leetcode.com/problems/palindrome-partitioning/
// Author : Hao Chen
// Date   : 2014-08-21

/**********************************************************************************
 *
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 *
 * Return all possible palindrome partitioning of s.
 *
 * For example, given s = "aab",
 *
 * Return
 *
 *   [
 *     ["aa","b"],
 *     ["a","a","b"]
 *   ]
 *
 *
 **********************************************************************************/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// my implm
// 链接：https://leetcode-cn.com/problems/palindrome-partitioning/solution/fen-ge-hui-wen-chuan-by-leetcode-solutio-6jkv/
// https://leetcode-cn.com/problems/palindrome-partitioning/solution/shou-hua-tu-jie-san-chong-jie-fa-hui-su-q5zjt/
class Solution {
 private:
  vector<vector<int>> f;  //动规结果
  vector<vector<string>> ret; //最后返回结果
  vector<string> ans; //每轮切分的临时结果
  int n;

 public:
 // 时间： O(n*n^2)； 空间：O(n^2)
  vector<vector<string>> partition(string s) {
    // 判断f[i][j]是否回文
    n = s.size();
    f.assign(n, vector<int>(n, true));//原题没用vector，超时

    for (int i = n - 1; i >= 0; --i) {
      for (int j = i + 1; j < n; ++j) {
        f[i][j] = (s[i] == s[j]) && f[i + 1][j - 1];
      }
    }

    backTrace(s, 0);
    return ret;
  }

  void backTrace(const string& s, int i) {  // i = start
    if (i == n) {
      ret.push_back(ans);
      return;
    }
    for (int j = i; j < n; ++j) {
      if (f[i][j]) {                            //剪枝作用
        ans.push_back(s.substr(i, j - i + 1));  //做出选择
        backTrace(s, j + 1);
        ans.pop_back();  //撤销选择
      }
    }
  }
};




bool isPalindrome(string& s, int start, int end) {
  while (start < end) {
    if (s[start] != s[end]) {
      return false;
    }
    start++;
    end--;
  }
  return true;
}

// DFS - Deepth First Search
//
//   For example: "aaba"
//
//                     +------+
//              +------| aaba |-----+
//              |      +------+     |
//            +-v-+              +-v--+
//            | a |aba           | aa |ba
//        +---+---+--+           +--+-+
//        |          |              |
//      +-v-+     +--v--+         +-v-+
//      | a |ba   | aba |\0       | b |a
//      +-+-+     +-----+         +-+-+
//        |        a, aba           |
//      +-v-+                     +-v-+
//      | b |a                    | a |\0
//      +-+-+                     +---+
//        |                      aa, b, a
//      +-v-+
//      | a |\0
//      +---+
//    a, a, b, a
//
//   You can see this algorithm still can be optimized, becasue there are some dupliation.
//   (  The optimization you can see the "Palindrome Partitioning II" )
//

void partitionHelper(string& s, int start, vector<string>& output, vector<vector<string>>& result) {
  if (start == s.size()) {
    result.push_back(output);
    return;
  }
  for (int i = start; i < s.size(); i++) {
    if (isPalindrome(s, start, i) == true) {
      // put the current palindrome substring into ouput
      output.push_back(s.substr(start, i - start + 1));
      // Recursively check the rest substring
      partitionHelper(s, i + 1, output, result);
      // take out the current palindrome substring, in order to check longer substring.
      output.pop_back();
    }
  }
}

vector<vector<string>> partition(string s) {
  vector<vector<string>> result;
  vector<string> output;

  partitionHelper(s, 0, output, result);

  return result;
}

void printMatrix(vector<vector<string>>& matrix) {
  for (int i = 0; i < matrix.size(); i++) {
    cout << "{ ";
    for (int j = 0; j < matrix[i].size(); j++) {
      cout << matrix[i][j] << ", ";
    }
    cout << "}" << endl;
  }
  cout << endl;
}

int main(int argc, char** argv) {
  string s("aab");
  if (argc > 1) {
    s = argv[1];
  }

  vector<vector<string>> result = partition(s);

  printMatrix(result);
}
