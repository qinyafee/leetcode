
// my implm
// 扫描一遍数组，用变量x1保存当前最小的值，变量x2保存当前第二小的值。
// 如果右面能碰到一个数大于x2，说明必然存在一个递增的三元组。
class Solution {
 public:
  // 时间O(n)
  bool increasingTriplet(vector<int>& nums) {
    if (nums.size() < 3) return false;
    int first = nums[0];
    int second = INT_MAX;
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] < first) {
        first = nums[i];
        // 不要急着重置second，只要后面大于old second就行
        // second = INT_MAX;
      } else if (nums[i] > first && nums[i] < second)
        second = nums[i];
      else if (nums[i] > second)
        return true;
    }
    return false;
  }

  //时间O(n^2)，不太好的实现
  bool increasingTriplet2(vector<int>& nums) {
    if (nums.size() < 3) return false;
    int first = nums[0];
    int second = INT_MAX;
    for (int i = 1; i < nums.size() - 1; ++i) {
      if (nums[i] < first) {
        first = nums[i];
        second = INT_MAX;
      } else if (nums[i] > first && nums[i] < second)
        second = nums[i];
      else if (nums[i] > second)
        return true;
      for (int j = i + 1; j < nums.size(); ++j)
        if (nums[j] > second) return true;
    }
    return false;
  }
};

// clang-format off
// Source : https://leetcode.com/problems/increasing-triplet-subsequence/
// Author : Calinescu Valentin, Hao Chen
// Date   : 2016-02-27

/*************************************************************************************** 
 *
 * Given an unsorted array return whether an increasing subsequence of length 3 exists
 * or not in the array.
 * 
 * Formally the function should:
 * Return true if there exists i, j, k 
 * such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.
 * Your algorithm should run in O(n) time complexity and O(1) space complexity.
 * 
 * Examples:
 * Given [1, 2, 3, 4, 5],
 * return true.
 * 
 * Given [5, 4, 3, 2, 1],
 * return false.
 * 
 ***************************************************************************************/
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        bool solution = false;
        if(nums.size())
        {
            int first = nums[0];
            int second = 0x7fffffff; //MAX_INT so we can always find something smaller than it
            for(int i = 1; i < nums.size() && !solution; i++)
            {
                if(nums[i] > second)
                    solution = true;
                else if(nums[i] > first && nums[i] < second)
                    second = nums[i];
                else if(nums[i] < first)
                    first = nums[i];
            }
        }
        return solution;
    }
};


//Hao Chen's implementation
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        if (nums.size() < 3) return false;
        
        int first=INT_MAX, second = INT_MAX;
        
        for(int i=0; i<nums.size(); i++) {
            if ( first > nums[i] ) {
                first = nums[i];
            }else if ( first < nums[i] && nums[i] < second) {
                second = nums[i];
            }else if (nums[i] > second){
                return true;
            }
        }
        return false;
    }
};
