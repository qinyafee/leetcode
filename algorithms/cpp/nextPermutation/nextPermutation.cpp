// Source : https://oj.leetcode.com/problems/next-permutation/
// Author : Hao Chen
// Date   : 2014-08-21

/********************************************************************************** 
* 
* Implement next permutation, which rearranges numbers into the lexicographically next 
* greater permutation of numbers.
* 
* If such arrangement is not possible, it must rearrange it as the lowest possible order 
* (ie, sorted in ascending order).
* 
* The replacement must be in-place, do not allocate extra memory.
* 
* Here are some examples. Inputs are in the left-hand column and its corresponding outputs 
* are in the right-hand column.
*
*   1,2,3 → 1,3,2
*   3,2,1 → 1,2,3
*   1,1,5 → 1,5,1
*               
**********************************************************************************/
//my implm
// https://leetcode-cn.com/problems/next-permutation/solution/xia-yi-ge-pai-lie-suan-fa-xiang-jie-si-lu-tui-dao-/
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        //std::next_permutation(nums.begin(),nums.end()); //stl
        const int n = nums.size();
        if(n < 2) return;
        //step1 从后往前找到第一个【相邻升序对】，即A[i]<A[i+1]。此时A[i+1,end)为降序。
        int i = n-2; //注意index
        for(; i >= 0; --i){
            if(nums[i] < nums[i+1]) break;
        }

        //step2 在区间[i+1,end)中，从后往前找到第一个大于A[i]的元素A[j]
        if(i == -1){ // 特判，无相邻升序对，必定为非递减序列，已经是最大全排列
            std::reverse(nums.begin(), nums.end());
            return;
        }
        int j = n-1;
        for(; j >= i+1; --j){
            if(nums[j] > nums[i]) break;
        }

        //step3 交换A[i]和A[j]，此时A[i+1,end)一定还是降序，因为A[j]是从右侧起第一个大于A[i]的值
        swap(nums[i], nums[j]);
        //step4 反转A[i+1,end)，变成升序
        std::reverse(nums.begin()+i+1, nums.end());
        return;
    }
};

/*
 * Take a look the following continuous permutation, can you find the patern?
 *
 *    1 2 3 4
 *    1 2 4 3
 *    1 3 2 4
 *    1 3 4 2
 *    1 4 2 3
 *    1 4 3 2
 *    2 1 3 4
 *    ...
 *
 * The pattern can be descripted as below:
 *
 *    1) from n-1 to 0, find the first place [i-1] which num[i-1] < num[i]
 *    2) from n-1 to i, find the first number from n-1 to i which >= num[i-1]
 *    3) swap the 2) num with the num[i-1]
 *    4) sort the sub-array [i, n) //actuall sort is fine as well
 * 
 * For example:
 * 
 *     1 4 3 2   <-- 1) find the first place which num[i-1] < num[i]
 *     ^
 * 
 *     1 4 3 2   <-- 2) find the first number from n-1 to i which >= num[i-1]
 *     ^     ^  
 * 
 *     2 4 3 1   <-- 3) swap them
 *     ^     ^
 * 
 *     2 4 3 1   <-- 4) sort
 *       ^   ^
 *
 *     2 1 3 4   
 * 
 * Edge Case:
 *
 *     4 3 2 1, the next permutation is 1 2 3 4
 */

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void nextPermutation(vector<int> &num) {

    if(num.size()<=1) return;

    for(int i=num.size()-1; i>0; i--) {
        if (num[i-1] < num[i]){
            int j = num.size()-1;
            while( num[i-1] >= num[j]) {
                //pass;
                j--;
            }
            int tmp = num[j];
            num[j] = num[i-1];
            num[i-1] = tmp;
            //sort works as well
            //sort(num.begin()+i, num.end()); 
            reverse(num.begin()+i, num.end()); 
            return; 
        }
        //edge case: 4 3 2 1
        if (i == 1 ){
            //sort works as well
            //sort(num.begin(), num.end());
            reverse(num.begin(), num.end());
            return;
        }
    }

}

void printVector(vector<int> &num) {
    for(int i=0; i<num.size(); i++) {
        cout << num[i] << " ";
    } 
    cout <<endl;
}
bool isBeginVector(vector<int> &num) {
    for(int i=0; i<num.size(); i++) {
        if(num[i] != i+1) {
            return false;
        }
    } 
    return true;
}

int main(int argc, char** argv)
{
    int n = 4;
    if (argc>1){
        n = atoi(argv[1]);
    }
    vector<int> num;
    for(int i=1; i<=n; i++){
        num.push_back(i);
    }
    
    while(true){
        printVector(num);
        nextPermutation(num);
        if(isBeginVector(num)){
            break;
        }
    }
    return 0;
}
