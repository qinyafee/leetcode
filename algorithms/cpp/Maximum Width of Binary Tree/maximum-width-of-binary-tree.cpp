// 给每个节点一个 position 值，如果我们走向左子树，那么 position -> position *2，
// 如果我们走向右子树，那么 position -> positon * 2 + 1。
// 当我们在看同一层深度的位置值 L 和 R 的时候，宽度就是 R - L + 1。
// https://leetcode.cn/problems/maximum-width-of-binary-tree/solution/er-cha-shu-zui-da-kuan-du-by-leetcode/

// bfs
class Solution {
 public:
  int widthOfBinaryTree(TreeNode* root) {
    if (!root) {
      return 0;
    }
    queue<pair<TreeNode*, unsigned long long>> q;
    q.emplace(root, 1);
    int ans = 0;
    while (!q.empty()) {
      int len = q.size();
      unsigned long long start = q.front().second, end = 0;
      for (int i = 0; i < len; ++i) {
        auto node = q.front();
        q.pop();
        if (i == len - 1) {
          end = node.second;
        }
        if (node.first->left) {
          q.emplace(node.first->left, 2 * node.second - 1);  // 编号为该层的第几个结点数
        }
        if (node.first->right) {
          q.emplace(node.first->right, 2 * node.second);
        }
      }
      if (ans < end - start + 1) {
        ans = end - start + 1;
      }
    }
    return ans;
  }
};