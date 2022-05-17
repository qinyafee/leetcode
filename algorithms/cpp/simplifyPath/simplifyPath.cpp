// https://leetcode.cn/problems/simplify-path/solution/jian-hua-lu-jing-by-leetcode-solution-aucq/
// https://leetcode.cn/problems/simplify-path/solution/gong-shui-san-xie-jian-dan-zi-fu-chuan-m-w7xi/
// 先根据'/' split path，存成items，
// 每次以 item 为单位进行处理（有效的文件名），分情况讨论：
// item为有效值 ：存入栈中；
// item为 .. ：弹出栈顶元素（若存在）；
// item为 . ：不作处理。

class Solution {
 public:
  string simplifyPath(string path) {
    vector<string> names = split(path, '/');
    vector<string> stack;  // vector当做栈，因为最后要从头遍历
    for (string& name : names) {
      if (name == "..") {
        if (!stack.empty()) {
          stack.pop_back();
        }
      } else if (!name.empty() && name != ".") {  //! 不为空的判断
        stack.push_back(move(name));
      }
    }
    string ans;
    if (stack.empty()) {
      ans = "/";
    } else {
      for (string& name : stack) {  //从头遍历
        ans += "/" + move(name);
      }
    }
    return ans;
  }

  vector<string> split(const string& s, char delim) {
    vector<string> ans;
    string cur;
    for (char ch : s) {
      if (ch == delim) {
        ans.push_back(move(cur));  //可能有空string
        cur.clear();
      } else {
        cur += ch;
      }
    }
    ans.push_back(move(cur));
    return ans;
  }
};

// Source : https://oj.leetcode.com/problems/simplify-path/
// Author : Hao Chen
// Date   : 2014-10-09

/**********************************************************************************
 *
 * Given an absolute path for a file (Unix-style), simplify it.
 *
 * For example,
 * path = "/home/", => "/home"
 * path = "/a/./b/../../c/", => "/c"
 *
 *
 * Corner Cases:
 *
 * Did you consider the case where path = "/../"?
 * In this case, you should return "/".
 * Another corner case is the path might contain multiple slashes '/' together, such as
 *"/home//foo/". In this case, you should ignore redundant slashes and return "/home/foo".
 *
 *
 **********************************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<string>& split(const string& s, char delim, vector<string>& elems) {
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

vector<string> split(const string& s, char delim) {
  vector<string> elems;
  split(s, delim, elems);
  return elems;
}

string simplifyPath(string path) {
  string result;
  vector<string> elems = split(path, '/');

  int ignor = 0;
  for (int i = elems.size() - 1; i >= 0; i--) {
    if (elems[i] == "" || elems[i] == ".") {
      continue;
    }
    if (elems[i] == "..") {
      ignor++;
      continue;
    }
    if (ignor > 0) {
      ignor--;
      continue;
    }
    if (result.size() == 0) {
      result = "/" + elems[i];
    } else {
      result = "/" + elems[i] + result;
    }
  }

  return result.size() ? result : "/";
}

int main(int argc, char** argv) {
  string path("/a/./b/../../c/");
  if (argc > 1) {
    path = argv[1];
  }

  cout << path << " : " << simplifyPath(path) << endl;
}
