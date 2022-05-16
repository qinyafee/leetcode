// 假设子串里含有重复字符，则父串一定含有重复字符，单个子问题就可以决定父问题，因此可以用贪心法。
// 动规里，单个子问题只能影响父问题，不足以决定父问题。
// 从左往右扫描，当遇到重复字母时，以上一个重复字母的 index+1，作为新的搜索起始位置， 直到最后一
// 个字母，如图所示[algorithm-essential]。
// 复杂度是 O(n)
class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> lookup;  // char<->index
    int global = 0;
    int local = 0;
    for (int i = 0; i < s.size(); ++i) {
      auto it = lookup.find(s[i]);
      if (it == lookup.end()) {
        ++local;
        lookup.emplace(s[i], i);
      } else {
        i = it->second;  // 找到重复的index，从index+1开始
        local = 0;
        lookup.clear(); //! 可以继续优化
      }
      global = max(global, local);
    }
    return global;
  }
};

// clang-format off
// Source : https://oj.leetcode.com/problems/longest-substring-without-repeating-characters/
// Author : Hao Chen
// Date   : 2014-07-19

/********************************************************************************** 
* 
* Given a string, find the length of the longest substring without repeating characters. 
* For example, the longest substring without repeating letters for "abcabcbb" is "abc", 
* which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
*               
**********************************************************************************/

#include <string.h>
#include <iostream>
#include <string>
#include <map>
using namespace std;
/*
 * Idea:
 * 
 * Using a map store each char's index.
 * 
 * So, we can be easy to know the when duplication and the previous duplicated char's index.
 * 
 * Then we can take out the previous duplicated char, and keep tracking the maxiumn length. 
 * 
 */
int lengthOfLongestSubstring1(string s) {
    map<char, int> m;
    int maxLen = 0;
    int lastRepeatPos = -1;
    for(int i=0; i<s.size(); i++){
        if (m.find(s[i])!=m.end() && lastRepeatPos < m[s[i]]) {
            lastRepeatPos = m[s[i]];
        }
        if ( i - lastRepeatPos > maxLen ){
            maxLen = i - lastRepeatPos;
        }
        m[s[i]] = i;
    }
    return maxLen;
}
//don't use <map>
int lengthOfLongestSubstring(string s) {
    const int MAX_CHARS = 256;
    int m[MAX_CHARS];
    memset(m, -1, sizeof(m));

    int maxLen = 0;
    int lastRepeatPos = -1;
    for(int i=0; i<s.size(); i++){
        if (m[s[i]]!=-1 && lastRepeatPos < m[s[i]]) {
            lastRepeatPos = m[s[i]];
        }
        if ( i - lastRepeatPos > maxLen ){
            maxLen = i - lastRepeatPos;
        }
        m[s[i]] = i;
    }
    return maxLen;
}

int main(int argc, char** argv)
{
    string s = "abcabcbb";
    cout << s << " : " << lengthOfLongestSubstring(s) << endl;

    s = "bbbbb";
    cout << s << " : " << lengthOfLongestSubstring(s) << endl;

    s = "bbabcdb";
    cout << s << " : " << lengthOfLongestSubstring(s) << endl;

    if (argc>1){
        s = argv[1];
        cout << s << " : " << lengthOfLongestSubstring(s) << endl;
    }

    return 0;
}
