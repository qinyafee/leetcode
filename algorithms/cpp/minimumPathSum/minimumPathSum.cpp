// my implm
class Solution {
 public:
  // 二维动规
  // 设状态为 dp[i][j] ， 表示从起点 (0,0) 到达 (i,j) 的最小路径和， 则状态转移方程为：
  // dp[i][j] = min(dp[i-1][j], dp[i][j-1])+grid[i][j]
  // 时间复杂度O(n)， 空间复杂度O(1)。复用原来空间
  int minPathSum(vector<vector<int>>& grid) {
    const int m = grid.size();
    if (m == 0) return 0;
    const int n = grid[0].size();

    for (int i = 1; i < n; ++i) grid[0][i] += grid[0][i - 1];

    for (int i = 1; i < m; ++i) grid[i][0] += grid[i - 1][0];

    for (int i = 1; i < m; ++i)
      for (int j = 1; j < n; ++j) grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);

    return grid[m - 1][n - 1];
  }

  // 时间复杂度O(n)， 空间复杂度O(n)
  int minPathSum2(vector<vector<int>>& grid) {
    const int m = grid.size();
    if (m == 0) return 0;
    const int n = grid[0].size();

    vector<vector<int>> dp(m, vector<int>(n, 0));

    dp[0][0] = grid[0][0];

    for (int i = 1; i < m; ++i) {
      dp[i][0] = dp[i - 1][0] + grid[i][0];  //累加
    }
    for (int j = 1; j < n; ++j) {
      dp[0][j] = dp[0][j - 1] + grid[0][j];  // 累加
    }
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
      }
    }
    return dp[m - 1][n - 1];
  }
};

// clang-format off

// Source : https://oj.leetcode.com/problems/minimum-path-sum/
// Author : Hao Chen
// Date   : 2014-06-21

/***************************************************************************************************** 
 *
 * Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right 
 * which minimizes the sum of all numbers along its path.
 * 
 * Note: You can only move either down or right at any point in time.
 * 
 * Example:
 * 
 * Input:
 * [
 *   [1,3,1],
 *   [1,5,1],
 *   [4,2,1]
 * ]
 * Output: 7
 * Explanation: Because the path 1&rarr;3&rarr;1&rarr;1&rarr;1 minimizes the sum.
 * 
 ******************************************************************************************************/
#include <limits.h>
#include <iostream>
#include <vector>
using namespace std;

int minPathSum(vector<vector<int>>& grid) {
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].size(); j++) {
            if (i==0 && j==0) continue;
            else if (i==0) grid[0][j] += grid[0][j-1];
            else if (j==0) grid[i][0] += grid[i-1][j];
            else grid[i][j] += min( grid[i-1][j], grid[i][j-1]);
        }
    }
    return grid[grid.size()-1][grid[0].size()-1];
}

int main()
{
    int a[6][2]={{7,2},{6,6},{8,6},{8,7},{5,0},{6,0}};
    vector< vector<int> > grid;
    for(int i=0; i<6; i++){
        vector<int> v;
        for(int j=0; j<2; j++){
            v.push_back(a[i][j]);
        }
        grid.push_back(v);
    }

    cout << "minPathSum=" << minPathSum(grid) << endl;

    return 0;
}

