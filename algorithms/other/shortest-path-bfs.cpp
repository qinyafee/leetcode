
// 宽度优先搜索 最短路径
// 对于图搜索的问题，既可以使用bfs也可以使用dfs方法来解决，
// 使用bfs求得的解一定是步数最少的，而dfs则不一定

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
#define maxn 105
#define LL long long
#define lson step << 1
#define rson step << 1 | 1
#define INF 4294967295
using namespace std;
int n, m;
int sx, sy, gx, gy;
struct node {
  int x, y, s;  // s为路径长度
};
char mapp[maxn][maxn];
bool book[maxn][maxn];
void input() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> mapp[i][j];
    }
  }
}
void bfs(int sx, int sy, int gx, int gy) {
  int next[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
  int tx, ty;
  node h, fw;
  h.x = sx;
  h.y = sy;
  h.s = 0;
  queue<node> q;
  q.push(h);
  int flag = 0;
  while (!q.empty()) {
    h = q.front();
    q.pop();
    for (int k = 0; k < 4; k++) {
      tx = h.x + next[k][0];
      ty = h.y + next[k][1];
      if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;
      if (mapp[tx][ty] == '.' && book[tx][ty] == false) {
        fw.x = tx;
        fw.y = ty;
        fw.s = h.s + 1;
        book[tx][ty] = true;
        q.push(fw);
      }
      if (tx == gx && ty == gy) {
        flag = 1;
        break;
      }
    }
    if (flag) break;
  }
  cout << fw.s << endl;
}
int main() {
  // ios_base::sync_with_stdio(false);
  cin >> n >> m;
  input();
  memset(book, false, sizeof(book));
  cin >> sx >> sy >> gx >> gy;
  sx--;
  sy--;
  gx--;
  gy--;
  bfs(sx, sy, gx, gy);

  return 0;
}