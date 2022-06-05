// 规则定义： 设学生 A 和学生 B 左右相邻，A在 B左边；
// 左规则： 当 ratingsB>ratingsA时，B的糖比 A的糖数量多。
// 右规则： 当 ratingsA>ratingsB时，A的糖比 B的糖数量多。
// 相邻的学生中，评分高的学生必须获得更多的糖果 等价于 所有学生满足左规则且满足右规则。
// 两边扫描即可
// 链接：https://leetcode.cn/problems/candy/solution/candy-cong-zuo-zhi-you-cong-you-zhi-zuo-qu-zui-da-/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
class Solution {
 public:
  int candy(vector<int>& ratings) {
    const int n = ratings.size();
    // if(n == 0) return 0;
    // if(n == 1) return 1;
    vector<int> assign(n);
    // 左扫描
    int inc = 1;  //高分递增起点
    for (int i = 1; i < n; i++) {
      if (ratings[i] > ratings[i - 1]) {
        assign[i] = max(inc++, assign[i]);
      } else {
        inc = 1;
      }
    }
    // 右扫描
    inc = 1;
    for (int i = n - 2; i >= 0; i--) {
      if (ratings[i] > ratings[i + 1]) {
        assign[i] = max(inc++, assign[i]);
      } else {
        inc = 1;
      }
    }
    // 最开始每人至少一颗
    int sum = accumulate(&assign[0], &assign[0] + n, n);
    return sum;
  }
};
int main() {
  // clang-format off
  vector<int> ratings{ 5, 4, 1, 9, 7, 2, 3, 2, 1, 7 };
                    // 0  0  0  1  0  0  1  0  0  1
                    // 2  1  0  2  1  0  2  1  0  1  //10+10
  //vector<int> ratings{};
                    // 0  0  0  1   0  0  1  0  0  1
                    // 2  1  0  2   1  0  2  1  0  1  //10+10
  // clang-format on
  Solution solution;
  cout << solution.candy(ratings) << '\n';
  return 0;
}

// Source : https://oj.leetcode.com/problems/candy/
// Author : Hao Chen
// Date   : 2014-10-12

/**********************************************************************************
 *
 * There are N children standing in a line. Each child is assigned a rating value.
 *
 * You are giving candies to these children subjected to the following requirements:
 *
 * Each child must have at least one candy.
 * Children with a higher rating get more candies than their neighbors.
 *
 * What is the minimum candies you must give?
 *
 *
 **********************************************************************************/

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
using namespace std;

void print(vector<int>& v);

/*
 *    The soluiton is O(2n) run-time complexity
 *
 *    For example:
 *
 *        ratings[] = { 5, 6, 7, 4, 1, 2, 3, 2, 1, 7 }
 *
 *    1) Go through the ratings from left to right.
 *
 *       Find the each increasing sub-array, giving the minimal candy
 *
 *        ratings[] = { 5, 6, 7,   4,   1, 2, 3,   2,   1, 7 }
 *                      ------>    ->   ------>    ->   --->
 *          candy[] = { 1, 2, 3,   1,   1, 2, 3,   1,   1, 2 }
 *
 *    2) Go through the raings from right to left.
 *
 *             ratings[] = { 5,   6,   7, 4, 1,   2,   3, 2, 1,   7 }
 *                           <-   <-   <------    <-   <------    <-
 *          prev_candy[] = { 1,   2,   3, 1, 1,   2,   3, 1, 1,   2 }
 *                                        +1              +1
 *               candy[] = { 1,   2,   3, 2, 1,   2,   3, 2, 1,   2 }
 *
 *    3) total candy is 19
 *
 */
int candy(vector<int>& ratings) {
  vector<int> candyCnt(ratings.size());
  // allocate candies, considering the minimal rating on the left
  candyCnt[0] = 1;
  for (int i = 1; i < ratings.size(); i++) {
    candyCnt[i] = ratings[i] > ratings[i - 1] ? candyCnt[i - 1] + 1 : 1;
  }
  print(candyCnt);
  // modify the allocation, considering the minimal rating on the right
  int totalCandy = candyCnt[ratings.size() - 1];
  for (int i = ratings.size() - 2; i >= 0; i--) {
    candyCnt[i] = (ratings[i] > ratings[i + 1] && candyCnt[i + 1] + 1 > candyCnt[i])
                      ? candyCnt[i + 1] + 1
                      : candyCnt[i];
    // count total candies by the way
    totalCandy += candyCnt[i];
  }
  print(candyCnt);
  return totalCandy;
}

void generateRatings(vector<int>& ratings, int n) {
  srand(time(0));
  for (int i = 0; i < n; i++) {
    ratings.push_back(rand() % 10);
  }
}

void print(vector<int>& v) {
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;
}

int main(int argc, char** argv) {
  int n = 10;
  if (argc > 1) {
    n = atoi(argv[1]);
  }
  vector<int> ratings;
  generateRatings(ratings, n);
  print(ratings);

  cout << candy(ratings) << endl;

  cout << "--------------------" << endl;
  int r[] = {5, 6, 7, 4, 1, 2, 3, 2, 1, 7};
  vector<int> ra(r, r + sizeof(r) / sizeof(r[0]));
  print(ra);
  cout << candy(ra) << endl;
  return 0;
}
