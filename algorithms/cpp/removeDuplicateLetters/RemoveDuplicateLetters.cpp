// https://leetcode.cn/problems/remove-duplicate-letters/solution/qu-chu-zhong-fu-zi-mu-by-leetcode-soluti-vuso/
// 方法一：贪心 + 单调栈

class Solution {
 public:
  string removeDuplicateLetters(string s) {
    vector<bool> vis(26, false);  // 当前元素ch是否在栈中
    vector<int> num(26, 0);       // 每个元素的计数
    for (char ch : s) {
      num[ch - 'a']++;
    }

    string stk;  // 用作stack
    for (char ch : s) {
      // 如果当前字符ch已经在栈里，则ch一定不是单调递增字符串的最后一个字符。
      if (!vis[ch - 'a']) {  // 所以遍历到栈里有的字符ch，可以直接丢弃。
        while (!stk.empty() && stk.back() > ch) {
          if (num[stk.back() - 'a'] > 0) {  // 当前栈顶元素在后面还会出现，pop掉
            vis[stk.back() - 'a'] = 0;
            stk.pop_back();
          } else {  //否则break，保证字典序
            break;
          }
        }
        vis[ch - 'a'] = true;
        stk.push_back(ch);
      }
      num[ch - 'a'] -= 1;  // 每次遍历，ch--，为了查后面是否有ch元素
    }
    return stk;
  }
};

// Source : https://leetcode.com/problems/remove-duplicate-letters/
// Author : Hao Chen
// Date   : 2017-01-02

/***************************************************************************************
 *
 * Given a string which contains only lowercase letters, remove duplicate letters so
 * that every letter appear once and only once. You must make sure your result is the
 * smallest in lexicographical order among all possible results.
 *
 * Example:
 *
 * Given "bcabc"
 * Return "abc"
 *
 * Given "cbacdcbc"
 * Return "acdb"
 *
 * Credits:Special thanks to @dietpepsi for adding this problem and creating all test
 * cases.
 ***************************************************************************************/

class Solution {
 public:
  string removeDuplicateLetters(string s) {
    const int ASCII_LEN = 256;
    int counter[ASCII_LEN] = {0};
    bool visited[ASCII_LEN] = {false};

    for (char ch : s) {
      counter[ch]++;
    }

    string result;
    for (char ch : s) {
      counter[ch]--;
      // if the current `ch` has already put into the result.
      if (visited[ch]) continue;

      // if the current `ch` is smaller than the last one char in result.
      // and we still have duplicated last-one char behind, so we can remove the current one.
      while (!result.empty() && ch < result.back() && counter[result.back()]) {
        visited[result.back()] = false;
        result.pop_back();
      }
      result.push_back(ch);
      visited[ch] = true;
    }
    return result;
  }
};
