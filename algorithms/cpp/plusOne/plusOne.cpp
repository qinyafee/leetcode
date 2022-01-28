// Source : https://oj.leetcode.com/problems/plus-one/
// Author : Hao Chen
// Date   : 2014-06-21

/********************************************************************************** 
* 
* Given a non-negative number represented as an array of digits, plus one to the number.
* 
* The digits are stored such that the most significant digit is at the head of the list.
*               
**********************************************************************************/
// my implm
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        const int n = digits.size();
        vector<int> res;
        int carry = 1;
        for(int i = n-1; i >= 0; --i){
            digits[i] += carry;
            // res.push_back(digits[i] % 10);//wrong
            res.insert(v.begin(), digits[i]%10);
            carry = digits[i] / 10;;
        }
        if(carry > 0)  res.insert(res.begin(), carry);
        return res;
    }
};


#include <iostream>
#include <vector>
using namespace std;

vector<int> plusOne(vector<int> &digits) {
    int carry=1;
    vector <int> v;
    while(digits.size()>0){
        int x = digits.back();
        digits.pop_back();
        x = x + carry;
        v.insert(v.begin(), x%10);
        carry = x/10;
    }
    if (carry>0){
        v.insert(v.begin(), carry);
    }
    return v;

}

void printVector(vector<int>& v)
{
    cout << "{ ";
    for(int i=0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << "} " << endl;
}


int main()
{
    int a[]={9,9,9};
    vector<int> d(&a[0], &a[0]+sizeof(a)/sizeof(int));
    vector<int> v = plusOne(d);
    printVector(v);
    return 0;
}
