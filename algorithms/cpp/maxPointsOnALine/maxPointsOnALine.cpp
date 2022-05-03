// Max Points on a Line
// 暴力枚举， 以点为中心， 时间复杂度O(n^2)， 空间复杂度O(n^2)
// 以每个“点”为中心， 然后遍历剩余点， 找到所有的斜率，如果斜率相同， 那么一定共线.
// 对每个点， 用一个哈希表， key为斜率， value为该直线上的点数，
// 计算出哈希表后， 取最大值， 并更新全局最大值， 最后就是结果。

class Solution {
 public:
  int maxPoints(vector<vector<int>>& points) {
    if (points.size() < 3) return points.size();
    int result = 0;
    unordered_map<double, int> slope_count;
    for (int i = 0; i < points.size() - 1; i++) {
      slope_count.clear();
      int samePointNum = 0;  // 与i重合的点
      int point_max = 1;     // 和i共线的最大点数
      for (int j = i + 1; j < points.size(); j++) {
        double slope;  // 斜率
        if (points[i][0] == points[j][0]) {
          slope = std::numeric_limits<double>::infinity();  //! 无穷大的表示
          if (points[i][1] == points[j][1]) {
            ++samePointNum;
            continue;
          }
        } else {
          if (points[i][1] == points[j][1]) {
            // 0.0 and -0.0 is the same
            slope = 0.0;
          } else {
            slope = 1.0 * (points[i][1] - points[j][1]) / (points[i][0] - points[j][0]);
          }
        }
        int count = 0;
        if (slope_count.find(slope) != slope_count.end())
          count = ++slope_count[slope];
        else {
          count = 2;  // 从2开始
          slope_count[slope] = 2;
        }
        if (point_max < count) point_max = count;
      }
      result = max(result, point_max + samePointNum);
    }
    return result;
  }
};

// clang-format off
// Source : https://oj.leetcode.com/problems/max-points-on-a-line/
// Author : Hao Chen
// Date   : 2014-10-12

/********************************************************************************** 
* 
* Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
*               
**********************************************************************************/

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

// O(n^2) time complexity solution
int maxPoints(vector<Point> &points) {

    #define INT_MAX 2147483647
    #define INT_MIN (-INT_MAX - 1)

    if (points.size()<=0) return 0;
    if (points.size()<=2) return points.size();
    
    int maxnum = 0;
    //using a map to find the same slope line
    map<double, int> slopeMap;

    //The algorithm here is quite straight forward.
    //   take each point in array to caculate with others
    //
    //Actually the algorithm here can be optimized.
    //   there are many duplicated calculation. 
    //   considering two points A and B, (A,B) is same with (B,A), here re-calculated.
    for(int i=0; i<points.size(); i++) {
        //reset teh slope map.
        slopeMap.clear();
        slopeMap[INT_MIN] = 0;
        int samePointCnt = 1;
        for (int j=0; j<points.size(); j++) {
            if (i==j) continue; //skip the same point
            //Caculate the slope of two points
            int delta_x = points[i].x - points[j].x;
            int delta_y = points[i].y - points[j].y;
            //Special case: two points are exactly at same place
            if (delta_y == 0 && delta_x == 0){
                samePointCnt++;
                continue;
            }
            //Special case: delta_x == 0
            double slope = INT_MAX;
            if (delta_x!=0) {
                slope = 1.0*delta_y / delta_x;
            }
            //Count the points is same line.
            slopeMap[slope]++;
        }
        //find the max number of points located at same line with points[i]
        map<double, int>::iterator it;
        for (it = slopeMap.begin(); it != slopeMap.end(); it++) {
            if (maxnum < it->second + samePointCnt) {
                maxnum = it->second + samePointCnt;
            }
        }
    }

    return maxnum;
}

void generatePoints(vector<Point> &points, int n) {
    srand(time(0));
    Point p;
    for(int i=0; i<n; i++) {
        p.x = rand() % 1;
        p.y = rand() % 1;
        points.push_back(p);
    }
}

void printPoints(vector<Point> &points) {
    for(int i=0; i<points.size(); i++) {
        cout << "(" << points[i].x << "," << points[i].y << ") ";
    }
    cout << endl;
}


int main(int argc, char** argv) 
{
    int n = 20;
    if ( argc > 1) {
        n = atoi(argv[1]);
    }
    vector<Point> points;
    generatePoints(points, n);
    printPoints(points);
    cout << maxPoints(points) << endl;
    return 0;
}
