// 1765. 地图中的最高点, https://leetcode-cn.com/problems/map-of-highest-peak/
// https://leetcode-cn.com/problems/map-of-highest-peak/solution/gong-shui-san-xie-duo-yuan-bfs-yun-yong-8sw0f/
//https://juejin.cn/post/6979044529680678920

const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
class Solution {
 public:
  vector<vector<int>> highestPeak(vector<vector<int>>& g) {
    int n = g.size(), m = g[0].size();
    queue<pair<int, int>> q;
    vector<vector<int>> ans(n, vector<int>(m, 0));  //海洋填0
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (g[i][j] == 1) {  // =1,是海洋
          q.emplace(i, j);
        } else {
          ans[i][j] = -1;  //未访问的陆地填-1
        }
      }
    }
    while (!q.empty()) {
      auto [x, y] = q.front();
      q.pop();
      for (int i = 0; i < 4; ++i) {
        int a = x + dx[i], b = y + dy[i];
        if (a < 0 || a == n || b < 0 || b == m) continue;  // not inArea
        if (ans[a][b] >= 0) continue;                      //海洋+已访问的陆地
        ans[a][b] = ans[x][y] + 1;
        q.emplace(a, b);
      }
    }
    return ans;
  }
};
