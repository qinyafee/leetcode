// Source : https://oj.leetcode.com/problems/find-minimum-in-rotated-sorted-array/
// Author : Hao Chen
// Date   : 2014-10-20

/********************************************************************************** 
* 
* Suppose a sorted array is rotated at some pivot unknown to you beforehand.
* 
* (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
* 
* Find the minimum element.
* 
* You may assume no duplicate exists in the array.
*               
**********************************************************************************/
// my implm

// 二分查找， 最关键的是要判断那个“断层”是在左边还是右边。
// 若 A[mid] < A[right] ， 则区间 [mid,right] 一定递增， 断层一定在左边
// 若 A[mid] > A[right] ， 则区间 [left,mid] 一定递增， 断层一定在右边
// nums[mid] == nums[right] ， 这种情况不可能发生， 因为数组是严格单调递增的， 不存在重复元素
// https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/solution/er-fen-cha-zhao-wei-shi-yao-zuo-you-bu-dui-cheng-z/
class Solution {
public:
    // 时间复杂度为O(logN)，空间复杂度为O(1)。
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;             /* 左闭右闭区间，如果用右开区间则不方便判断右值 */
        while (left < right) {                   /* 循环不变式，如果left == right，则循环结束 */
            int mid = left + (right - left) / 2; /* 地板除，mid更靠近left */
            if (nums[mid] > nums[right]) {       /* 中值 > 右值，最小值在右半边，收缩左边界 */
                left = mid + 1;                  /* 因为中值 > 右值，中值肯定不是最小值，左边界可以跨过mid */
            }
            else if (nums[mid] < nums[right]){   /* 明确中值 < 右值，最小值在左半边，收缩右边界 */
                right = mid;                     /* 因为中值 < 右值，中值也可能是最小值，右边界只能取到mid处 */
            }
        }
        return nums[left];    /* 循环结束，left == right，最小值输出nums[left]或nums[right]均可 */
    }
};

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
using namespace std;

/* 
 *  Obveriously, to search any sorted array, the binary search is the common sense.
 * 
 *  To solve this problem, the idea is same as the search in rotated sorted array.
 */
int findMin(vector<int> &num) {

    int low=0, high=num.size()-1;

    while(high-low>1){
        int mid = low + (high-low)/2;
        // Chek the array if it is non-rotated, then just return the first element.
        if (num[low] < num[mid] && num[mid] < num[high]){
            return num[low];
        }

        // The array is rotated
        // Split it into two part, the minimal value must be the rotated part
        
        // if the left part is rotated, warch the left part
        if (num[low] > num [mid]){
            high = mid;
            continue;
        }
        // if the right part is rotated, search the right part.
        if (num[mid] > num[high]){
            low = mid;
            continue;
        }
    }
    // the array only has 1 element
    if (high == low) return num[low];

    // the array has 2 elements
    return num[low] < num[high] ? num[low] : num[high];

}


void rotate_array(int a[], int n, int pos){
    int i, from=0;
    pos = pos % n;
    if (n<=0) return;

    int tmp = a[0];

    for(int i=0, step=0; step<n && i<pos; step++){
        int to;
        if (from-pos < 0) {
            to = n-pos+from; 
        }else{
            to = from-pos;
        }
        int t ;
        t = a[to];
        a[to] = tmp; 
        tmp = t;
        from = to;
        if ( to == i ){
            i++;
            from++;
            tmp = a[from];
        }
    }

}

void printArray(int A[], int n) {
    printf("{");
    for(int i=0; i<n; i++) {
        printf("%d, ", A[i]);
    }
    printf("}\n");
}

int main(int argc, char** argv)
{

    int cnt=20;

    if (argc>1) {
        cnt = atoi(argv[1]);
    }

    srand(time(NULL)); 

    int expectedMin, actualMin;
    int *a = new int[cnt];
    for(int n=0; n<=cnt; n++) {
        printf("--------------------------------------\n");
        for(int i=0; i<cnt; i++){
            a[i]=i;
        }
        expectedMin = a[0];
        //printArray(a, cnt);
        int rotate_pos = random() % cnt;
        //rotate_pos=2;
        printf("rotate=%d\n", rotate_pos);
        rotate_array(a, cnt, rotate_pos);
        printArray(a, cnt);

        vector<int> num(a, a+cnt);
        actualMin = findMin(num);
        cout << "findMin = " << actualMin << "   " << (expectedMin==actualMin ? "passed" : "failed") << endl;

    }
    delete[] a;

    return 0;
}
