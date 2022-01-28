// Source : https://oj.leetcode.com/problems/majority-element/
// Author : Hao Chen
// Date   : 2014-12-25

/********************************************************************************** 
 * 
 * Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.
 * 
 * You may assume that the array is non-empty and the majority element always exist in the array.
 * 
 * Credits:Special thanks to @ts for adding this problem and creating all test cases.
 *               
 **********************************************************************************/

// my implm
// 哈希表，哈希表来快速统计每个元素出现的次数，复杂度也是o(n).
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> mp; //<元素，个数>
        int i = 0;
        for(; i < nums.size(); ++i){
            ++mp[nums[i]];
            if(mp[nums[i]] > nums.size()/2)
                break;
        }
        return nums[i];
    }
};

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Moore Voting Algorithm
// Refer to: 
// http://www.cs.utexas.edu/~moore/best-ideas/mjrty/index.html
int majorityElement(vector<int> &num) {
    int majority;
    int cnt = 0;
    for(int i=0; i<num.size(); i++){
        if ( cnt ==0 ){
            majority = num[i];
            cnt++;
        }else{
            majority == num[i] ? cnt++ : cnt --;
            if (cnt > num.size()/2) return majority;
        }
    }
    return majority;

}


vector<int> &split(const string &s, char delim, vector<int> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(atoi(item.c_str()));
    }
    return elems;
}


vector<int> split(const string &s, char delim) {
    vector<int> elems;
    split(s, delim, elems);
    return elems;
}


int main(int argc, char** argv)
{
    //string array = "1,2,1,2,1,2,1,2,1,2,1";
    string array = "2,2,1,1,1";
    if (argc > 1){
        array = argv[1];
    }

    cout << "[" << array << "]" << endl;
    vector<int> num = split(array, ',');
    cout << majorityElement(num) <<endl;

    return 0;
}
