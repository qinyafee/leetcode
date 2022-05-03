// Insert Interval

// https://leetcode-cn.com/problems/insert-interval/solution/cha-ru-qu-jian-by-leetcode-solution/
class Solution {
 public:
  vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    int left = newInterval[0];
    int right = newInterval[1];
    bool placed = false;
    vector<vector<int>> ans;
    for (const auto& interval : intervals) {
      if (interval[0] > right) {
        // 在插入区间的右侧且无交集
        if (!placed) {
          ans.push_back({left, right});
          placed = true;
        }
        ans.push_back(interval);
      } else if (interval[1] < left) {
        // 在插入区间的左侧且无交集
        ans.push_back(interval);
      } else {
        // 与插入区间有交集，计算它们的并集
        left = min(left, interval[0]);
        right = max(right, interval[1]);
      }
    }
    if (!placed) {
      ans.push_back({left, right});
    }
    return ans;
  }
};

// 这个实现超时
// 时间复杂度O(n)， 空间复杂度O(1)
class Solution {
 public:
  vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    int left = newInterval.front();
    int right = newInterval.back();
    vector<vector<int>>::iterator it = intervals.begin();
    while (it != intervals.end()) {
      if (right < it->front()) {  // 当前区间 在插入区间的右侧且无交集
        intervals.insert(it, {left, right});
        return intervals;
      } else if (left > it->back()) {  // 当前区间 在插入区间的左侧且无交集
        ++it;
        continue;
      } else {  // 与插入区间有交集，计算它们的并集
        left = min(left, it->front());
        right = max(right, it->back());
        it = intervals.erase(it);  // 合并+删除，此处耗时严重
      }
    }
    intervals.insert(intervals.end(), {left, right});
    return intervals;
  }
};

// clang-format off
// Source : https://oj.leetcode.com/problems/insert-interval/
// Author : Hao Chen
// Date   : 2014-08-26

/********************************************************************************** 
* 
* Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
* 
* You may assume that the intervals were initially sorted according to their start times.
* 
* Example 1:
* Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
* 
* Example 2:
* Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].
* 
* This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
* 
*               
**********************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

//Two factors sorting [start:end]
bool compare(const Interval& lhs, const Interval& rhs){
    return (lhs.start==rhs.start) ? lhs.end < rhs.end : lhs.start < rhs.start;
}

vector<Interval> merge(vector<Interval> &intervals) {

    vector<Interval> result;

    if (intervals.size() <= 0) return result;
    //sort the inervals. Note: using the customized comparing function.
    sort(intervals.begin(), intervals.end(), compare);
    for(int i=0; i<intervals.size(); i++) {
        int size = result.size();
        // if the current intervals[i] is overlapped with previous interval.
        // merge them together
        if( size>0 && result[size-1].end >= intervals[i].start) {
            result[size-1].end = max(result[size-1].end, intervals[i].end);
        }else{
            result.push_back(intervals[i]);
        }
    }

    return result;
}

//just reuse the solution of "Merge Intervals", quite straight forward
vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {

    intervals.push_back(newInterval);

    return merge(intervals);
}

int main(int argc, char**argv)
{
    Interval i1(1,2);
    Interval i2(3,5);
    Interval i3(6,7);
    Interval i4(8,10);
    Interval i5(12,16);
    vector<Interval> intervals;
    intervals.push_back(i1);
    intervals.push_back(i2);
    intervals.push_back(i3);
    intervals.push_back(i4);
    intervals.push_back(i5);

    Interval n(4,9);
    vector<Interval> r = insert(intervals, n);

    for(int i=0; i<r.size(); i++){
        cout << "[ " << r[i].start << ", " << r[i].end << " ] ";
    }
    cout <<endl;

    return 0;
}
