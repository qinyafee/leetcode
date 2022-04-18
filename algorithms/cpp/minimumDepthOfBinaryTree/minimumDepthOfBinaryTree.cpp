// Source : https://oj.leetcode.com/problems/minimum-depth-of-binary-tree/
// Author : Hao Chen
// Date   : 2014-06-22

/**********************************************************************************
 *
 * Given a binary tree, find its minimum depth.
 *
 * The minimum depth is the number of nodes along the shortest path from the root node
 * down to the nearest leaf node.
 *
 **********************************************************************************/

// my implm
// 思路：
// 很多人写出的代码都不符合 1,2 这个测试用例，是因为没搞清楚题意
// 题目中说明:叶子节点是指没有子节点的节点，这句话的意思是 1 不是叶子节点
// 题目问的是到叶子节点的最短距离，所以所有返回结果为 1 当然不是这个结果

// 另外这道题的关键是搞清楚*递归结束条件*:
// 定义：叶子节点的定义是左孩子和右孩子都为 NULL 时叫做叶子节点
// 1.当 root 节点为空时，返回深度0
// 2.当 root 节点左右孩子都为空时，返回 1
// 3.当 root 节点左右孩子有一个为空时，*返回不为空*的孩子节点的深度【因为孩子为空的节点处不是叶子】
// 4.当 root 节点左右孩子都不为空时，返回左右孩子较小深度的节点值
// https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/solution/li-jie-zhe-dao-ti-de-jie-shu-tiao-jian-by-user7208/
class Solution {
 public:
  int minDepth(TreeNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    int m1 = minDepth(root->left);
    int m2 = minDepth(root->right);
    if (root->left == NULL || root->right == NULL) return m1 + m2 + 1;
    return min(m1, m2) + 1;
  }
};

// 几种情况分开写
class Solution {
 public:
  int minDepth(TreeNode* root) {
    if (root == NULL) return 0;
    //这道题递归条件里分为三种情况
    // 1.左孩子和有孩子都为空的情况，说明到达了叶子节点，直接返回1即可
    if (root->left == NULL && root->right == NULL) return 1;
    // 2.如果左孩子和由孩子其中一个为空，那么需要返回比较大的那个孩子的深度
    int m1 = minDepth(root->left);
    int m2 = minDepth(root->right);
    //这里其中一个节点为空，说明m1和m2有一个必然为0，所以可以返回m1 + m2 + 1;
    if (root->left == NULL || root->right == NULL) return m1 + m2 + 1;

    // 3.最后一种情况，也就是左右孩子都不为空，返回最小深度+1即可
    return min(m1, m2) + 1;
  }
}

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
  int minDepth(TreeNode* root) {
    if (root == NULL) {
      return 0;
    }
    if (root->left == NULL && root->right == NULL) {
      return 1;
    }
    int left = INT_MAX;
    if (root->left) {
      left = minDepth(root->left) + 1;
    }
    int right = INT_MAX;
    if (root->right) {
      right = minDepth(root->right) + 1;
    }

    return left < right ? left : right;
  }
};
