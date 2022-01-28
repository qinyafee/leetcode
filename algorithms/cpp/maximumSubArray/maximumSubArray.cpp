// Source : https://oj.leetcode.com/problems/maximum-subarray/
// Author : Hao Chen
// Date   : 2014-06-20

/********************************************************************************** 
* 
* Find the contiguous subarray within an array (containing at least one number) 
* which has the largest sum.
* 
* For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
* the contiguous subarray [4,−1,2,1] has the largest sum = 6.
* 
* More practice:
* 
* If you have figured out the O(n) solution, try coding another solution using 
* the divide and conquer approach, which is more subtle.
* 
*               
**********************************************************************************/

// my impl
class Solution {
public:
    //设状态为 f[i]， 表示以 a[i] 结尾的最大连续子序列和

    // 时间复杂度O(n)， 空间复杂度O(1)
    int maxSubArray(vector<int>& nums) {
        const int N = nums.size();
        if(N==0) return 0;
        int localmax = nums[0];
        int globalmax = nums[0];

        for(int i = 1; i < N; ++i){
            localmax = max(localmax, 0) + nums[i];
            globalmax = max(globalmax, localmax);
        }
        return globalmax;
    }

    // 时间复杂度O(n)， 空间复杂度O(n)
    int maxSubArray2(vector<int>& nums) {
        const int N = nums.size();
        if(N==0) return 0;
        vector<int> f(N,0);
        f[0]=nums[0]; //此处易错，不能是f[0]=0；
        int res = f[0];
        for(int i = 1; i < N; ++i){
            f[i] = max(f[i-1], 0) + nums[i];
            res = max(res, f[i]);
        }
        return res;
    }
};

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INT_MIN     (-2147483647 - 1)

int maxSubArray1(int A[], int n);
int maxSubArray2(int A[], int n); 

int max(int x, int y){
    return x>y?x:y;
}

int maxSubArray(int A[], int n) {
    if (random()%2){
        return maxSubArray1(A, n);
    }
    return maxSubArray2(A, n);
}

int maxSubArray1(int A[], int n) {
    int *sum = new int[n];
    sum[0] = A[0];
    int m = A[0]; 
    for (int i=1; i<n; i++){
        sum[i] = max(A[i], A[i] + sum[i-1]);
        m = max(m, sum[i]);
    }
    delete[] sum;
    return m;
}

int maxSubArray2(int A[], int n) {
    int m=INT_MIN;
    int sum=0;
    for (int i=0; i<n; i++){
        sum += A[i];
        m = max(sum, m);
        if (sum<0){
            sum = 0;
        }
    }
    return m;
}

int main()
{
    srand(time(NULL));
    int a[]= {-2,1,-3,4,-1,2,1,-5,4};
    printf("%d\n", maxSubArray(a, sizeof(a)/sizeof(int)));
    printf("%d\n", maxSubArray(a, sizeof(a)/sizeof(int)));
    return 0;
}
