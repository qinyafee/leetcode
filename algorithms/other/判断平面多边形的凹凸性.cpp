// clang-format off
// 原文链接：https://blog.csdn.net/swety_gxy/article/details/70176512

// 1、使用角度和判断凹凸性

// 我们知道，任意n个顶点的凸多边形可以分解成(n-2)个三角形，一个三角形的内角和是180°，所有三角形的内角和是(n-2)*180°，这一点，对于凸多边形或者凹多边形来说都是一样的，但是对于一个凸多边形来说，不存在内角大于外角，而凹多边形则会存在。

// 因此，将多边形每个顶点处较小的角（内角或外角）相加，凸多边形得到(n-2)*180°,而凹多边形则小于它。至于如何判断小角，我们可以使用几何工具---向量点乘。我们知道，向量点乘可以用来等价求两个向量的夹角，它的值（即角度）总是以较短的弧度来度量的。


// 2、连续叉乘法，使用矢量判断凹凸性，检测多边形的凸点

// 叉乘 可以用来判断两个向量在空间中的位置关系，在平面内的多边形，我们有它的有序点集，比如A0A1……An.
// 通过A0A1×A1A2 ……, 只需要记录叉乘的符号。
// 只要有一次叉乘出来的结果符号和之前的不对，就是凹多边形，如果直到最后多是同样的符号，那么就是凸多边形。


// clang-format on


// method1
struct Node {
  int x;
  int y;
  Node *next = nullptr;
}

bool Decide(Node* p0){
  std::vector<Eigen::Vector2d> clock;
  std::vector<Eigen::Vector2d> cclock;
  // auto pEnd = p0;
  auto p = p0;
  int N = 0;
  while (p->next != p0) {
    Eigen::Vector2d O{p->x, p->y};
    Eigen::Vector2d A{p->next->x, p->next->y};
    clock.push_back(A - O);
    cclock.push_back(O - A);
    p = p->next;
    ++N;
  }

  auto calcos = [](Eigen::Vector2d OA, Eigen::Vector2d OB) {
    double dot_product = OA.dot(OB);
    double cos = dot_product / (max(1e-6, OA.norm()) * max(1e-6, OB.norm));
    double theta = std::acos(cos);
    return theta;
  };

  double sum = 0.0;
  for (int i = 0; i < N; ++i) {
    sum += calcos(clock[i], cclock[(i - 1) % N]);// find offset
  }
  return sum < PI * (N - 2);
}