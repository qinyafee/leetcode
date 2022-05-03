// Source : https://leetcode.com/problems/find-all-anagrams-in-a-string/
// Author : Manu Gond
// Date   : 2019-10-06

/*****************************************************************************************************
* Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

* Strings consists of lowercase English letters only and the length of both strings s and p will not
be larger than 20,100.

* The order of output does not matter.

* Example 1:

* Input:
   s: "cbaebabacd" p: "abc"

* Output:
  [0, 6]

* Explanation:
  The substring with start index = 0 is "cba", which is an anagram of "abc".
  The substring with start index = 6 is "bac", which is an anagram of "abc".
*Example 2:

* Input:
   s: "abab" p: "ab"

* Output:
   [0, 1, 2]

* Explanation:
* The substring with start index = 0 is "ab", which is an anagram of "ab".
* The substring with start index = 1 is "ba", which is an anagram of "ab".
* The substring with start index = 2 is "ab", which is an anagram of "ab".
 ******************************************************************************************************/
// my implm
// 计数排序 + 滑动窗口
// time: O(n)
class Solution {
 public:
  vector<int> findAnagrams(string s, string p) {
    vector<int> result;
    vector<int> v1(26);
    if (s.size() < p.size()) {
      return result;
    }
    for (int i = 0; i < p.size(); i++) {  // pattern
      v1[p[i] - 'a']++;                   // ascii码: 'a' = 97, 'A'=65
    }
    vector<int> v2(26);
    for (int index = 0; index < s.size(); index++) {
      if (index < p.size()) {  // 滑窗不满
        v2[s[index] - 'a']++;
      } else {
        v2[s[index - p.size()] - 'a']--;  //滑出老元素
        v2[s[index] - 'a']++;             //滑入新元素
      }
      if (v1 == v2) {  // 直接比较两个vector； 此处可以继续优化
        result.push_back(index - p.size() + 1);  //! 起始index
      }
    }
    return result;
  }
};

class Solution {
 public:
  //计数排序+暴力匹配
  // time: O(m*n)
  vector<int> findAnagrams(string s, string p) {
    vector<int> result;
    vector<int> v1(26);
    if (s.size() < p.size()) {
      return result;
    }
    for (int i = 0; i < p.size(); i++) {  // pattern
      v1[p[i] - 'a']++;                   // 'a' = 97
    }
    for (int i = 0; i <= (s.size() - p.size()); i++) {  //! <=
      vector<int> v2(26);
      for (int index = i; index < (i + p.size()); index++) {
        v2[s[index] - 'a']++;
      }
      if (v1 == v2) {  // 直接比较两个vector
        result.push_back(i);
      }
    }
    return result;
  }
};
