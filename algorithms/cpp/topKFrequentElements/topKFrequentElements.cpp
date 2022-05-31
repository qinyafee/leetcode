
// 首先遍历整个数组，并使用哈希表记录每个数字出现的次数，并形成一个「出现次数数组」。
// 找出原数组的前k个高频元素，就相当于找出「出现次数数组」的前 kkk 大的值。
// 链接：https://leetcode.cn/problems/top-k-frequent-elements/solution/qian-k-ge-gao-pin-yuan-su-by-leetcode-solution/

// 类似 215. Kth Largest Element in an Array
// method2 快速排序

// method1 堆排序，维护一个k大小的小根堆，将数组中的每个元素与堆顶元素进行比较
// 如果比堆顶元素大，则删除堆顶元素并添加该元素; 如果比堆顶元素小，则什么也不做。继续下一个元素。
// 时间复杂度 O(nlogk)，空间复杂度 O(k) 。
class Solution {
 public:
  struct cmp {
    bool operator()(const pair<int, int>& lh, const pair<int, int>& rh) {
      return lh.second > rh.second;  // 相当于定义>, 实现小根堆
    }
  };

  vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> counts;
    for (const auto& v : nums) {
      counts[v]++;
    }

    // pair 的第一个元素代表数组的值，第二个元素代表了该值出现的次数
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp)> q;
    for (auto& [num, count] : counts) { // 用法
      if (q.size() == k) {
        if (q.top().second < count) {
          q.pop();
          q.emplace(num, count);
        }
      } else {
        q.emplace(num, count);
      }
    }
    vector<int> ret;
    while (!q.empty()) {
      ret.emplace_back(q.top().first);
      q.pop();
    }
    return ret;
  }
};

// Source : https://leetcode.com/problems/top-k-frequent-elements/
// Author : Calinescu Valentin
// Date   : 2016-05-02

/***************************************************************************************
 *
 * Given a non-empty array of integers, return the k most frequent elements.
 *
 * For example,
 * Given [1,1,1,2,2,3] and k = 2, return [1,2].
 *
 * Note:
 * You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
 * Your algorithm's time complexity must be better than O(n log n), where n is the
 * array's size.
 *
 ***************************************************************************************/

class Solution {
 public:
  struct element  // structure consisting of every distinct number in the vector,
  // along with its frequency
  {
    int number, frequency;
    bool operator<(const element arg) const {
      return frequency < arg.frequency;
    }
  };
  priority_queue<element> sol;  // we use a heap so we have all of the elements sorted
  // by their frequency
  vector<int> solution;

  vector<int> topKFrequent(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int i = 1;
    for (; i < nums.size(); i++) {
      int freq = 1;
      while (i < nums.size() && nums[i] == nums[i - 1]) {
        i++;
        freq++;
      }
      element el;
      el.number = nums[i - 1];
      el.frequency = freq;
      sol.push(el);
    }
    if (i == nums.size())  // if we have 1 distinct element as the last
    {
      element el;
      el.number = nums[nums.size() - 1];
      el.frequency = 1;
      sol.push(el);
    }
    while (k)  // we extract the first k elements from the heap
    {
      solution.push_back(sol.top().number);
      sol.pop();
      k--;
    }
    return solution;
  }
};
