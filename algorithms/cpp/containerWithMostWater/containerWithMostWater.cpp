// Container With Most Water， 【和42. Trapping Rain Water不一样：这个用单调栈，不限于取两个板】
// 双指针，限定取两个板子
// 每个容器的面积， 取决于最短的木板。
// 时间复杂度O(n)， 空间复杂度O(1)
class Solution {
 public:
  int maxArea(vector<int>& height) {
    int left = 0;
    int right = height.size() - 1;
    int result = INT_MIN;
    while (left < right) {
      int area = min(height[right], height[left]) * (right - left);
      result = max(result, area);

      // height[left] < height[right] ? left++ : right-- ;
      if (height[left] <= height[right]) {  //! 这个左指针对应的数不会作为容器的边界了
        left++;
      } else {
        right--;
      }
    }
    return result;
  }
};
// 分析：https://leetcode-cn.com/problems/container-with-most-water/solution/sheng-zui-duo-shui-de-rong-qi-by-leetcode-solution/

// clang-format off
// Source : https://oj.leetcode.com/problems/container-with-most-water/
// Author : Hao Chen
// Date   : 2014-06-22

/********************************************************************************** 
* 
* Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). 
* n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). 
* 
* Find two lines, which together with x-axis forms a container, such that the container contains the most water.
* 
* Note: You may not slant the container.
* 
*               
**********************************************************************************/

class Solution {
public:
    int maxArea(vector<int> &height) {

        int maxArea = 0;
        // two pointers scan from two sides to middle
        int left = 0; 
        int right = height.size()-1;

        int area; 
        while ( left < right ){
            // calculate the area
            area = (right - left) * ( height[left] < height[right] ? height[left] : height[right]);
            // tracking the maxium area
            maxArea = area > maxArea ? area : maxArea;
            // because the area is decided by the shorter edge
            // so we increase the area is to increase the shorter edge
            //
            //     height[left] < height[right] ? left++ : right-- ;
            //
            // However, the above code could cause the unnecessary `area` cacluation
            // We can do some improvement as below:
            if (height[left] < height[right]) {
                do {
                    left++;
                } while (left < right && height[left-1] >= height[left]);
            } else {
                do {
                    right--;
                } while (right > left && height[right+1] >= height[right]);
            }
        }
        
        return maxArea;
    }
};
