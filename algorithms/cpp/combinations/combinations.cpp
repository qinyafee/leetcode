// 链接：https://leetcode.cn/problems/combinations/solution/hui-su-suan-fa-jian-zhi-python-dai-ma-java-dai-ma-/

// version1 其实是dfs
class Solution {
 public:
  vector<vector<int>> results;
  vector<vector<int>> combine(int n, int k) {
    if (k <= 0 || n < k) {
      return results;
    }
    vector<int> path;
    for (int i = 1; i <= n; ++i) {
      backTrace(n, k, i, path);
    }
    return results;
  }

  void backTrace(int n, int k, int sid, vector<int> path) {
    path.push_back(sid);
    if (path.size() == k) {
      results.push_back(path);
      return;  //! 及时返回
    }
    for (int i = sid + 1; i <= n; ++i) {
      backTrace(n, k, i, path);
    }
  }
};

// version2 真正回溯，无剪枝
class Solution {
 public:
  vector<vector<int>> results;
  vector<vector<int>> combine(int n, int k) {
    if (k <= 0 || n < k) {
      return results;
    }
    vector<int> path;
    backTrace(n, k, 1, path);
    return results;
  }

  void backTrace(int n, int k, int sid, vector<int> path) {
    if (path.size() == k) {
      results.push_back(path);
      return;  //! 及时返回
    }
    for (int i = sid; i <= n; ++i) {
      path.push_back(i);  //每次backTrace只添加一个数
                          // 下一轮搜索，设置的搜索起点要加 1，因为组合数不允许出现重复的元素
      backTrace(n, k, i + 1, path);
      // 撤销，重点理解，可以打印出来看看
      path.pop_back();
    }
  }
};

// version2 真正回溯，有剪枝
class Solution {
 public:
  vector<vector<int>> results;
  vector<vector<int>> combine(int n, int k) {
    if (k <= 0 || n < k) {
      return results;
    }
    vector<int> path;
    backTrace(n, k, 1, path);
    return results;
  }

  void backTrace(int n, int k, int sid, vector<int> path) {
    if (path.size() == k) {
      results.push_back(path);
      return;  //! 及时返回
    }
    //! 归纳出来的结束/剪枝条件
    // n = 6 ，k = 4。path.size()=1的时候，接下来要选择3个数，搜索起点最大是 4，
    // 最后一个被选的组合是[4,5,6]；
    for (int i = sid; i <= n - (k - path.size()) + 1; ++i) {
      path.push_back(i);  //每次backTrace只添加一个数
                          // 下一轮搜索，设置的搜索起点要加 1，因为组合数不允许出现重复的元素
      backTrace(n, k, i + 1, path);
      // 撤销
      path.pop_back();
    }
  }
};
// Source : https://oj.leetcode.com/problems/combinations/
// Author : Hao Chen
// Date   : 2014-07-03

/**********************************************************************************
 *
 * Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
 *
 * For example,
 * If n = 4 and k = 2, a solution is:
 *
 * [
 *   [2,4],
 *   [3,4],
 *   [2,3],
 *   [1,2],
 *   [1,3],
 *   [1,4],
 * ]
 *
 *
 **********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void getCombination(int n, int k, vector<int>& solution, vector<vector<int>>& result);
vector<vector<int>> combine1(int n, int k);
vector<vector<int>> combine2(int n, int k);

vector<vector<int>> combine(int n, int k) {
  if (random() % 2) {
    cout << "recusive method!" << endl;
    return combine1(n, k);
  }
  cout << "non-recusive method!" << endl;
  return combine2(n, k);
}

vector<vector<int>> combine1(int n, int k) {
  vector<vector<int>> result;
  vector<int> solution;
  getCombination(n, k, solution, result);
  return result;
}

void getCombination(int n, int k, vector<int>& solution, vector<vector<int>>& result) {
  if (k == 0) {
    // sort to meet LeetCode requirement
    vector<int> v = solution;
    sort(v.begin(), v.end());
    result.push_back(v);
    return;
  }
  for (int i = n; i > 0; i--) {
    solution.push_back(i);
    getCombination(i - 1, k - 1, solution, result);
    solution.pop_back();
  }
}

vector<vector<int>> combine2(int n, int k) {
  vector<vector<int>> result;
  vector<int> d;
  for (int i = 0; i < n; i++) {
    d.push_back((i < k) ? 1 : 0);
  }

  // 1) from the left, find the [1,0] pattern, change it to [0,1]
  // 2) move all of the 1 before the pattern to the most left side
  // 3) check all of 1 move to the right
  while (1) {
    vector<int> v;
    for (int x = 0; x < n; x++) {
      if (d[x]) v.push_back(x + 1);
    }
    result.push_back(v);
    // step 1), find [1,0] pattern
    int i;
    bool found = false;
    int ones = 0;
    for (i = 0; i < n - 1; i++) {
      if (d[i] == 1 && d[i + 1] == 0) {
        d[i] = 0;
        d[i + 1] = 1;
        found = true;
        // step 2) move all of right 1 to the most left side
        for (int j = 0; j < i; j++) {
          d[j] = (ones > 0) ? 1 : 0;
          ones--;
        }
        break;
      }
      if (d[i] == 1) ones++;
    }
    if (!found) {
      break;
    }
  }
  return result;
}

void printResult(vector<vector<int>>& result) {
  for (int i = 0; i < result.size(); i++) {
    cout << "{";
    for (int j = 0; j < result[i].size(); j++) {
      cout << " " << result[i][j];
    }
    cout << " }" << endl;
  }
}

int main(int argc, char** argv) {
  srand(time(NULL));

  int n = 4, k = 2;
  if (argc > 2) {
    n = atoi(argv[1]);
    k = atoi(argv[2]);
  }
  vector<vector<int>> r = combine(n, k);
  printResult(r);
}
