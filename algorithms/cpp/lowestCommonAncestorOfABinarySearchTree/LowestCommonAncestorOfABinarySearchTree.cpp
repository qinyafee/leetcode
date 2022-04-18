// Source : https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
// Author : Hao Chen
// Date   : 2015-07-17

/**********************************************************************************
 *
 * Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given
 * nodes in the BST.
 *
 * According to the definition of LCA on Wikipedia: “The lowest common ancestor is
 * defined between two nodes v and w as the lowest node in T that has both v and w as
 * descendants (where we allow a node to be a descendant of itself).”
 *
 *         _______6______
 *        /              \
 *     ___2__          ___8__
 *    /      \        /      \
 *    0      _4       7       9
 *          /  \
 *          3   5
 *
 * For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. Another example
 * is LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according
 * to the LCA definition.
 *
 *
 **********************************************************************************/

// my implm
class Solution {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // 1. 两个子节点都在树的左子树上，需递归到左子树上
    if (root->val > p->val && root->val > q->val) return lowestCommonAncestor(root->left, p, q);
    // 2. 两个子节点都在树的右子树上，需递归到右子树上
    if (root->val < p->val && root->val < q->val) return lowestCommonAncestor(root->right, p, q);

    // // 3. 一个子节点在左子树， 一个子节点在右子树，当前节点即为最近公共祖先
    // if(root->val > p->val && root->val < q->val) return root;
    // // 4. 一个子节点的值和根节点的值相等，当前节点即为最近公共祖先
    // if(root->val == p->val || root->val == q->val) return root;
    return root;
  }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// my implm
// 根据二叉搜索树的性质， 两个子节点 p , q 和根节点 root 的关系， 有以下四种情况：
// 1. 两个子节点都在树的左子树上
// 2. 两个子节点都在树的右子树上
// 3. 一个子节点在左子树， 一个子节点在右子树
// 4. 一个子节点的值和根节点的值相等
// 若为情况3或4，当前节点即为最近公共祖先；若为情况1或2，则还需递归到左或右子树上，继续这个过程。
class Solution {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
      if (p->val > root->val && q->val > root->val) {
        root = root->right;
        continue;  //跳出当前循环，继续下一次循环
      }
      if (p->val < root->val && q->val < root->val) {
        root = root->left;
        continue;  //跳出当前循环，继续下一次循环
      }
      return root;
    }
    return nullptr;
  }
};
