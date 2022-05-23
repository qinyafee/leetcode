// 暴力
// 挨个节点遍历bfs，统计下每个节点的高度，然后用map存储起来，后面查询这个高度的集合里最小的就可以了。

// bfs
// 首先，我们看了样例，发现这个树并不是二叉树，是多叉树。于是我们看图（题目介绍里面的图）分析一下，发现，越是靠里面的节点越有可能是最小高度树。
// 所以，我们可以这样想，我们可以倒着来。
// 我们从边缘开始，先找到所有出度为1的节点，然后把所有出度为1的节点进队列，然后不断地bfs，最后找到的就是两边同时向中间靠近的节点，那么这个中间节点就相当于把整个距离二分了，那么它当然就是到两边距离最小的点啦，也就是到其他叶子节点最近的节点了。
// https://leetcode.cn/problems/minimum-height-trees/solution/zui-rong-yi-li-jie-de-bfsfen-xi-jian-dan-zhu-shi-x/

class Solution {
 public:
  vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    if (n == 1) return {0};
    vector<int> degree(n, 0);  //每个节点对应的度数
    map<int, vector<int>> m;   //邻接表
    vector<int> res;           //结果
    for (int i = 0; i < edges.size(); i++) {
      int u = edges[i][0];
      int v = edges[i][1];
      degree[u]++;
      degree[v]++;
      m[u].push_back(v);
      m[v].push_back(u);
    }
    queue<int> q;
    //把叶子节点入栈
    for (int i = 0; i < n; i++) {
      if (degree[i] == 1) {
        q.push(i);
      }
    }
    //从外向内一层一层剥，每次加入的都是一层的
    while (!q.empty()) {
      res.clear();
      int sz = q.size();
      //一层全部加入结果并且清出去
      for (int i = 0; i < sz; i++) {
        int t = q.front();
        q.pop();
        res.push_back(t);
        //加入t的邻接叶子节点
        degree[t]--;
        for (auto j : m[t]) {
          degree[j]--;
          if (degree[j] == 1) {
            q.push(j);
          }
        }
      }
    }
    return res;
  }
};

// Source : https://leetcode.com/problems/minimum-height-trees/
// Author : Hao Chen
// Date   : 2016-01-24

/***************************************************************************************
 *
 * For a undirected graph with tree characteristics, we can choose any node as the
 * root. The result graph is then a rooted tree. Among all possible rooted trees, those
 * with minimum height are called minimum height trees (MHTs).
 *
 * Given such a graph, write a function to find all the MHTs and return a list of
 * their root labels.
 *
 *     *Format*
 *     The graph contains n nodes which are labeled from 0 to n - 1.
 *     You will be given the number n and a list of undirected edges (each edge is a
 *     pair of labels).
 *
 *
 *     You can assume that no duplicate edges will appear in edges. Since all edges are
 *     undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.
 *
 *     Example 1:
 *
 *     Given n = 4, edges = [[1, 0], [1, 2], [1, 3]]
 *
 *         0
 *         |
 *         1
 *        / \
 *       2   3
 *
 *     return  [1]
 *
 *     Example 2:
 *
 *     Given n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]
 *
 *      0  1  2
 *       \ | /
 *         3
 *         |
 *         4
 *         |
 *         5
 *
 *     return  [3, 4]
 *
 *     How many MHTs can a graph have at most?
 *
 *     Note:
 *
 *     (1) According to the definition of tree on Wikipedia:
 *https://en.wikipedia.org/wiki/Tree_(graph_theory) “a tree is an undirected graph in which any two
 *vertices are connected by exactly one path. In other words, any connected graph without simple
 *cycles is a tree.”
 *
 *     (2) The height of a rooted tree is the number of edges on the longest downward path between
 *         the root and a leaf.
 *
 * Credits:Special thanks to @dietpepsi for adding this problem and creating all test
 * cases.
 ***************************************************************************************/

class Solution {
 public:
  vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
    // corner case
    if (n <= 1) return {0};

    // construct a edges search data stucture
    vector<unordered_set<int>> graph(n);
    for (auto e : edges) {
      graph[e.first].insert(e.second);
      graph[e.second].insert(e.first);
    }

    // find all of leaf nodes
    vector<int> current;
    for (int i = 0; i < graph.size(); i++) {
      if (graph[i].size() == 1) current.push_back(i);
    }

    // BFS the graph
    while (true) {
      vector<int> next;
      for (int node : current) {
        for (int neighbor : graph[node]) {
          graph[neighbor].erase(node);
          if (graph[neighbor].size() == 1) next.push_back(neighbor);
        }
      }
      if (next.empty()) break;
      current = next;
    }
    return current;
  }
};
