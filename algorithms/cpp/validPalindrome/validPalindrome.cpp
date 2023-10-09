// Source : https://oj.leetcode.com/problems/valid-palindrome/
// Author : Hao Chen
// Date   : 2014-06-26

/**********************************************************************************
 *
 * Given a string, determine if it is a palindrome, considering only alphanumeric characters and
 *ignoring cases.
 *
 * For example,
 * "A man, a plan, a canal: Panama" is a palindrome.
 * "race a car" is not a palindrome.
 *
 * Note:
 * Have you consider that the string might be empty? This is a good question to ask during an
 *interview.
 *
 * For the purpose of this problem, we define empty string as valid palindrome.
 *
 *
 **********************************************************************************/
// my implm
class Solution {
 public:
  // 时间复杂度O(n)， 空间复杂度O(1)【不增加额外存储，best practice】
  bool isPalindrome(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);  //! 字母全转成小写
    auto left = s.begin();
    auto right = std::prev(s.end());  // s最后一个元素
    while (left < right) {
      if (!std::isalnum(*left))
        ++left;
      else if (!std::isalnum(*right))
        --right;
      else if (*left != *right)
        return false;
      else {
        ++left, --right;
      }
    }
    return true;
  }

  // 时间复杂度O(n)， 空间复杂度O(n)
  bool isPalindrome2(string s) {
    vector<char> vec;
    stack<char> stk;
    transform(s.begin(), s.end(), s.begin(), ::tolower);  // 字母全转成小写
    for (char ch : s) {
      if (std::isalnum(ch)) {  // 是否为数字和字符
        vec.push_back(ch);
        stk.push(ch);
      }
    }
    for (char ch : vec) {
      if (stk.top() == ch)
        stk.pop();
      else
        return false;
    }
    return true;
  }
};

class Solution {
 public:
  bool isPalindrome(string s) {
    s = removeNoise(s);
    for (int i = 0; i < s.size() / 2; i++) {
      if (s[i] != s[s.size() - i - 1]) {
        return false;
      }
    }
    return true;
  }

  string removeNoise(string& s) {
    string d;
    for (int i = 0; i < s.size(); i++) {
      if (::isalpha(s[i]) || ::isdigit(s[i])) {
        d.push_back(::tolower(s[i]));
      }
    }
    return d;
  }
};
