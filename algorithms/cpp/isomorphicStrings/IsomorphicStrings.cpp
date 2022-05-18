// Source : https://leetcode.com/problems/isomorphic-strings/
// Author : Hao Chen
// Date   : 2015-06-09

/**********************************************************************************
 *
 * Given two strings s and t, determine if they are isomorphic.
 *
 * Two strings are isomorphic if the characters in s can be replaced to get t.
 *
 * All occurrences of a character must be replaced with another character while preserving
 * the order of characters. No two characters may map to the same character but a character
 *  may map to itself.
 *
 * For example,
 *
 *     Given "egg", "add", return true.
 *
 *     Given "foo", "bar", return false.
 *
 *     Given "paper", "title", return true.
 *
 * Note:
 * You may assume both s and t have the same length.
 *
 **********************************************************************************/

// my implm
// 用两个HashMap维护字符的映射关系
// https://leetcode.cn/problems/isomorphic-strings/solution/tong-gou-zi-fu-chuan-by-leetcode-solutio-s6fd/
// 时间复杂度 O(n) ， 空间复杂度 O(n) 。
class Solution {
 public:
  bool isIsomorphic(string s, string t) {
    unordered_map<char, char> s2t;
    unordered_map<char, char> t2s;
    const int len = s.size();
    for (int i = 0; i < len; ++i) {
      char x = s[i], y = t[i];
      if ((s2t.count(x) && s2t[x] != y) || (t2s.count(y) && t2s[y] != x)) {
        return false;
      }
      s2t[x] = y;
      t2s[y] = x;
    }
    return true;
  }
};

// version2
class Solution {
 public:
  bool isIsomorphic(string s, string t) {
    if (s.size() != t.size()) {
      return false;
    }

    const int MAXCHAR = 256;
    char maps[MAXCHAR] = {0}, mapt[MAXCHAR] = {0};
    // memset(maps, 0, sizeof(maps));
    // memset(mapt, 0, sizeof(mapt));

    for (int i = 0; i < s.size(); i++) {
      if (maps[s[i]] == 0 && mapt[t[i]] == 0) { // char隐式转换成int
        maps[s[i]] = t[i];
        mapt[t[i]] = s[i];
        // continue;
      }
      if (maps[s[i]] == t[i] && mapt[t[i]] == s[i]) {
        continue;
      } else {
        return false;
      }
    }
    return true;
  }
};
