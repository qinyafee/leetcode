// Source : https://oj.leetcode.com/problems/palindrome-number/
// Author : Hao Chen
// Date   : 2014-06-18

/********************************************************************************** 
* 
* Determine whether an integer is a palindrome. Do this without extra space.
* 
* 
* Some hints:
* 
* Could negative integers be palindromes? (ie, -1)
* 
* If you are thinking of converting the integer to string, note the restriction of using extra space.
* 
* You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", 
* you know that the reversed integer might overflow. How would you handle such case?
* 
* There is a more generic way of solving this problem.
* 
*               
**********************************************************************************/
// my implm
// 错误想法：将整数反转，然后与原来的整数比较，是否相等，相等则为Palindrome的。可是reverse()会溢出。
// 正确解法：不断地取第一位和最后一位（10进制下）进行比较，相等则取第二位和倒数第二位，直到
// 完成比较或者中途找到了不一致的位。
class Solution {
public:
    // 时间复杂度O(1)， 空间复杂度O(1)
    bool isPalindrome(int x) {
        if(x<0) return false;
        int d = 1; //divisor
        while(x/d >= 10) d *= 10; //d，找到最高位数目
        while(x > 0){
            int q = x/d; // quotient，商，最高位的数值
            int r = x%10; // remainder, 余数，最低位的数值
            if(q != r) return false;
            x = x%d; //余数，[第二位，最后一位]
            x /= 10; //商数，[第二位，倒数第二位]
            d /= 100;//每此循环消去两位
        }
        return true;
    }
};

#include <stdio.h>

class Solution {
public:

    bool isPalindrome(int x) {    
        return isPalindrome1(x);
        return isPalindrome2(x);
    }

    bool isPalindrome1(int x) {
        if (x<0) {
            return false;
        }
        
        int len=1;
        for (len=1; (x/len) >= 10; len*=10 );
        
        while (x != 0 ) {
            int left = x / len;
            int right = x % 10;
            
            if(left!=right){
                return false;
            }
            
            x = (x%len) / 10;
            len /= 100;
        }
        return true;
    }
    
    bool isPalindrome2(int x) {
        return (x>=0 && x == reverse(x));
    }

private:    
    int reverse(int x) {
        int y=0;

        int n;
        while( x!=0 ){
            n = x%10;
            //check if y is overflowed or not. 
            //if it is, then it's not palindrome
            if ( y > INT_MAX/10 - n) return x-1;
            y = y*10 + n;
            x /= 10;
        }
        return y;
    }
};



int main()
{
    Solution s;
    printf("%d is %d\n", 0, s.isPalindrome(0) );
    printf("%d is %d\n", -101, s.isPalindrome(-101) );
    printf("%d is %d\n", 1001, s.isPalindrome(1001) );
    printf("%d is %d\n", 1234321, s.isPalindrome(1234321) );
    printf("%d is %d\n", 2147447412, s.isPalindrome(2147447412) );
    printf("%d is %d\n", 2142, s.isPalindrome(2142) );
}
