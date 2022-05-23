// 求x到y的最少计算次数
// 给定两个-100到100的整数x和y,对x只能进行加1，减1，乘2操作，问最少对x进行几次操作能得到y？
// 例如：
// a=3,b=11: 可以通过3*2*2-1，3次操作得到11；
// a=5,b=8：可以通过(5-1)*2，2次操作得到8；

#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

// 宽搜
int main() {
  int x, y;
  int cnt = 0;
  bool flag = false;
  scanf("%d,%d", &x, &y);
  queue<int> q;
  q.push(x);
  while (!q.empty()) {
    int len = q.size();
    for (int i = 0; i < len; i++) {
      int tmp = q.front();
      q.pop();
      if (tmp == y) {
        flag = true;
        break;
      } else {
        q.push(tmp + 1);
        q.push(tmp - 1);
        q.push(tmp * 2);
      }
    }
    if (flag) break;
    cnt++;
  }
  cout << cnt << endl;
  return 0;
}