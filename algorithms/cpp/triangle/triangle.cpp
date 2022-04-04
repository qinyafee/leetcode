// Source : https://oj.leetcode.com/problems/triangle/
// Author : Hao Chen
// Date   : 2014-06-18

/**********************************************************************************
 *
 * Given a triangle, find the minimum path sum from top to bottom.
 * Each step you may move to adjacent numbers on the row below.
 *
 * For example, given the following triangle
 *
 * [
 *      [2],
 *     [3,4],
 *    [6,5,7],
 *   [4,1,8,3]
 * ]
 *
 * The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
 *
 * Note:
 * Bonus point if you are able to do this using only O(n) extra space, where n is the total number
 *of rows in the triangle.
 *
 *
 **********************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

// 设状态为 f(i, j) ， 表示从从位置 (i,j) 出发， 路径的最小和， 则状态转移方程为
// f(i, j) = min f(i + 1, j), f(i + 1, j + 1) + (i, j)
// 这里考虑从下到上的方式，状态的定义就变成了 “最后一行元素到当前元素的最小路径和”，
// 对于 [0][0]这个元素来说，最后状态表示的就是我们的最终答案。

class Solution {
 public:
  // my impl 1
  // space O(1)
  int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    for (int i = n - 2; i >= 0; --i) {
      for (int j = 0; j <= i; ++j)  // j < i + 1; 注意边界条件易错
        triangle[i][j] = min(triangle[i + 1][j], triangle[i + 1][j + 1]) + triangle[i][j];
    }
    return triangle[0][0];
  }
  // my impl 2
  // space:O(n^2)
  int minimumTotal2(vector<vector<int>>& triangle) {
    const int N = triangle.size();
    vector<vector<int>> dp(N, vector<int>(N, 0));

    // dp.back() = triangle.back();
    for (int i = N - 1; i >= 0; --i) {
      dp[N - 1][i] = triangle[N - 1][i];
    }
    for (int i = N - 2; i >= 0; --i) {
      for (int j = i; j >= 0; --j) {
        dp[i][j] = min(dp[i + 1][j], dp[i + 1][j + 1]) + triangle[i][j];
      }
    }
    return dp[0][0];
  }

  int minimumTotal(vector<vector<int>>& triangle) {
    vector<vector<int>> v;

    for (int i = 0; i < triangle.size(); i++) {
      if (i == 0) {
        v.push_back(triangle[i]);
        continue;
      }

      vector<int> tmp;

      for (int j = 0; j < triangle[i].size(); j++) {
        int x, y, z;
        x = y = z = 0x7fff;
        if ((j - 1) >= 0) {
          x = v[i - 1][j - 1];
        }
        if (j < v[i - 1].size()) {
          y = v[i - 1][j];
        }
        /* won't take the previous adjacent number */
        // if ( (j+1)<v[i-1].size()) {
        //    z = v[i-1][j+1];
        //}
        tmp.push_back(min(x, y, z) + triangle[i][j]);
      }

      v.push_back(tmp);
    }
    int min = 0x7fff;
    if (v.size() > 0) {
      vector<int>& vb = v[v.size() - 1];
      for (int i = 0; i < vb.size(); i++) {
        if (vb[i] < min) {
          min = vb[i];
        }
      }
    }

    return min;
  }

 private:
  inline int min(int x, int y, int z) {
    int n = x < y ? x : y;
    return (n < z ? n : z);
  }
};

int main() {
  vector<vector<int>> v;
  vector<int> i;
  i.push_back(-1);
  v.push_back(i);

  i.clear();
  i.push_back(2);
  i.push_back(3);
  v.push_back(i);

  i.clear();
  i.push_back(1);
  i.push_back(-1);
  i.push_back(-3);
  v.push_back(i);

  Solution s;
  cout << s.minimumTotal(v) << endl;
  ;

  v.clear();
  i.clear();
  i.push_back(-1);
  v.push_back(i);

  i.clear();
  i.push_back(3);
  i.push_back(2);
  v.push_back(i);

  i.clear();
  i.push_back(-3);
  i.push_back(1);
  i.push_back(-1);
  v.push_back(i);
  cout << s.minimumTotal(v) << endl;
  ;

  return 0;
}
