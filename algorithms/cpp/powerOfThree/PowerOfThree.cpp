//1. 我们可以把该整数对3取对数，如果结果是整数，说明该整数是3的幂。
class Solution {
 public:
  bool isPowerOfThree(int n) {
    if (n <= 0) return false;  // 异常情况

    double dn = static_cast<double>(n);
    double res = log10(dn) / log10(3);
    return (res - static_cast<int>(res) == 0);
  }
};

//2. 不断除以3， 看最后能否得到1。
// https://leetcode-cn.com/problems/power-of-three/solution/3de-mi-by-leetcode-solution-hnap/

class Solution {
 public:
  bool isPowerOfThree(int n) {
    while (n && n % 3 == 0) {
      n /= 3;
    }
    return n == 1;
  }
};

// Source : https://leetcode.com/problems/power-of-three/
// Author : Hao Chen
// Date   : 2016-01-14

/*************************************************************************************** 
 *
 * Given an integer, write a function to determine if it is a power of three.
 * 
 *     Follow up:
 *     Could you do it without using any loop / recursion?
 * 
 * Credits:Special thanks to @dietpepsi for adding this problem and creating all test 
 * cases.
 *               
 ***************************************************************************************/

class Solution {

public:
    
    bool isPowerOfThree(int n) {
        return isPowerOfThree03(n); //140ms
        return isPowerOfThree02(n);//130ms
        return isPowerOfThree01(n); //140ms
        return isPowerOfThree_loop(n);  //136ms
        return isPowerOfThree_recursive(n); //168ms
    }
    
    bool isPowerOfThree03(int n) {
        double logRes = log10(n)/log10(3); 
        return (logRes - int(logRes) == 0);
    }
    bool isPowerOfThree02(int n) {
        return n>0 ? (1162261467%n==0) : false;
    }
    
    void init(unordered_map<int, bool>& power ){
        int p = 1;
        power[1]=true;
        while(1){
            p *= 3;
            power[p] = true;
            if (p > INT_MAX/3) break;
            
        }
    }
    bool isPowerOfThree01(int n) {
        static unordered_map<int, bool> power; 
        if (power.size()==0) init(power);
        return power.find(n) != power.end();
    }
    
    bool isPowerOfThree_loop(int n) {
        for(;n>0;n /= 3){
            if (n==1 || n==3) return true;
            if (n%3 != 0) return false;
        }
        return false;
    }
    
    bool isPowerOfThree_recursive(int n) {
        if ( n == 1 || n == 3) return true;
        if ( n==0 || n%3 != 0 ) return false;
        return isPowerOfThree_recursive(n/3);
    } 
};
