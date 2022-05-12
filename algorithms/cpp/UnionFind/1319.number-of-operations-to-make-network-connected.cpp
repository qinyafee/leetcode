// https://leetcode.cn/problems/number-of-operations-to-make-network-connected/solution/lian-tong-wang-luo-de-cao-zuo-ci-shu-by-leetcode-s/
// 我们可以使用并查集来得到图中的连通分量数。
// 并查集本身就是用来维护连通性的数据结构。
// 如果其包含 n 个节点，那么初始时连通分量数为n;
// 每成功进行一次合并操作，连通分量数就会减少1。
// 最后要保证只有1个联通分量

// 并查集模板
class UnionFind {
 public:
  vector<int> parent;
  vector<int> size;
  int n;
  // 当前连通分量数目
  int setCount;

 public:
  UnionFind(int _n) : n(_n), setCount(_n), parent(_n), size(_n, 1) {
    std::iota(parent.begin(), parent.end(), 0); //! 用法
  }

  int findset(int x) {
    return parent[x] == x ? x : parent[x] = findset(parent[x]);
  }

  bool unite(int x, int y) {
    x = findset(x);
    y = findset(y);
    if (x == y) {
      return false;
    }
    if (size[x] < size[y]) {  //保证短的挂到长的
      swap(x, y);
    }
    parent[y] = x;
    size[x] += size[y];
    --setCount; // 每次merge，联通分量-1
    return true;
  }

  bool connected(int x, int y) {
    x = findset(x);
    y = findset(y);
    return x == y;
  }
};

class Solution {
 public:
  int makeConnected(int n, vector<vector<int>>& connections) {
    if (connections.size() < n - 1) {
      return -1;
    }

    UnionFind uf(n);
    for (const auto& conn : connections) {
      uf.unite(conn[0], conn[1]);
    }

    return uf.setCount - 1;
  }
};
