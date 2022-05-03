// my implm
class Solution {
 public:
  // 时间复杂度O(n^2)， 空间复杂度O(1)
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> result;
    if (matrix.empty()) return result;
    int beginX = 0, endX = matrix.size() - 1;
    int beginY = 0, endY = matrix[0].size() - 1;
    while (true) {
      // From left to right
      for (int j = beginY; j <= endY; ++j) result.push_back(matrix[beginX][j]);
      if (++beginX > endX) break;  //去掉上行
      // From top to bottom
      for (int i = beginX; i <= endX; ++i) result.push_back(matrix[i][endY]);
      if (beginY > --endY) break;  //去掉右列
      // From right to left
      for (int j = endY; j >= beginY; --j) result.push_back(matrix[endX][j]);
      if (beginX > --endX) break;  //去掉下行
      // From bottom to top
      for (int i = endX; i >= beginX; --i) result.push_back(matrix[i][beginY]);
      if (++beginY > endY) break;  //去掉左列
    }
    return result;
  }
};

// clang-format off
// Source : https://oj.leetcode.com/problems/spiral-matrix/
// Author : Hao Chen
// Date   : 2014-06-30

/********************************************************************************** 
* 
* Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
* 
* For example,
* Given the following matrix:
* 
* [
*  [ 1, 2, 3 ],
*  [ 4, 5, 6 ],
*  [ 7, 8, 9 ]
* ]
* 
* You should return [1,2,3,6,9,8,7,4,5].
* 
*               
**********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

vector<int> spiralOrder(vector<vector<int> > &matrix) {
    vector <int> v;
    int row = matrix.size();
    if (row<=0) return v;
    int col = matrix[0].size();
    if (col<=0) return v;
    int r, c;
    for (r=0, c=0; r<(row+1)/2 && c<(col+1)/2; r++, c++){
        //top
        for(int i=c; i<col-c; i++){
            v.push_back(matrix[r][i]);
        }
        //right
        for(int i=r+1; i<row-r; i++){
            v.push_back(matrix[i][col-c-1]);
        }
        //bottom
        for(int i=col-c-2; row-r-1>r && i>=c; i--){
            v.push_back(matrix[row-r-1][i]);
        }
        //left
        for(int i=row-r-2; col-c-1>c && i>r; i--){
            v.push_back(matrix[i][c]);
        }
        
    }
    return v;
}


void printArray(vector<int> v)
{
    cout << "[";
    for(int j=0; j<v.size(); j++) {
        printf(" %02d", v[j]);
    }
    cout << "]" << endl;;
}

void printMatrix(vector< vector<int> > &vv)
{
    for(int i=0; i<vv.size(); i++) {
        printArray(vv[i]);
    }
    cout << endl;
}

vector< vector<int> > createMatrix(int n, int m)
{
    vector< vector<int> > vv;
    int cnt = 1;
    for(int i=0; i<n; i++){
        vector<int> v;
        for(int j=0; j<m; j++){
            v.push_back(cnt++);
        }
        vv.push_back(v);
    }
    return vv;
}

int main(int argc, char** argv)
{
    int n=3, m=3;
    if (argc>2){
        n = atoi(argv[1]);
        m = atoi(argv[2]);
    }
    vector< vector<int> > matrix = createMatrix(n, m);
    printMatrix(matrix);
    vector<int> v = spiralOrder(matrix);
    printArray(v);
    return 0;
}
