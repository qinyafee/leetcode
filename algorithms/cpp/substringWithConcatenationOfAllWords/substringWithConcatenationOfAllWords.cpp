// 滑动窗口！我们一直在 s 维护着所有单词长度总和的一个长度队列！
// https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/solution/chuan-lian-suo-you-dan-ci-de-zi-chuan-by-powcai/
class Solution {
 public:
  vector<int> findSubstring(string s, vector<string>& words) {
    //特殊情况直接排除
    if (s.empty() || words.empty()) return {};

    //存放结果的数组
    vector<int> result;

    //单词数组中的单词的大小，个数，以及总长度
    int one_word = words[0].size();
    int word_num = words.size();
    int all_len = one_word * word_num;

    //建立单词->单词个数的映射
    unordered_map<string, int> m1;
    for (const auto& w : words) {
      m1[w]++;
    }

    for (int i = 0; i < one_word; ++i) {
      // left和rigth表示窗口的左右边界，count用来统计匹配的单词个数
      int left = i, right = i, count = 0;

      unordered_map<string, int> m2;

      //开始滑动窗口
      while (right + one_word <= s.size()) {
        //从s中提取一个单词拷贝到w
        string w = s.substr(right, one_word);
        right += one_word;  //窗口右边界右移一个单词的长度

        if (m1.count(w) == 0) {  //此单词不在words中，表示匹配不成功,
          count = 0;             //然后重置单词个数、窗口边界、以及m2
          left = right;
          m2.clear();
        } else {  //该单词匹配成功，添加到m2中
          m2[w]++;
          count++;
          while (m2.at(w) > m1.at(w))  //! 一个单词匹配多次，需要缩小窗口，也就是left右移
          {
            string t_w = s.substr(left, one_word);
            count--;
            m2[t_w]--;
            left += one_word;
          }
          if (count == word_num) result.push_back(left);
        }
      }
    }
    return result;
  }
};

// clang-format off
// Source : https://oj.leetcode.com/problems/substring-with-concatenation-of-all-words/
// Author : Hao Chen
// Date   : 2014-08-24

/********************************************************************************** 
* 
* You are given a string, S, and a list of words, L, that are all of the same length. 
* Find all starting indices of substring(s) in S that is a concatenation of each word 
* in L exactly once and without any intervening characters.
* 
* For example, given:
* S: "barfoothefoobarman"
* L: ["foo", "bar"]
* 
* You should return the indices: [0,9].
* (order does not matter).
* 
*               
**********************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

vector<int> findSubstring(string S, vector<string> &L) {

    vector<int> result;
    if ( S.size()<=0 || L.size() <=0 ){
        return result;
    }
    
    int n = S.size(), m = L.size(), l = L[0].size();

    //put all of words into a map    
    map<string, int> expected;
    for(int i=0; i<m; i++){
        if (expected.find(L[i])!=expected.end()){
            expected[L[i]]++;
        }else{
            expected[L[i]]=1;
        }
    }

    for (int i=0; i<l; i++){
        map<string, int> actual;
        int count = 0; //total count
        int winLeft = i;
        for (int j=i; j<=n-l; j+=l){
            string word = S.substr(j, l);
            //if not found, then restart from j+1;
            if (expected.find(word) == expected.end() ) {
                actual.clear();
                count=0;
                winLeft = j + l;
                continue;
            }
            count++;
            //count the number of "word"
            if (actual.find(word) == actual.end() ) {
                actual[word] = 1;
            }else{
                actual[word]++;
            }
            // If there is more appearance of "word" than expected
            if (actual[word] > expected[word]){
                string tmp;
                do {
                    tmp = S.substr( winLeft, l );
                    count--;
                    actual[tmp]--;
                    winLeft += l; 
                } while(tmp!=word);
            }

            // if total count equals L's size, find one result
            if ( count == m ){
                result.push_back(winLeft);
                string tmp = S.substr( winLeft, l );
                actual[tmp]--;
                winLeft += l;
                count--;
            }
            
        }
    }

    return result;
}


int main(int argc, char**argv)
{
    string s = "barfoobarfoothefoobarman";
    vector<string> l;
    l.push_back("foo");
    l.push_back("bar");
    l.push_back("foo");
    
    vector<int> indics = findSubstring(s, l);
    
    for(int i=0; i<indics.size(); i++){
        cout << indics[i] << " ";
    }
    cout << endl;

    return 0;
}
