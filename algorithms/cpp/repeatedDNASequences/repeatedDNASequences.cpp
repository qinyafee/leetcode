// https://leetcode.cn/problems/repeated-dna-sequences/solution/zhong-fu-de-dnaxu-lie-by-leetcode-soluti-z8zn/
// method1, 哈希表 + 滑动窗口
// 时间复杂度：O(NL)，L=10；空间复杂度：O(NL)
class Solution {
  const int L = 10;

 public:
  vector<string> findRepeatedDnaSequences(string s) {
    vector<string> ans;
    unordered_map<string, int> cnt;
    const int n = s.size();
    for (int i = 0; i <= n - L; ++i) {
      string sub = s.substr(i, L);
      if (++cnt[sub] == 2) {  //只要达到2，就记录
        ans.push_back(sub);
      }
    }
    return ans;
  }
};

// method2, 哈希表 + 滑动窗口 + 位运算
// A, C, G, T, 分别映射到2bit；
// 长度10的字符串， 可以映射为 20 bits, 小于32位， 用一个int代替，空间复杂降低。
// 时间复杂度通过 位运算 降低，见解析。
//  时间复杂度：O(N)，L=10；空间复杂度：O(N)
class Solution {
  const int L = 10;
  unordered_map<char, int> bin = {{'A', 0}, {'C', 1}, {'G', 2}, {'T', 3}};

 public:
  vector<string> findRepeatedDnaSequences(string s) {
    vector<string> ans;
    int n = s.length();
    if (n <= L) {
      return ans;
    }
    int x = 0;
    for (int i = 0; i < L - 1; ++i) {
      x = (x << 2) | bin[s[i]];
    }
    unordered_map<int, int> cnt;
    for (int i = 0; i <= n - L; ++i) {
      x = ((x << 2) | bin[s[i + L - 1]]) & ((1 << (L * 2)) - 1);
      if (++cnt[x] == 2) {
        ans.push_back(s.substr(i, L));
      }
    }
    return ans;
  }
};

// Source : https://oj.leetcode.com/problems/repeated-dna-sequences/
// Author : Hao Chen
// Date   : 2015-02-09

/**********************************************************************************
 *
 * All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T,
 *
 * For example: "ACGAATTCCG".
 * When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.
 *
 * Write a function to find all the 10-letter-long sequences (substrings) that
 * occur more than once in a DNA molecule.
 *
 * For example,
 *
 * Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",
 *
 * Return:
 * ["AAAAACCCCC", "CCCCCAAAAA"].
 *
 *
 **********************************************************************************/
#include <stdlib.h>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

const int MAX_LEN = 10;

int ACGT2Int(char ch) {
  switch (ch) {
    case 'A':
      return 0;
    case 'C':
      return 1;
    case 'G':
      return 2;
    case 'T':
      return 3;
  }
  return -1;
}
int DNASeqs2Int(string& s, int begin) {
  int result = 0;
  for (int i = 0; i < MAX_LEN; i++) {
    result = result * 4 + ACGT2Int(s[i + begin]);
  }
  return result;
}

vector<string> findRepeatedDnaSequences_01(string s) {
  unordered_map<int, int> stat;

  vector<string> result;

  for (int i = 0; i + MAX_LEN <= s.size(); i++) {
    int hash_code = DNASeqs2Int(s, i);
    stat[hash_code]++;
    if (stat[hash_code] == 2) {
      result.push_back(s.substr(i, MAX_LEN));
    }
  }

  return result;
}

vector<string> findRepeatedDnaSequences_02(string s) {
  unordered_map<size_t, int> stat;
  hash<string> hash_func;

  vector<string> result;

  for (int i = 0; i + MAX_LEN <= s.size(); i++) {
    string word = s.substr(i, MAX_LEN);
    size_t hash_code = hash_func(word);
    stat[hash_code]++;
    if (stat[hash_code] == 2) {
      result.push_back(word);
    }
  }

  return result;
}

vector<string> findRepeatedDnaSequences(string s) {
  srand(time(0));
  if (random() % 2) {
    return findRepeatedDnaSequences_01(s);
  }
  return findRepeatedDnaSequences_02(s);
}

void printVector(vector<string> v) {
  cout << "[ ";
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << (i < v.size() - 1 ? ", " : "");
  }
  cout << " ]" << endl;
}

int main(int argc, char** argv) {
  string s = "GAGAGAGAGAGAG";
  if (argc > 1) {
    s = argv[1];
  }
  printVector(findRepeatedDnaSequences(s));
}
