// clang-format off
// 1135. 最低成本联通所有城市
// 想象一下你是个城市基建规划者，地图上有 N 座城市，它们按以 1 到 N 的次序编号。

// 给你一些可连接的选项 conections，其中每个选项 conections[i] = [city1, city2, cost] 表示将城市 city1 和城市 city2 连接所要的成本。（连接是双向的，也就是说城市 city1 和城市 city2 相连也同样意味着城市 city2 和城市 city1 相连）。

// 返回使得每对城市间都存在将它们连接在一起的连通路径（可能长度为 1 的）最小成本。
// 该最小成本应该是所用全部连接代价的综合。如果根据已知条件无法完成该项任务，则请你返回 -1。
// 示例 1：
// 输入：N = 3, conections = [[1,2,5],[1,3,6],[2,3,1]]
// 输出：6
// 解释：
// 选出任意 2 条边都可以连接所有城市，我们从中选取成本最小的 2 条。

// 示例 2：
// 输入：N = 4, conections = [[1,2,3],[3,4,4]]
// 输出：-1
// 解释： 
// 即使连通所有的边，也无法连接所有城市。
// clang-format on

// 0.并查集, Disjoint
// Set，即不相交集合。是一种树型的数据结构，用于处理一些不相交集合的合并及查询问题。
// 并查集的思想是用一个数组表示了整片森林（parent），树的根节点唯一标识了一个集合，我们只要找到了某个元素的的树根，就能确定它在哪个集合里。
// https://www.runoob.com/data-structures/union-find-quick-merge.html
class UnionFind  // 并查集，主要作用是检查两个顶点是不是在同一个连通分量[集合]
{
  vector<int> parent;  // parent[i]表示当前元素i指向的父节点
  int count;

 public:
  UnionFind(int n) : count(n) {
    parent.resize(n);
    // 初始化, 每一个parent[i]指向自己, 表示每一个元素自己自成一个集合
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  // 查找元素 a 所对应的集合编号，不断去查询自己的父亲节点, 直到到达根节点，
  // O(h) 复杂度, h 为树的高度。
  int find(int a) {
    // assert( p >= 0 && p < count );
    while (a != parent[a]) {  //根节点的特点 parent[a] == a
      a = parent[a];
    }
    return a;
  }

  // 查看元素p和元素q是否所属一个集合
  // O(h)复杂度, h为树的高度
  bool isConnected(int p, int pq) {
    return find(p) == find(pq);
  }

  // 合并元素 p 和元素 pq 所属的集合
  // 分别查询两个元素的根节点，使其中一个根节点指向另外一个根节点，两个集合就合并了。
  // O(h) 时间复杂度，h 为树的高度。
  void merge(int a, int b) {
    int pa = find(a);
    int pb = find(b);
    if (pa == pb) {//!
      return;
    }
    parent[pa] = pb;
  }
};

// https://blog.csdn.net/qq_21201267/article/details/107796632
// https://blog.csdn.net/weixin_40137369/article/details/108183816

// 1. Kruskal是一种贪心算法,
// 将边的权值排序，先遍历权值小的，用并查集检查两个顶点是否合并了，没有合并则将该边加入生成树
// 也可以使用优先队列实现（相当于排序）
// 时间复杂度主要在对边进行排序上 O(∣E∣log∣E∣)；并查集判断边的两个端点是否在同一个连通分量：近似O(1)

class Solution {
 public:
  int minimumCost(int N, vector<vector<int>>& connections) {
    UnionFind uf(N + 1);  // 因为城市编号从1开始
    sort(connections.begin(), connections.end(), [&](auto a, auto b) {
      return a[2] < b[2];  //距离短的边优先
    });
    int edge = 0, p1 = 0, p2 = 0, dis = 0, total = 0;
    for (int i = 0; i < connections.size(); ++i) {
      p1 = connections[i][0];
      p2 = connections[i][1];
      dis = connections[i][2];
      // 对于两个顶点不在同一连通分量的边，才添加边。
      if (!uf.isConnected(p1, p2)) {
        uf.merge(p1, p2);
        ++edge;
        total += dis;
      }
      if (edge == N - 1) {  // N个节点的图，其生成树的边数量必然是 N-1
        break;
      }
    }
    // 如果边数量不是N-1，那么不存在最小生成树，也就是说这是一个非连通图。
    return edge == N - 1 ? total : -1;
  }
};

// 2. prim，也是贪心
// 把一个初始顶点的所有边加入优先队列,
// 取出最短的边，把这条边的另一个顶点相关的边加入队列
// 再取出最小的边，重复下去，直到所有顶点加入过了
// 时间复杂度: O(|V|^2)
struct cmp {
  // priority_queue自定义函数的比较与sort正好是相反的，
  // 也就是说，如果你是把【大于号】作为第一关键字的比较方式，那么堆顶的元素就是第一关键字最小的
  bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
    return a.second > b.second;  //小顶堆, 距离小的优先
  }
};
class Solution {
 public:
  int minimumCost(int N, vector<vector<int>>& connections) {
    vector<bool> vis(N + 1, false);
    vector<vector<pair<int, int>>> edges(N + 1, vector<pair<int, int>>());
    for (auto& c : connections) {
      // edges[i] 是个vector,里面存了i点直接相连的点及其对应的边的权值。
      // 邻接表
      edges[c[0]].push_back({c[1], c[2]});
      edges[c[1]].push_back({c[0], c[2]});
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
    int to = 0, distance = 0, total = 0, edge = 0;
    vis[1] = true;              // 第1点是起始点。
    for (auto& e : edges[1]) {  // 把第1点的所有边加入优先队列；
      pq.push(e);
    }
    while (!pq.empty()) {
      to = pq.top().first;  // to 是 连通分量a中的所有点的相关边里，权值最小的边的另一个顶点
      distance = pq.top().second;  // 权值最小的边的权值
      pq.pop();                    // 去掉刚刚处理的边
      if (!vis[to]) {  // 如果以前访问过，说明已经在这个连通分量a里，跳过
        vis[to] = true;
        total += distance;
        edge++;
        if (edge == N - 1)  // 放入连通分量 a 的 边数等于N-1，最小生成树形成
          return total;
        for (auto& e : edges[to]) {  // 把顶点to的入边加入队列
          pq.push(e);
        }
      }
    }
    return -1;  // 如果连通分量 a 的 边的数量无法等于N-1，说明是非连通图，没有生成树。
  }
};

/**
 * 在偏远的山区，有N个农户，每户都可以打口井，农户之间也可以修建管道，要使得这些井都能连通。
 * well[N]，打井cost；
 * price[i][j]，修管道cost
 * 要求总cost最小。
 * */

// 解法：水源头我们抽象为0号节点，向其他N个农户增加N个节点，组成一个大图，然后求MST。