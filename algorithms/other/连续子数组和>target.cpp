
// 给一个数组 array 和一个数字 sum, 求这个数组的连续子数组的元素相加和 >= sum 解的个数。
// 数组元素大小：0 <= array <= 10^9

// 比如:
// array: [56,21,56,35,9], sum = 61
// ans = 9

// [1,2,3,4,5,6,7,8,9,10], sum = 20
// ans = 27

#include <iostream>
#include <vector>
using namespace std;

// 双指针
// time: O(n^2)
int count_the_subarray(std::vector<int>& nums, int target) {
  int sid = 0;
  int eid = 0;
  int cnt = 0;
  int tmp = 0;
  while (eid < nums.size()) {
    tmp += nums[eid];

    while (tmp >= target && sid <= eid) {
      cnt += nums.size() - eid;
      tmp = tmp - nums[sid];
      sid++;
    }
    eid++;
  }
  return cnt;
}

int main() {
  // int a;
  // cin >> a;
  vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  cout << count_the_subarray(nums, 20) << endl;
}
