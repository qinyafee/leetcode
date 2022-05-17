// https://leetcode.cn/problems/sum-root-to-leaf-numbers/solution/qiu-gen-dao-xie-zi-jie-dian-shu-zi-zhi-he-by-leetc/
// 1. 深搜，递归
// Sum root to leaf numbers
// 时间复杂度O(n)， 空间复杂度O(logn)
class Solution {
 public:
  int sumNumbers(TreeNode* root) {
    return dfs(root, 0);
  }

 private:
  int dfs(TreeNode* root, int sum) { // sum是上一层的结果
    if (root == nullptr) {
      return 0;
    }
    if (root->left == nullptr && root->right == nullptr) { // root是叶节点
      return sum * 10 + root->val;
    }
    return dfs(root->left, sum * 10 + root->val) + dfs(root->right, sum * 10 + root->val);
  }
};

// Source : https://oj.leetcode.com/problems/sum-root-to-leaf-numbers/
// Author : Hao Chen
// Date   : 2014-06-21

/**********************************************************************************
 *
 * Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a
 *number. An example is the root-to-leaf path 1->2->3 which represents the number 123.
 *
 * Find the total sum of all root-to-leaf numbers.
 *
 * For example,
 *
 *     1
 *    / \
 *   2   3
 *
 * The root-to-leaf path 1->2 represents the number 12.
 * The root-to-leaf path 1->3 represents the number 13.
 *
 * Return the sum = 12 + 13 = 25.
 *
 *
 **********************************************************************************/

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
 public:
  int sumNumbers(TreeNode* root) {
    if (!root) return 0;

    int sum = 0;
    vector<TreeNode*> v;
    v.push_back(root);
    while (v.size() > 0) {
      TreeNode* node = v.back();
      v.pop_back();
      if (node->left) {
        node->left->val += (10 * node->val);
        v.push_back(node->left);
      }
      if (node->right) {
        node->right->val += (10 * node->val);
        v.push_back(node->right);
      }
      if (!node->right && !node->left) {
        sum += node->val;
      }
    }

    return sum;
  }
};
