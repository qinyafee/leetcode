
// https://leetcode.cn/problems/valid-sudoku/solution/you-xiao-de-shu-du-by-leetcode-solution-50m6/

// 可以使用哈希表记录每一行、每一列和每一个小九宫格中，每个数字出现的次数。
// 只需要遍历数独一次，在遍历的过程中更新哈希表中的计数，并判断是否满足有效的数独的条件即可。

class Solution {
 public:
  bool isValidSudoku(vector<vector<char>>& board) {
    int rows[9][9];  // 每个数字在每一行出现次数
    int columns[9][9];
    int subboxes[3][3][9];  // subbox，3行3列

    memset(rows, 0, sizeof(rows));
    memset(columns, 0, sizeof(columns));
    memset(subboxes, 0, sizeof(subboxes));
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        char c = board[i][j];
        if (c != '.') {
          int index = c - '0' - 1; // 下标-1
          rows[i][index]++;
          columns[j][index]++;
          subboxes[i / 3][j / 3][index]++;  // 找到subbox
          if (rows[i][index] > 1 || columns[j][index] > 1 || subboxes[i / 3][j / 3][index] > 1) {
            return false;
          }
        }
      }
    }
    return true;
  }
};

// clang-format off
// Source : https://oj.leetcode.com/problems/valid-sudoku/
// Author : Hao Chen
// Date   : 2014-07-17

/********************************************************************************** 
* 
* Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.
* 
* The Sudoku board could be partially filled, where empty cells are filled with the character '.'.
* 
* A partially filled sudoku which is valid.
* 
* Note:
* > A valid Sudoku board (partially filled) is not necessarily solvable. 
*   Only the filled cells need to be validated.
* 
*               
**********************************************************************************/

class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
        const int cnt = 9;
        bool row_mask[cnt][cnt] = {false};
        bool col_mask[cnt][cnt] = {false};
        bool area_mask[cnt][cnt] = {false};
        //check each rows and cols
        for(int r=0; r<board.size(); r++){
            for (int c=0; c<board[r].size(); c++){
                if (!isdigit(board[r][c])) continue;
                int idx =  board[r][c] - '0' - 1;
                
                //check the rows
                if (row_mask[r][idx] == true){
                    return false;
                }
                row_mask[r][idx] = true;
                
                //check the cols
                if (col_mask[c][idx] == true) {
                    return false;
                }
                col_mask[c][idx] = true;
                
                //check the areas
                int area = (r/3) * 3 + (c/3);
                if (area_mask[area][idx] == true) {
                    return false;
                }
                area_mask[area][idx] = true;
            }
        }
        
        return true;
    }
};
