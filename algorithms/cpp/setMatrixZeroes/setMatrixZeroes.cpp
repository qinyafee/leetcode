// Source : https://oj.leetcode.com/problems/set-matrix-zeroes/
// Author : Hao Chen
// Date   : 2014-06-23

/********************************************************************************** 
* 
* Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
* 
* click to show follow up.
* 
* Follow up:
* 
* Did you use extra space?
* A straight forward solution using O(mn) space is probably a bad idea.
* A simple improvement uses O(m + n) space, but still not the best solution.
* Could you devise a constant space solution?
* 
*               
**********************************************************************************/
// my implm
class Solution {
public:
    // 时间复杂度O(m*n)， 空间复杂度O(1)
    void setZeroes(vector<vector<int>>& matrix) {
        const size_t m = matrix.size();
        const size_t n = matrix[0].size();
        bool row_has_zero = false; // 第一行是否存在 0
        bool col_has_zero = false; // 第一列是否存在 0

        for(size_t i = 0; i < n; ++i){
            if(matrix[0][i]==0){
                row_has_zero = true;
                break;
            }
        }

        for(size_t j = 0; j < m; ++j){
            if(matrix[j][0]==0){
                col_has_zero = true;
                break;
            } 
        }

        for(size_t i = 1; i < m; ++i){
            for(size_t j = 1; j < n; ++j){
                if(matrix[i][j]==0){
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for(size_t i = 1; i < m; ++i){
            for(size_t j = 1; j < n; ++j){
                if(matrix[i][0]==0 || matrix[0][j]==0)
                    matrix[i][j] = 0;
            }
        }
        if(row_has_zero)
            for(size_t i = 0; i < n; ++i)
                matrix[0][i] = 0;
        if(col_has_zero)
            for(size_t j = 0; j < m; ++j)
                matrix[j][0] = 0;
    }
};


class Solution {
public:
    Solution(){
        srand(time(NULL));
    }
    void setZeroes(vector<vector<int> > &matrix) {
        if(random()%2){
            setZeroes1(matrix);
        }
        setZeroes2(matrix);
    }
    
    void setZeroes1(vector<vector<int> > &matrix) {
        
        int bRow = false, bCol=false;
        
        for (int r=0; r<matrix.size(); r++){
            for(int c=0; c<matrix[r].size(); c++){
                if (matrix[r][c]==0){
                    if (r==0) bRow = true;
                    if (c==0) bCol = true;
                    matrix[0][c] = matrix[r][0] = 0;
                }
            }
        }
        
        for (int r=1; r<matrix.size(); r++){
            for(int c=1; c<matrix[r].size(); c++){
                if (matrix[0][c]==0 || matrix[r][0]==0) {
                    matrix[r][c]=0;
                }
            }
        }
        if (bRow){
            for(int c=0; c<matrix[0].size(); c++) matrix[0][c] = 0;
        }
        if (bCol){
            for(int r=0; r<matrix.size(); r++) matrix[r][0] = 0;
        }

    }
    
    void setZeroes2(vector<vector<int> > &matrix) {

        bool *row = new bool[matrix.size()]();
        bool *col = new bool[matrix[0].size()]();
        for (int r=0; r<matrix.size(); r++){
            for(int c=0; c<matrix[r].size(); c++){
                if (matrix[r][c]==0){
                    row[r]=true;
                    col[c]=true;
                }
            }
        }
        
        for (int r=0; r<matrix.size(); r++){
            for(int c=0; c<matrix[r].size(); c++){
                if (row[r] || col[c]) {
                    matrix[r][c]=0;
                }
            }
        }
    }
};
