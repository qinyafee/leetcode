
// 链接：https://leetcode.cn/problems/is-graph-bipartite/solution/bfs-dfs-bing-cha-ji-san-chong-fang-fa-pan-duan-er-/

// 1. dfs

class Solution {
 public:
  bool isBipartite(vector<vector<int>>& graph) {
    // 初始值为 0 表示未被访问，赋值为 1 或者 -1 表示两种不同的颜色。
    vector<int> visited(graph.size(), 0);

    // 因为图中可能含有多个连通域，所以我们需要判断是否存在顶点未被访问，
    // 若存在则从它开始再进行一轮 dfs 染色。
    for (int i = 0; i < graph.size(); i++) {
      if (visited[i] == 0 && !dfs(graph, i, 1, visited)) {
        return false;
      }
    }
    return true;
  }

 private:
  bool dfs(vector<vector<int>>& graph, int v, int color, vector<int>& visited) {
    // 如果要对某顶点染色时，发现它已经被染色了，则判断它的颜色是否与本次要染的颜色相同，
    // 如果相同，返回false。
    if (visited[v] != 0) {
      return visited[v] == color;
    }

    // 对当前顶点进行染色，并将当前顶点的所有邻接点染成相反的颜色。
    visited[v] = color;
    for (int w : graph[v]) {
      if (!dfs(graph, w, -color, visited)) {
        return false;
      }
    }
    return true;
  }
};

// 2. bfs
class Solution {
 public:
  bool isBipartite(vector<vector<int>>& graph) {
    // 初始值为 0 表示未被访问，赋值为 1 或者 -1 表示两种不同的颜色
    vector<int> visited(graph.size(), 0);
    queue<int> que;
    // 因为图中可能含有多个连通域，所以我们需要判断是否存在顶点未被访问，
    // 若存在则从它开始再进行一轮 bfs 染色。
    for (int i = 0; i < graph.size(); i++) {
      if (visited[i] != 0) {
        continue;
      }
      // 每出队一个顶点，将其所有邻接点染成相反的颜色并入队。
      que.push(i);
      visited[i] = 1;
      while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (int w : graph[v]) {
          // 如果当前顶点的某个邻接点已经被染过色了，且颜色和当前顶点相同，
          // 说明此无向图无法被正确染色，返回false。
          if (visited[w] == visited[v]) {
            return false;
          }
          if (visited[w] == 0) {
            visited[w] = -visited[v];
            que.push(w);
          }
        }
      }
    }
    return true;
  }
};

// 3.并查集