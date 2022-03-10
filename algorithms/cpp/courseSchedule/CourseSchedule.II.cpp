// https://leetcode-cn.com/problems/course-schedule/solution/ke-cheng-biao-by-leetcode-solution/
// 给定一个包含 n 个节点的有向图 G，我们给出它的节点编号的一种排列，如果满足：
// 对于图 G 中的"任意"一条有向边 (u,v)，u 在排列中都出现在 v 的前面。
// 那么称该排列是图 G的「拓扑排序」。
// 结论： 如果图 G 中存在环（即图 G 不是「有向无环图」），那么图 G 不存在拓扑排序。
// 如果图 G 是有向无环图，那么它的拓扑排序可能不止一种。极端例子：图中都是孤立节点。

// dfs
class Solution {
  // 邻接表存DAG
  vector<vector<int>> neighbours;
  // 标记每个节点的状态：0=未搜索，1=搜索中，2=已完成
  vector<int> visited;
  // vector模拟栈
  vector<int> fake_stack;
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
    // 将节点入栈
    fake_stack.push_back(u);
  }

 public:
  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    neighbours.resize(numCourses);  //注意此处是节点个数
    visited.resize(numCourses);
    std::fill(visited.begin(), visited.end(), 0);  //初始化未搜索

    //建图
    for (const auto& item : prerequisites) {
      neighbours[item[1]].push_back(item[0]);  //注意边的方向
    }
    // 每次挑选一个「未搜索」的节点，开始进行深度优先搜索
    for (int u = 0; u < visited.size(); ++u) {
      if (has_cycle) return {};
      if (visited[u] == 0) dfs(u);
    }
    if (has_cycle) return {};

    // 如果没有环，那么就有拓扑排序
    //从栈顶到栈底看，是拓扑排序，所以相当于vector反向
    reverse(fake_stack.begin(), fake_stack.end());
    return fake_stack;
  }
};

// bfs
class Solution {
 public:
  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    // 每个节点的邻接表存DAG
    vector<vector<int>> neighbours;
    neighbours.resize(numCourses);  //注意此处是节点个数
    //每个节点的入度表
    vector<int> indeg(numCourses, 0l);
    vector<int> topology;
    topology.reserve(numCourses);
    //建图
    for (const auto& item : prerequisites) {
      neighbours[item[1]].push_back(item[0]);  //注意边的方向
      ++indeg[item[0]];
    }

    queue<int> que;
    // 将所有入度为 0 的节点放入队列中
    for (int u = 0; u < indeg.size(); ++u) {
      if (indeg[u] == 0) que.push(u);
    }
    while (!que.empty()) {
      // 从队首取出一个节点
      int u = que.front();
      que.pop();
      topology.push_back(u);
      for (const auto& v : neighbours[u]) {
        --indeg[v];
        // 如果相邻节点 v 的入度为 0，就可以选 v 对应的课程了
        if (indeg[v] == 0) que.push(v);
      }
    }
    //这种情况存在环。环中节点的入度都不是0
    if (topology.size() != numCourses) return {};

    return topology;
  }
};

// Source : https://leetcode.com/problems/course-schedule-ii/
// Author : Hao Chen
// Date   : 2015-06-10

/**********************************************************************************
 *
 * There are a total of n courses you have to take, labeled from 0 to n - 1.
 *
 * Some courses may have prerequisites, for example to take course 0 you have to first take course
 *1, which is expressed as a pair: [0,1]
 *
 * Given the total number of courses and a list of prerequisite pairs, return the ordering of
 *courses you should take to finish all courses.
 *
 * There may be multiple correct orders, you just need to return one of them. If it is impossible to
 * finish all courses, return an empty array.
 *
 * For example:
 *      2, [[1,0]]
 * There are a total of 2 courses to take. To take course 1 you should have finished course 0.
 * So the correct course order is [0,1]
 *
 *      4, [[1,0],[2,0],[3,1],[3,2]]
 * There are a total of 4 courses to take. To take course 3 you should have finished both courses 1
 *and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course
 *order is [0,1,2,3]. Another correct ordering is[0,2,1,3].
 *
 * Note:
 * The input prerequisites is a graph represented by a list of edges, not adjacency matrices.
 * Read more about how a graph is represented.
 *
 * click to show more hints.
 *
 * Hints:
 *
 *  - This problem is equivalent to finding the topological order in a directed graph. If a cycle
 *exists, no topological ordering exists and therefore it will be impossible to take all courses.
 *
 *  - Topological Sort via DFS - A great video tutorial (21 minutes) on Coursera explaining
 *    the basic concepts of Topological Sort.
 *
 *  - Topological sort could also be done via BFS.
 *
 *
 **********************************************************************************/

class Solution {
 public:
  // if has cycle, return false, else return true
  bool topologicalSort(int n, vector<int>& explored, vector<int>& path,
                       unordered_map<int, vector<int>>& graph, vector<int>& result) {
    for (int i = 0; i < graph[n].size(); i++) {
      int prereq = graph[n][i];

      if (path[prereq]) {
        result.clear();
        return false;
      }

      path[prereq] = true;
      if (!topologicalSort(prereq, explored, path, graph, result)) {
        result.clear();
        return false;
      }
      path[prereq] = false;
    }
    if (!explored[n]) {
      result.push_back(n);
    }
    explored[n] = true;
    return true;
  }

  vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<int> result;
    vector<int> enterance(numCourses, true);

    // using map to stroe the graph, it's easy to search the edge for each node
    // the bool in pair means it is explored or not
    unordered_map<int, vector<int>> graph;
    for (int i = 0; i < prerequisites.size(); i++) {
      graph[prerequisites[i].first].push_back(prerequisites[i].second);
      enterance[prerequisites[i].second] = false;
    }

    // explored[] is used to record the node already checked!
    vector<int> explored(numCourses, false);

    // path[] is used to check the cycle during DFS
    vector<int> path(numCourses, false);

    for (int i = 0; i < numCourses; i++) {
      if (!enterance[i] || explored[i]) continue;
      if (!topologicalSort(i, explored, path, graph, result)) return result;
    }
    // if there has one course hasn't been explored, means there is a cycle
    for (int i = 0; i < numCourses; i++) {
      if (!explored[i]) return vector<int>();
    }
    return result;
  }
};
