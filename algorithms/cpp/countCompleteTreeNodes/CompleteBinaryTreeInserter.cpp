// 222. Count Complete Tree Nodes
// https://leetcode.cn/problems/count-complete-tree-nodes/solution/wan-quan-er-cha-shu-de-jie-dian-ge-shu-by-leetco-2/
// 规定根节点位于第 0 层，根节点编号=1
// 最大层数为 h 的完全二叉树，节点个数一定在 [2^h,2^(h+1)−1]的范围内,
// 在该范围内通过二分查找,得到完全二叉树的节点个数

// 919.
// https://leetcode.cn/problems/complete-binary-tree-inserter/solution/cshuang-100-shi-xian-o1kong-jian-olognsh-nwm4/

class CBTInserter {
 private:
  TreeNode* root_;
  int size_;

 public:
  CBTInserter(TreeNode* root) : root_(root) {
    size_ = countNodes(root);
  }

  int insert(int val) {
    TreeNode* node = root_;
    int idx = ++size_;  // idx: 本次插入结点的编号
    int _idx = idx;
    int bits = 0;  // bits: idx的位数
    while (_idx) {
      ++bits;
      _idx >>= 1;
    }

    --bits;               // idx首位1不需要
    while (--bits > 0) {  //! bits=1时，--bits=0, 最后一次不进入
      if (idx & (1 << bits)) {
        node = node->right;
      } else {
        node = node->left;
      }
    }
    // 处理循环的最后一次,bits=0
    if (idx & 1) {
      node->right = new TreeNode(val);  // 此时node是上一层最后一个元素
    } else {
      node->left = new TreeNode(val);
    }
    return node->val;
  }

  TreeNode* get_root() {
    return root_;
  }

 public:
  int countNodes(TreeNode* root) {
    if (root == nullptr) {
      return 0;  //! corner case
    }
    int level = 0;  //规定根节点位于第 0 层
    TreeNode* p = root;
    while (p->left != nullptr) {  //求得最大层数h
      ++level;
      p = p->left;
    }

    // 节点序号：上界= 2^h，下界=2^(h+1)-1
    int low = 1 << level, high = (1 << (level + 1)) - 1;
    while (low < high) {
      int mid = (high - low + 1) / 2 + low;
      if (exists(root, level, mid)) {
        low = mid;  // 如果第 k 个节点存在，则节点个数一定 >=k
      } else {
        high = mid - 1;  // 如果第 k 个节点不存在，则节点个数一定 <k
      }
    }
    return low;
  }

  // 判断最后一层第k个索引是否存在
  // 如果第 k 个节点位于第 l 层，则 k 的二进制表示包含 l+1 位
  // 其中最高位是 1，其余各位从高到低表示从根节点到第 k 个节点的路径，
  // 0 表示移动到左子节点，1表示移动到右子节点。
  bool exists(TreeNode* root, int level, int k) {
    int bits = 1 << (level - 1);  // 从第l-1位开始找，对应第l=1层
    TreeNode* p = root;
    while (p != nullptr && bits > 0) {
      if (!(bits & k)) {
        p = p->left;
      } else {
        p = p->right;
      }
      bits >>= 1;
    }
    return p != nullptr;
  }
};

// Source : https://leetcode.com/problems/count-complete-tree-nodes/
