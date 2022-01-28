498. 对角线遍历
给定一个含有 M x N 个元素的矩阵（M 行，N 列），请以对角线遍历的顺序返回这个矩阵中的所有元素，对角线遍历如下图所示。

示例:

输入:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]

输出:  [1,2,4,7,5,3,6,8,9]

//https://leetcode-cn.com/problems/diagonal-traverse/solution/dui-jiao-xian-bian-li-fen-xi-ti-mu-zhao-zhun-gui-l/

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int m = matrix.size();
        if(m == 0) return res;
        int n = matrix[0].size();
        if(n == 0) return res;
        
        int i = 0;
        while(i <= m+n-2){
            // 第 1 3 5 ... 趟
            int x1 = i < m ? i : m-1; // 确定 x y 的初始值
            int y1 = i - x1;
            while(x1 >= 0 && y1 < n){
                res.push_back(matrix[x1][y1]);
                --x1;
                ++y1;
            }
            ++i;

            // 第 2 4 6 ... 趟
            int y2 = i < n ? i : n-1;
            int x2 = i - y2;
            while(y2 >= 0 && x2 < m){
                res.push_back(matrix[x2][y2]);
                ++x2;
                --y2;
            }
            ++i;
        }
        return res;
    }
};

依行科技
输入n, m（正整数） 分别表示矩阵的行数， 和 列数
输出如下形式的矩阵：

0	2	3	9	10
1	4	8	11	16
5	7	12	15	17
6	13	14	18	19