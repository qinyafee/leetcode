// Source : https://oj.leetcode.com/problems/pascals-triangle-ii/
// Author : Hao Chen
// Date   : 2014-06-18

/********************************************************************************** 
* 
* Given an index k, return the kth row of the Pascal's triangle.
* 
* For example, given k = 3,
* Return [1,3,3,1].
* 
* Note:
* Could you optimize your algorithm to use only O(k) extra space?
* 
*               
**********************************************************************************/
// my implm
// 杨辉三角，是二项式系数在三角形中的一种几何排列。
// 时间复杂度：O(row^2)，空间复杂度：O(1)。不考虑返回值的空间占用。
// https://leetcode-cn.com/problems/pascals-triangle-ii/solution/yang-hui-san-jiao-ii-by-leetcode-solutio-shuk/
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> row(rowIndex+1, 0); //注意+1
        row[0]=1;

        for (int i=0; i<rowIndex; i++) //左到右
            for(int j=i+1; j>0; j--)
                row[j] += row[j-1];
        return row;
    }
};

#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

vector<int> getRow(int rowIndex) {
    vector<int> v(rowIndex+1, 0);
    v[0]=1;

    for (int i=0; i<rowIndex; i++){
        for(int j=i+1; j>0; j--){
           v[j] += v[j-1];
        } 
    }
    return v;
    
}

void printVector( vector<int>  pt)
{
    cout << "{ ";
    for(int j=0; j<pt.size(); j++){
        cout << pt[j] << ", ";
    }
    cout << "} " << endl;
}

int main(int argc, char** argv)
{
    int n = 3;
    if (argc>1) {  
        n = atoi(argv[1]);
    }
    printVector(getRow(n)); 
}
