// https://leetcode.cn/problems/count-complete-tree-nodes/solution/wan-quan-er-cha-shu-de-jie-dian-ge-shu-by-leetco-2/
// 规定根节点位于第 0 层，根节点编号=1
// 最大层数为 h 的完全二叉树，节点个数一定在 [2^h,2^(h+1)−1]的范围内,
// 在该范围内通过二分查找,得到完全二叉树的节点个数

// 时间：O(logn*logn)，证明见链接
class Solution {
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
    int bits = 1 << (level - 1);  // 从第l-1位开始找，对应第1层
    TreeNode* p = root;
    while (p != nullptr && bits > 0) {
      if (!(bits & k)) { // 遍历k中的某一位=0
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
// Author : Hao Chen
// Date   : 2015-06-12

/**********************************************************************************
 *
 * Given a complete binary tree, count the number of nodes.
 *
 * Definition of a complete binary tree from Wikipedia:
 * http://en.wikipedia.org/wiki/Binary_tree#Types_of_binary_trees
 *
 * In a complete binary tree every level, except possibly the last, is completely filled,
 * and all nodes in the last level are as far left as possible.
 * It can have between 1 and 2^h nodes inclusive at the last level h.
 *
 **********************************************************************************/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
 public:
  // return -1 if it is not.
  int isCompleteTree(TreeNode* root) {
    if (!root) return 0;

    int cnt = 1;
    TreeNode *left = root, *right = root;
    for (; left && right; left = left->left, right = right->right) {
      cnt *= 2;
    }

    if (left != NULL || right != NULL) {
      return -1;
    }
    return cnt - 1;
  }

  int countNodes(TreeNode* root) {
    int cnt = isCompleteTree(root);
    if (cnt != -1) return cnt;
    int leftCnt = countNodes(root->left);
    int rightCnt = countNodes(root->right);
    return leftCnt + rightCnt + 1;
  }
};
