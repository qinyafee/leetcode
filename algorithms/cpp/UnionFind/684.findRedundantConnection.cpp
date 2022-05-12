// https://leetcode.cn/problems/redundant-connection/submissions/
// 并查集

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
    if (pa == pb) {
      return;
    }
    parent[pa] = pb;
  }
};

class Solution {
 public:
  vector<int> findRedundantConnection(vector<vector<int>>& edges) {
		set<int> vertexs;
		for(const auto& e : edges){
			vertexs.insert(e[0]);
			vertexs.insert(e[1]);
		}
		const int N = vertexs.size();
		UnionFind uf(N+1);
		for(auto it = edges.begin(); it != edges.end(); ++it){
			const int from = it->front();
			const int to = it->back();
			if(!uf.isConnected(from, to)){
				uf.merge(from, to);
			} else{
				return *it;
			}
		}
		return {};
  }
};