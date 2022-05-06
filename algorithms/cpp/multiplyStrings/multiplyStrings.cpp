// 由于 num1和num2的乘积的长度为 m+n或者 m+n-1，因此创建长度为m+n的数组用于存储乘积。
// 对于任意 0≤i<m和 0≤j<n，num1[i]×num2[j] 的结果位于 ansArr[i+j+1]
// 如果 ansArr[i+j+1]≥10，则将进位部分加到 ansArr[i+j]。
// https://leetcode-cn.com/problems/multiply-strings/solution/zi-fu-chuan-xiang-cheng-by-leetcode-solution/

// 时间复杂度：O(mn)，空间复杂度：O(m+n)
class Solution {
 public:
  string multiply(string num1, string num2) {
    if (num1 == "0" || num2 == "0") {
      return "0";
    }
    const int m = num1.size();
		const int n = num2.size();
    auto ansArr = vector<int>(m + n, 0);
    for (int i = m - 1; i >= 0; i--) {
      int x = num1.at(i) - '0';
      for (int j = n - 1; j >= 0; j--) {
        int y = num2.at(j) - '0';
        ansArr[i + j + 1] += x * y;  // 存储位置
      }
    }
    for (int k = m + n - 1; k > 0; k--) {  //!
      ansArr[k - 1] += ansArr[k] / 10; // 进位
      ansArr[k] %= 10;
    }
    int index = ansArr[0] == 0 ? 1 : 0;  // 找到首位index
    string ans;
    while (index < m + n) {
      ans.push_back(static_cast<char>(ansArr[index]));  // 转成char
      index++;
    }
    for (auto& c : ans) {
      c += '0';  // 转成对应的char
    }
    return ans;
  }
};

// clang-format off
// Source : https://oj.leetcode.com/problems/multiply-strings/
// Author : Hao Chen
// Date   : 2014-07-18

/********************************************************************************** 
* 
* Given two numbers represented as strings, return multiplication of the numbers as a string.
* 
* Note: The numbers can be arbitrarily large and are non-negative.
*               
**********************************************************************************/

#include <iostream>
#include <string>
using namespace std;

string multiply(string& num, char ch){
    int n = ch - '0';
    string s;
    int carry = 0;
    int x;
    for(int i=num.size()-1; i>=0; i--){
        x = (num[i]-'0') * n + carry;
        carry = x/10;
        s.insert(s.begin(), x%10+'0'); 
    }
    if (carry>0) {
        s.insert(s.begin(), carry+'0');
    }
    return s;
}

string strPlus(string& num1, string& num2) {
    string s;
    int carry=0;
    int x;
    int n1 = num1.size(); 
    int n2 = num2.size(); 
    
    int i, j;
    for(i=n1-1, j=n2-1; i>=0 || j>=0; i--, j--){
        int x1 = i>=0 ?  num1[i]-'0' : 0;
        int x2 = j>=0 ?  num2[j]-'0' : 0;
        x = x1 + x2 + carry; 
        carry = x/10;
        s.insert(s.begin(), x%10+'0');
    }
    if (carry>0) {
        s.insert(s.begin(), carry+'0');
    }
    return s;
}

string multiply(string num1, string num2) {

    if (num1.size()<=0 || num2.size()<=0) return "";

    int shift=0;
    string result="0";
    for (int i=num1.size()-1; i>=0; i--) {
        string s = multiply(num2, num1[i]);        
        for(int j=0; j<shift; j++){
            s.insert(s.end(), '0');
        }
        result = strPlus(result, s);
        shift++;
    }
    //check if it is zero
    if (result[0]=='0') return "0";
    return result;
}


/********************************************************************************** 
 *                            Another implementation
 **********************************************************************************/

class Solution {
    public:

        string strPlus(string& num1, string& num2) {
            if (num1.size()==0) return num2;
            if (num2.size()==0) return num1;

            if ( num1.size() < num2.size() ) {
                swap(num1, num2);
            }

            string s;
            int carry=0;
            int x;
            for (int i=num1.size()-1, j=num2.size()-1; i>=0; i--, j--) {
                x = num1[i]-'0' + carry;
                if(j>=0){
                    x += num2[j]-'0';
                }
                s.insert(s.begin(), x%10+'0');
                carry = x/10;
            }
            if (carry>0) {
                s.insert(s.begin(), carry+'0');
            }

            return s;
        }


        string multiply(string num1, string num2) {

            if (num1.size()<=0 || num2.size()<=0) return "";

            string result;
            for ( int i=num1.size()-1; i>=0; i--) {
                int carry = 0;
                string val;
                for( int j=num2.size()-1; j>=0; j--) {
                    int v = (num2[j]-'0') * (num1[i]-'0') + carry;
                    val.insert(val.begin(), v%10+'0');
                    carry = v/10;
                }
                if (carry) val.insert(val.begin(), carry+'0');
                for (unsigned int j=i; j<num1.size()-1; j++) {
                    val.push_back('0');
                }
                result = strPlus(result, val);
            }

            //check if it is zero
            if (result[0]=='0') return "0";
            return result;

        }
};



int main(int argc, char**argv)
{
    string s1="20";
    string s2="25";
    if (argc>2){
        s1 = argv[1];
        s2 = argv[2];
    }
    cout << s1 << " * " << s2 << " = " << multiply(s1, s2) << endl;
    return 0;
}
