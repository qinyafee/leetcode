// Source : https://oj.leetcode.com/problems/unique-paths/
// Author : Hao Chen
// Date   : 2014-06-25

/**********************************************************************************
 *
 * A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
 *
 * The robot can only move either down or right at any point in time. The robot is trying to reach
 * the bottom-right corner of the grid (marked 'Finish' in the diagram below).
 *
 *
 *    start                                                  
 *    +---------+----+----+----+----+----+
 *    |----|    |    |    |    |    |    |
 *    |----|    |    |    |    |    |    |
 *    +----------------------------------+
 *    |    |    |    |    |    |    |    |
 *    |    |    |    |    |    |    |    |
 *    +----------------------------------+
 *    |    |    |    |    |    |    |----|
 *    |    |    |    |    |    |    |----|
 *    +----+----+----+----+----+---------+
 *                                   finish
 *
 *
 * How many possible unique paths are there?
 *
 * Above is a 3 x 7 grid. How many possible unique paths are there?
 *
 * Note: m and n will be at most 100.
 *
 **********************************************************************************/

#ifdef CSTYLE

#include <stdio.h>
#include <stdlib.h>

void printMatrix(int* a, int m, int n) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%4d ", a[i * n + j]);
    }
    printf("\n");
  }
  printf("\n");
}

/*
 * Dynamic Programming
 *
 * We have a dp[i][j] represents  how many paths from [0][0] to hear. So, we have the following DP
 * formuler:
 *
 *    dp[i][j] =  1  if i==0 || j==0        //the first row/column only have 1 uniqe path.
 *             =  dp[i-1][j] + dp[i][j-1]   //the path can be from my top cell and left cell.
 */

// using C style array
int uniquePaths(int m, int n) {
  int* matrix = new int[m * n];
  printMatrix(matrix, m, n);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (i == 0 || j == 0) {
        matrix[i * n + j] = 1;
      } else {
        matrix[i * n + j] = matrix[(i - 1) * n + j] + matrix[i * n + j - 1];
      }
    }
  }
  printMatrix(matrix, m, n);
  int u = matrix[m * n - 1];
  delete[] matrix;
  return u;
}

#else

#include <vector>
using namespace std;

// my impl
// 设状态为 f[i][j] ， 表示从起点 (0,0) 到达 (i,j) 的路线条数，
// 则状态转移方程为：f[i][j]=f[i-1][j]+f[i][j-1]
// using C++ STL vector , the code is much easy to read

// 时间复杂度O(n^2)， 空间复杂度O(n^2)
int uniquePaths(int m, int n) {
  vector<vector<int>> dp(n, vector<int>(m, 1));
  for (int row = 1; row < n; row++) {
    for (int col = 1; col < m; col++) {
      dp[row][col] = dp[row - 1][col] + dp[row][col - 1];
    }
  }
  return dp[n - 1][m - 1];
}

// 动规， 滚动数组
// 时间复杂度O(n^2)， 空间复杂度O(n)
int uniquePaths(int m, int n) {
  vector<int> f(n, 0);
  f[0] = 1;
  for (int i = 0; i < m; i++) {
    for (int j = 1; j < n; j++) {
      // 左边的f[j]， 表示更新后的f[j]， 与公式中的f[i][j]对应
      // 右边的f[j]， 表示老的f[j]， 与公式中的f[i-1][j]对应
      f[j] = f[j] + f[j - 1];
    }
  }
  return f[n - 1];
}

#endif

int main(int argc, char** argv) {
  int m = 3, n = 7;
  if (argc > 2) {
    m = atoi(argv[1]);
    n = atoi(argv[2]);
  }

  printf("uniquePaths=%d\n", uniquePaths(m, n));
  return 0;
}
