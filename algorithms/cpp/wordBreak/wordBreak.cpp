// Source : https://oj.leetcode.com/problems/word-break/
// Author : Hao Chen
// Date   : 2014-07-01

/********************************************************************************** 
* 
* Given a string s and a dictionary of words dict, determine if s can be segmented 
* into a space-separated sequence of one or more dictionary words.
* 
* For example, given
* s = "leetcode",
* dict = ["leet", "code"].
* 
* Return true because "leetcode" can be segmented as "leet code".
* 
*               
**********************************************************************************/
//my implm

//设状态为 f(i) ， 表示 s[0,i) 是否可以分词， 则状态转移方程为
// f(i) = any_of(f(j) && s[j,i] in dict), 0 <= j < i。只要满足就true
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        const int n = s.size();
        if(n==0) return true;
        vector<bool> f(n+1,false);
        f[0] = true; /** 空字符串*/
        for(int i = 1; i <= n; ++i) /** 注意<=*/
            for(int j = i-1; j >= 0; --j)
                // if(f[j] && wordDictSet.find(s.substr(j,i-j))!= wordDict.end())
                if(f[j]){
                    //字典中查找
                    int k = 0;
                    for (;k < wordDict.size(); ++k)
                        if(s.substr(j,i-j) == wordDict[k]) //substr(pos,len)
                            break;
                    if (k != wordDict.size()){ //找到了
                        f[i]=true;
                        break;
                    }

                }
        return f[n];
    }
};

#include <iostream>
#include <vector>
#include <set>
using namespace std;

bool wordBreak(string s, set<string> &dict) {

    //using an array to mark subarray from 0 to i can be broken or not
    vector<bool> v(s.size(),false);

    for(int i=0; i<s.size(); i++){
        //check the substring from 0 to i is int dict or not
        string w = s.substr(0,i+1);
        v[i] = (dict.find(w)!=dict.end());

        //if it is, then use greedy algorithm
        if (v[i]) continue;

        //if it is not, then break it to check
        for(int j=0; j<i; j++){
            //if the substring from 0 to j can be borken, then check the substring from j to i
            if (v[j]==true){
                w = s.substr(j+1, i-j);
                v[i] = (dict.find(w)!=dict.end());
                if (v[i]) break;
            }
        }
    }
    return v.size() ? v[v.size()-1] : false;
}


int main()
{
    string s; 
    set<string> dict;

    s = "a";
    dict.insert("a");
    cout << wordBreak(s, dict) << endl;
    
    dict.clear();
    s = "dogs";
    string d[]={"dog","s","gs"};
    dict.insert(d, d+3);
    cout << wordBreak(s, dict) << endl;

    return 0;
}
