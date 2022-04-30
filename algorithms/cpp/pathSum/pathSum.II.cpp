// Source : https://oj.leetcode.com/problems/path-sum-ii/
// Author : Hao Chen
// Date   : 2014-07-01

/**********************************************************************************
 *
 * Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given
 *sum.
 *
 * For example:
 * Given the below binary tree and sum = 22,
 *
 *               5
 *              / \
 *             4   8
 *            /   / \
 *           11  13  4
 *          /  \    / \
 *         7    2  5   1
 *
 * return
 *
 * [
 *    [5,4,11,2],
 *    [5,8,4,5]
 * ]
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

// my implm
class Solution {
 public:
  vector<vector<int>> pathSum(TreeNode* root, int sum) {
    vector<vector<int>> result;
    vector<int> cur;
    generatePathSum(root, sum, 0, cur, result);
    return result;
  }

  // 此处cur不能用引用
  void generatePathSum(TreeNode* root, int sum, int s, vector<int> cur,
                       vector<vector<int>>& result) {
    if (root == NULL) return;

    s += root->val;
    cur.push_back(root->val);

    // 叶节点定义
    if (root->left == NULL && root->right == NULL) {
      if (s == sum) result.push_back(cur);  // 满足条件才push
      return;
    }

    generatePathSum(root->left, sum, s, cur, result);
    generatePathSum(root->right, sum, s, cur, result);
		cur.pop_back(); // 因为前两句push了两次root->val
  }
};

// 别人实现
class Solution {
 public:
  vector<vector<int>> pathSum(TreeNode* root, int sum) {
    vector<vector<int>> result;
    vector<int> cur;  // 中间结果
    pathSum(root, sum, cur, result);
    return result;
  }

 private:
  void pathSum(TreeNode* root, int gap, vector<int>& cur, vector<vector<int>>& result) {
    if (root == nullptr) return;
    cur.push_back(root->val);
    if (root->left == nullptr && root->right == nullptr) {  // leaf
      if (gap == root->val) result.push_back(cur);
    }
    pathSum(root->left, gap - root->val, cur, result);
    pathSum(root->right, gap - root->val, cur, result);
    cur.pop_back(); // 因为前两句push了两次root->val
  }
};