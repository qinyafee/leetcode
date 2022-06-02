#include <unordered_map>
using namespace std;

class Mat {
  Mat(const unordered_map<int, unordered_map<int, int>>& from_,
      const unordered_map<int, unordered_map<int, int>>& to_)
      : from(from_), to(to_) {
  }
  // 用邻近矩阵，给定行+列，O(1)时间复杂度访问元素，但空间复杂度比较高O(n^2)
  // 如果用一个邻接表，给定行+列，O(n)时间复杂度访问元素
  // 用两个邻接表，给定行+列，O(1)时间复杂度访问元素
  unordered_map<int, unordered_map<int, int>> from;   // 按 u->v 存储 weight
  unordered_map<int, unordered_map<int, int>> to;  // 按 v<-u 存储 weight
                                                    // 比用vector更灵活

 public:
  Mat Multiply(const Mat& lh, const Mat& rh) {
    unordered_map<int, unordered_map<int, int>> result_in;
    unordered_map<int, unordered_map<int, int>> result_out;
    for (const auto& row : lh.from) {
      auto r = row.first;
      auto relems = row.second;
      for (const auto& col : rh.to) {
        auto c = col.first;
        auto celems = col.second;
        int tmp = 0;
        for (auto& [c1, re] : relems) { // c++17用法
          if (celems.find(c1) != celems.end()) {//非零
            tmp += re * celems[c1];
          }
        }
        if (tmp != 0) {
          result_in[r].emplace(c, tmp);
          result_out[c].emplace(r, tmp);
        }
      }
    }
    return {result_in, result_out};
  }
};

int main() {
  return 0;
}