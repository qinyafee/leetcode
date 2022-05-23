// Source : https://leetcode.com/problems/valid-anagram/
// Author : Hao Chen
// Date   : 2015-08-16

/**********************************************************************************
 *
 * Given two strings s and t, write a function to determine if t is an anagram of s.
 *
 * For example,
 * s = "anagram", t = "nagaram", return true.
 * s = "rat", t = "car", return false.
 *
 * Note:
 * You may assume the string contains only lowercase alphabets.
 *
 **********************************************************************************/
// mehod1
// 为 s 和 t 分别建立一个HashMap， 统计每个字母出现的次数， 比较两个HashMap是否相等。
// 时间复杂度 O(n) ， 空间复杂度 O(n)

// method2
// 因为只包含小写的字母，意味着只有从 a-z 的26个字母，
// 于是我们可以为 s 和 t 开一个长度为26的整数数组来代替哈希表
// 此时额外空间为固定长度的两个数组，为 O(1)
class Solution {
 public:
  bool isAnagram(string s, string t) {
    if (s.length() != t.length()) {
      return false;
    }
    vector<int> table(26, 0);
    for (auto& ch : s) {
      table[ch - 'a']++;
    }
    for (auto& ch : t) {
      table[ch - 'a']--;
      if (table[ch - 'a'] < 0) {
        return false;
      }
    }
    return true;
  }
};

class Solution {
 public:
  // stupid way - but easy to understand  - 76ms
  bool isAnagram01(string s, string t) {
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s == t;
  }

  // using a map to count every chars in the string.
  bool isAnagram02(string s, string t) {
    int map[26] = {0};  // only lowercase alphabets
    // memset(map, 0, sizeof(map));

    // count each char for s
    for (int i = 0; i < s.size(); i++) {
      map[s[i] - 'a']++;
    }
    // decrease the count for t
    for (int i = 0; i < t.size(); i++) {
      map[t[i] - 'a']--;
    }

    // if all alphabets is zero, then they are anagram
    for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
      if (map[i] != 0) return false;
    }
    return true;
  }

  bool isAnagram(string s, string t) {
    return isAnagram02(s, t);  // 12ms
    return isAnagram01(s, t);  // 76ms
  }
};
