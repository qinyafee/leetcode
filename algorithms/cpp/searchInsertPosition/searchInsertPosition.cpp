// my impl
class Solution {
 public:
  int searchInsert(vector<int>& nums, int target) {
    //用stl
    auto it = std::lower_bound(nums.begin(), nums.end(), target);
    return std::distance(nums.begin(), it);
  }

	// 自己实现的
  template <typename ForwardIterator, typename T>
  ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, T value) {
    while (first != last) {
      auto mid = next(first, distance(first, last) / 2);
      if (value > *mid)
        first = ++mid;
      else
        last = mid;
    }
    return first;
  }

  template <typename ForwardIterator, typename T>
  ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, T value) {
    while (first != last) {
      auto mid = next(first, distance(first, last) / 2);
      if (value >= *mid)
        first = ++mid;  // 与 lower_bound 仅此不同
      else
        last = mid;
    }
    return first;
  }
};

// clang-format off
// Source : https://oj.leetcode.com/problems/search-insert-position/
// Author : Hao Chen
// Date   : 2014-06-22

/********************************************************************************** 
* 
* Given a sorted array and a target value, return the index if the target is found. 
* If not, return the index where it would be if it were inserted in order.
* 
* You may assume no duplicates in the array.
* 
* Here are few examples.
* [1,3,5,6], 5 → 2
* [1,3,5,6], 2 → 1
* [1,3,5,6], 7 → 4
* [1,3,5,6], 0 → 0
* 
*               
**********************************************************************************/

#include <stdio.h>


int binary_search(int A[], int n, int key) {
    int low = 0;
    int high = n-1;
    while (low <= high){
        int mid = low +(high-low)/2;
        if (A[mid] == key){
            return mid;
        }
        if ( key> A[mid] ) {
            low = mid+1;
        }else{
            high = mid-1;
        }
    }
    return low;
}
int searchInsert(int A[], int n, int target) {
    if (n==0) return n;
    return binary_search(A, n, target);
}

int main()
{
    int a[]={1,3,5,6};
    printf("%d -> %d\n", 5, searchInsert(a, 4, 5));
    printf("%d -> %d\n", 2, searchInsert(a, 4, 2));
    printf("%d -> %d\n", 7, searchInsert(a, 4, 7));
    printf("%d -> %d\n", 0, searchInsert(a, 4, 0));
    return 0;
}
