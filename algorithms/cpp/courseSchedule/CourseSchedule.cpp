
// https://leetcode-cn.com/problems/course-schedule/solution/ke-cheng-biao-by-leetcode-solution/
// 给定一个包含 n 个节点的有向图 G，我们给出它的节点编号的一种排列，如果满足：
// 对于图 G 中的"任意"一条有向边 (u,v)，u 在排列中都出现在 v 的前面。
// 那么称该排列是图 G的「拓扑排序」。
// 结论： 如果图 G 中存在环（即图 G 不是「有向无环图」），那么图 G 不存在拓扑排序。
// 如果图 G 是有向无环图，那么它的拓扑排序可能不止一种。极端例子：图中都是孤立节点。

// dfs
// 深度搜索,
// 当每个节点进行回溯的时候，我们把该节点放入栈中。最终从栈顶到栈底的序列就是一种拓扑排序。
class Solution {
  // 邻接表存DAG
  vector<vector<int>> neighbours;
  // 标记每个节点的状态：0=未搜索，1=搜索中，2=已完成
  vector<int> visited;
  // 判断有向图中是否有环
  bool has_cycle = false;

  void dfs(int u) {
    // 将节点标记为「搜索中」
    visited[u] = 1;
    // 搜索其相邻节点
    // 只要发现有环，立刻停止搜索
    for (const auto& v : neighbours[u]) {
      // 如果「未搜索」那么搜索相邻节点
      if (visited[v] == 0) {
        dfs(v);
        //！搜索相邻节点过程，可能发现环，退出递归
        if (has_cycle) return;
      } else if (visited[v] == 1) {
        has_cycle = true;
        return;
      } else if (visited[v] == 2) {  //已经搜索完，在栈里，不影响。可优化掉。
        continue;
      }
    }
    // 将节点标记为「已完成」
    visited[u] = 2;
  }

 public:
  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    neighbours.resize(numCourses);  //注意此处是节点个数
    visited.resize(numCourses);
    std::fill(visited.begin(), visited.end(), 0);  //初始化未搜索

    //建图
    for (const auto& item : prerequisites) {
      neighbours[item[1]].push_back(item[0]);  //! 注意边的方向
    }
    // 每次挑选一个「未搜索」的节点，开始进行深度优先搜索
    for (int u = 0; u < visited.size(); ++u) {
      if (has_cycle) {
        return false;
      }
      if (visited[u] == 0) {
        dfs(u);
      }
    }
    return !has_cycle;
  }
};

// bfs
// 深度优先搜索是一种「逆向思维」：最先被放入栈中的节点是在拓扑排序中最后面的节点。
// 我们也可以使用正向思维，顺序地生成拓扑排序:
// 1.将所有入度=0 的节点都被放入队列中，它们就是可以作为拓扑排序最前面的节点
// 2.取出队首的节点u，将 u 的所有相邻节点的入度减少 1。如果入度=0，入队。
class Solution {
 public:
  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    // 每个节点的邻接表存DAG
    vector<vector<int>> neighbours;
    neighbours.resize(numCourses);  //注意此处是节点个数
    //每个节点的入度表
    vector<int> indeg(numCourses, 0l);

    //建图
    for (const auto& item : prerequisites) {
      neighbours[item[1]].push_back(item[0]);  //注意边的方向
      ++indeg[item[0]];
    }

    queue<int> que;
    int visited = 0;
    // 将所有入度为 0 的节点放入队列中
    for (int u = 0; u < indeg.size(); ++u) {
      if (indeg[u] == 0) {
        que.push(u);
      }
    }
    while (!que.empty()) {
      // 从队首取出一个节点
      int u = que.front();
      que.pop();
      ++visited;
      for (const auto& v : neighbours[u]) {
        --indeg[v];
        // 如果相邻节点 v 的入度为 0，就可以选 v 对应的课程了
        if (indeg[v] == 0) {
          que.push(v);
        }
      }
    }
    return visited == numCourses;
  }
};

// Source : https://leetcode-cn.com/problems/course-schedule/
// Author : Hao Chen
// Date   : 2015-06-09

/**********************************************************************************
 *
 * There are a total of n courses you have to take, labeled from 0 to n - 1.
 *
 * Some courses may have prerequisites, for example to take course 0 you have to first take course
 *1, which is expressed as a pair: [0,1]
 *
 * Given the total number of courses and a list of prerequisite pairs, is it possible for you to
 * finish all courses?
 *
 * For example:
 *      2, [[1,0]]
 * There are a total of 2 courses to take. To take course 1 you should have finished course 0.
 * So it is possible.
 *
 *      2, [[1,0],[0,1]]
 * There are a total of 2 courses to take. To take course 1 you should have finished course 0,
 * and to take course 0 you should also have finished course 1. So it is impossible.
 *
 * Note:
 * The input prerequisites is a graph represented by a list of edges, not adjacency matrices.
 * Read more about how a graph is represented.
 *
 * click to show more hints.
 *
 * Hints:
 *
 *  - This problem is equivalent to finding if a cycle exists in a directed graph. If a cycle
 *exists, no topological ordering exists and therefore it will be impossible to take all courses.
 *
 *  - Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera explaining the
 *basic concepts of Topological Sort. (https://class.coursera.org/algo-003/lecture/52)
 *
 *  - Topological sort could also be done via BFS.
 *(http://en.wikipedia.org/wiki/Topological_sorting#Algorithms)
 *
 *
 **********************************************************************************/

class Solution {
 public:
  bool hasCycle(int n, vector<int>& explored, vector<int>& path, map<int, vector<int>>& graph) {
    for (int i = 0; i < graph[n].size(); i++) {
      // detect the cycle
      if (path[graph[n][i]]) return true;

      // set the marker
      path[graph[n][i]] = true;

      if (hasCycle(graph[n][i], explored, path, graph)) {
        return true;
      }
      // backtrace reset
      path[graph[n][i]] = false;
    }
    // no cycle found, mark this node can finished!
    explored[n] = true;
    return false;
  }

  bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
    // using map to stroe the graph, it's easy to search the edge for each node
    // the bool in pair means it is explored or not
    map<int, vector<int>> graph;
    for (int i = 0; i < prerequisites.size(); i++) {
      graph[prerequisites[i].first].push_back(prerequisites[i].second);
    }

    // explored[] is used to record the node already checked!
    vector<int> explored(numCourses, false);

    // path[] is used to check the cycle during DFS
    vector<int> path(numCourses, false);

    for (int i = 0; i < numCourses; i++) {
      if (explored[i]) continue;
      if (hasCycle(i, explored, path, graph)) return false;
    }
    return true;
  }
};
