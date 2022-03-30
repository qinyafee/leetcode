// https://leetcode-cn.com/problems/number-of-islands/solution/dao-yu-lei-wen-ti-de-tong-yong-jie-fa-dfs-bian-li-/

// 1254. 统计封闭岛屿的数目 [related: 130. 被围绕的区域]
// dfs如果遇到边界返回false，否则返回true。
class Solution {
 public:
  constexpr static int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
  int closedIsland(vector<vector<int>>& grid) {
    if(grid.size() < 2 || grid[0].size() < 2) return 0;
    int n = grid.size(), m = grid[0].size();

    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (grid[i][j] == 0) {
          ans += dfs(i, j, grid);
        }
      }
    }
    return ans;
  }

  bool dfs(int x, int y, vector<vector<int>>& grid) {
    bool f = true; // 是封闭岛屿
    grid[x][y] = 1; // 设置visited
    for (auto& dir : dirs) {
      int nx = x + dir[0];
      int ny = y + dir[1];
      if (nx < 0 || ny < 0 || nx >= grid.size() || ny >= grid[0].size()) {
        f = false; // 岛屿dfs遇到了边界
        continue;
      }
      if (grid[nx][ny] == 0) {
        f = min(f, dfs(nx, ny, grid)); //key
      }
    }
    return f;
  };
};

/// 200. 岛屿数量, https://leetcode-cn.com/problems/number-of-islands

class Solution {
 public:
  int numIslands(vector<vector<char>>& grid) {
    if (grid.size() == 0) return 0;

    // 可复用原来的数据
    // 0 —— 海洋格子
    // 1 —— 陆地格子（未遍历过）
    // 2 —— 陆地格子（已遍历过）
    // vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    int count = 0;
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[0].size(); ++j) {
        if (grid[i][j] == '1') {
          dfs(i, j, grid);
          ++count;
        }
      }
    }
    return count;
  }

  void dfs(int i, int j, vector<vector<char>>& grid) {
    //超过边界，直接返回
    if (!inArea(i, j, grid)) return;
    // 格子是海洋或已访问，直接返回
    if (grid[i][j] == '0' || grid[i][j] == '2') return;

    grid[i][j] = '2';  //标记陆地为已访问
    dfs(i, j - 1, grid);
    dfs(i, j + 1, grid);
    dfs(i - 1, j, grid);
    dfs(i + 1, j, grid);
  }
  // 判断坐标 (r, c) 是否在网格中
  bool inArea(int r, int c, vector<vector<char>>& grid) {
    return r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size();
  }
};

/// 695.岛屿的最大面积, https://leetcode-cn.com/problems/max-area-of-island/

class Solution {
 public:
  int maxAreaOfIsland(vector<vector<int>>& grid) {
    if (grid.size() == 0) return 0;
    int max_global = 0;
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[0].size(); ++j) {
        int max_local = dfs(i, j, grid);
        max_global = std::max(max_global, max_local);
      }
    }
    return max_global;
  }

  // 可复用原来的数据
  // 0 —— 海洋格子
  // 1 —— 陆地格子（未遍历过）
  // 2 —— 陆地格子（已遍历过）
  int dfs(int i, int j, vector<vector<int>>& grid) {
    //超过边界，直接返回
    if (!inArea(i, j, grid)) return 0;
    // 格子是海洋或已访问，直接返回
    if (grid[i][j] == 0 || grid[i][j] == 2) return 0;

    grid[i][j] = 2;  //标记陆地为已访问
    return 1 + dfs(i, j - 1, grid) + dfs(i, j + 1, grid) + dfs(i - 1, j, grid) +
           dfs(i + 1, j, grid);
  }
  // 判断坐标 (r, c) 是否在网格中
  bool inArea(int r, int c, vector<vector<int>>& grid) {
    return r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size();
  }
};

// 463. 岛屿的周长, https://leetcode-cn.com/problems/island-perimeter/
class Solution {
 public:
  int islandPerimeter(vector<vector<int>>& grid) {
    if (grid.size() == 0) return 0;
    int length = 0;
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[0].size(); ++j) {
        if (grid[i][j] == 1) {
          length += dfs(i, j, grid);
          break;  //因为只有一个岛屿
        }
      }
    }
    return length;
  }

  // 可复用原来的数据
  // 0 —— 海洋格子
  // 1 —— 陆地格子（未遍历过）
  // 2 —— 陆地格子（已遍历过）
  int dfs(int i, int j, vector<vector<int>>& grid) {
    //超过边界
    if (!inArea(i, j, grid)) return 1;
    // 格子是海洋
    if (grid[i][j] == 0) return 1;
    // 当前格子是已遍历的陆地格子, 和周长没关系
    if (grid[i][j] == 2) return 0;

    grid[i][j] = 2;  //标记陆地为已访问
    return dfs(i, j - 1, grid) + dfs(i, j + 1, grid) + dfs(i - 1, j, grid) + dfs(i + 1, j, grid);
  }
  // 判断坐标 (r, c) 是否在网格中
  bool inArea(int r, int c, vector<vector<int>>& grid) {
    return r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size();
  }
};

/// 827.【Hard】 最大人工岛https://leetcode-cn.com/problems/making-a-large-island/
class Solution {
 public:
  int largestIsland(vector<vector<int>>& grid) {
    if (grid.size() == 0) return 0;
    int id = 1;  //标记连通的岛屿id【已访问的】，从2开始
    map<int, int> id_to_area;
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[0].size(); ++j) {
        if (grid[i][j] == 1) {
          ++id;
          id_to_area[id] = dfsArea(i, j, id, grid);
        }
      }
    }

    int max_global = 0;
    bool has_ocean_grid = false;
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[0].size(); ++j) {
        if (grid[i][j] != 0) continue;
        has_ocean_grid = true;
        set<int> id_set;
        // grid[i][j] = -1;  //标记海洋为已访问
        if (inArea(i, j - 1, grid) && grid[i][j - 1] != 0) id_set.insert(grid[i][j - 1]);
        if (inArea(i, j + 1, grid) && grid[i][j + 1] != 0) id_set.insert(grid[i][j + 1]);
        if (inArea(i - 1, j, grid) && grid[i - 1][j] != 0) id_set.insert(grid[i - 1][j]);
        if (inArea(i + 1, j, grid) && grid[i + 1][j] != 0) id_set.insert(grid[i + 1][j]);
        int area = 1;  //填海格子
        for (const auto& id : id_set) {
          area += id_to_area[id];
        }
        max_global = max(max_global, area);
      }
    }
    return has_ocean_grid ? max_global
                          : grid.size() * grid[0].size();  //如果没有海洋，返回整个grid面积
  }

  int dfsArea(int i, int j, int id, vector<vector<int>>& grid) {
    //超过边界，直接返回
    if (!inArea(i, j, grid)) return 0;
    // 不是【未访问的陆地格子】，直接返回
    if (grid[i][j] != 1) return 0;

    grid[i][j] = id;  //标记陆地为已访问
    return 1 + dfsArea(i, j - 1, id, grid) + dfsArea(i, j + 1, id, grid) +
           dfsArea(i - 1, j, id, grid) + dfsArea(i + 1, j, id, grid);
  }

  // int dfsOcean(int i, int j, vector<vector<int>>& grid, map<int, int>& id_to_area) {

  // }
  // 判断坐标 (r, c) 是否在网格中
  bool inArea(int r, int c, vector<vector<int>>& grid) {
    return r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size();
  }
};