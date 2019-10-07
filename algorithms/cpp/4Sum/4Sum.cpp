// Source : https://oj.leetcode.com/problems/4sum/
// Author : Hao Chen
// Date   : 2014-07-03

/********************************************************************************** 
* 
* Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? 
* Find all unique quadruplets in the array which gives the sum of target.
* 
* Note:
* 
* Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
* The solution set must not contain duplicate quadruplets.
* 
*     For example, given array S = {1 0 -1 0 -2 2}, and target = 0.
* 
*     A solution set is:
*     (-1,  0, 0, 1)
*     (-2, -1, 1, 2)
*     (-2,  0, 0, 2)
* 
*               
**********************************************************************************/
// my implm
// 使用四个指针(a<b<c<d)。固定最小的a和b在左边，c=b+1,d=N-1 移动两个指针包夹求解。
// 保存使得nums[a]+nums[b]+nums[c]+nums[d]==target的解。偏大时d左移，偏小时c右移。c和d相遇时，表示以当前的a和b为最小值的解已经全部求得。b++,进入下一轮循环b循环。当b循环结束后， a++，进入下一轮a循环。即(a在最外层循环，里面嵌套b循环，再嵌套双指针c,d包夹求解)。
//https://leetcode-cn.com/problems/4sum/solution/shuang-zhi-zhen-jie-fa-can-zhao-san-shu-zhi-he-ge-/

class Solution{
	public: 
    //time: O(n^3)
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        vector<vector<int> > res;
        if(nums.size()<4)
        return res;
        int a,b,c,d,N=nums.size();
        for(a=0;a<=N-4;a++){
        	if(a>0&&nums[a]==nums[a-1]) continue;      //确保nums[a] 改变了
        	for(b=a+1;b<=N-3;b++){
        		if(b>a+1&&nums[b]==nums[b-1])continue;   //确保nums[b] 改变了
        		c=b+1,d=N-1;
        		while(c<d){
        			if(nums[a]+nums[b]+nums[c]+nums[d]<target)
        			    c++;
        			else if(nums[a]+nums[b]+nums[c]+nums[d]>target)
        			    d--;
        			else{
        				res.push_back({nums[a],nums[b],nums[c],nums[d]});
        				while(c<d&&nums[c+1]==nums[c])      //确保nums[c] 改变了
        				    c++;
        				while(c<d&&nums[d-1]==nums[d])      //确保nums[d] 改变了
        				    d--;
        				c++;
        				d--;
					}
				}
			}
		}
		return res;
    }
};


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > threeSum(vector<int> num, int target); 

/*
 * 1) Sort the array,
 * 2) traverse the array, and solve the problem by using "3Sum" soultion.
 */

vector<vector<int> > fourSum(vector<int> &num, int target) {
    vector< vector<int> > result;
    if (num.size() < 4) return result;
    sort( num.begin(), num.end() );

    for(int i = 0; i < num.size() - 3; i++) {
        //skip the duplication
        if (i > 0 && num[i - 1] == num[i]) continue;
        vector<int> n(num.begin()+i+1, num.end());
        vector<vector<int> > ret = threeSum(n, target-num[i]);
        for(int j = 0; j < ret.size(); j++) {
            ret[j].insert(ret[j].begin(), num[i]);
            result.push_back(ret[j]);
        }
    }

    return result; 
}

vector<vector<int> > threeSum(vector<int> num, int target) {

    vector< vector<int> > result;
    //sort the array (if the qrray is sorted already, it won't waste any time)
    sort(num.begin(), num.end());

    int n = num.size();

    for (int i = 0; i < n - 2; i++) {
        //skip the duplication
        if (i > 0 && num[i - 1] == num[i]) continue;
        int a = num[i];
        int low = i + 1;
        int high = n - 1;
        while (low < high) {
            int b = num[low];
            int c = num[high];
            if (a + b + c == target) {
                //got the soultion
                vector<int> v;
                v.push_back(a);
                v.push_back(b);
                v.push_back(c);
                result.push_back(v);
                // Continue search for all triplet combinations summing to zero.
                //skip the duplication
                while(low < n && num[low] == num[low + 1]) low++;
                while(high > 0 && num[high] == num[high - 1]) high--;
                low++;
                high--;
            } else if (a + b + c > target) {
                //skip the duplication
                while(high > 0 && num[high] == num[high - 1]) high--;
                high--;
            } else {
                //skip the duplication
                while(low < n && num[low] == num[low + 1]) low++;
                low++;
            }
        }
    }
    return result;
}


int printMatrix(vector< vector<int> > &vv)
{
    for(int i = 0; i < vv.size(); i++) {
        cout << "[";
        for(int j = 0; j < vv[i].size(); j++) {
            cout << " " << vv[i][j];
        }
        cout << "]" << endl;;
    }
}


int main()
{
    int a[] = { 1, 0, -1, 0, -2, 2 };
    vector<int> n(a, a+6);
    int t = 0;
    vector< vector<int> > v = fourSum(n, t);
    printMatrix(v);

    n.clear();
    int b[] = { -1, -5, -5, -3, 2, 5, 0, 4 };
    n.insert(n.begin(), b, b+8);
    t = -7;
    v = fourSum(n, t);
    printMatrix(v);

    return 0;
}
