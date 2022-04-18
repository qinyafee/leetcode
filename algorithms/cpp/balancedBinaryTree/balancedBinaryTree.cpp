// my implm
// 平衡二叉树: 二叉树的每个节点的左右子树的高度差的绝对值不超过1.
// 一棵二叉树是平衡二叉树，当且仅当其所有子树也都是平衡二叉树
// 定义函数 𝚑𝚎𝚒𝚐𝚑𝚝，计算二叉树中每个节点p的高度
// height(p) = 0, p为空
// height(p) = max(height(p->left), height(p->right)) +1, p不为空
// https://leetcode-cn.com/problems/balanced-binary-tree/solution/ping-heng-er-cha-shu-by-leetcode-solution/

// 自顶向下的递归, 类似前序遍历
class Solution {
 public:
  bool isBalanced(TreeNode* root) {
    if (root == nullptr) {
      return true;
    } else {
      return abs(height(root->left) - height(root->right)) <= 1 && isBalanced(root->left) &&
             isBalanced(root->right);
    }
  }
  int height(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    } else {
      return max(height(root->left), height(root->right)) + 1;
    }
  }
};


// 别人的实现版本
class Solution {
 public:
  bool isBalanced(TreeNode* root) {
    return balancedHeight(root) >= 0;
  }

  int balancedHeight(TreeNode* root) {
    if (root == nullptr) return 0;  // 终止条件

    int left = balancedHeight(root->left);
    int right = balancedHeight(root->right);

    if (left < 0 || right < 0 || std::abs(left - right) > 1) return -1;  // 剪枝

    return max(left, right) + 1;  // 三方合并
  }
};


// clang-format off

// Source : https://oj.leetcode.com/problems/balanced-binary-tree/
// Author : Hao Chen
// Date   : 2014-06-28

/********************************************************************************** 
* 
* Given a binary tree, determine if it is height-balanced.
* 
* For this problem, a height-balanced binary tree is defined as a binary tree in which 
* the depth of the two subtrees of every node never differ by more than 1.
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
    bool isBalanced(TreeNode *root) {
        int height=0;
        return isBalancedUtil(root, height);
    }

    bool isBalancedUtil(TreeNode* root, int& height){
       if(root==NULL){
          height=0;
          return true;
       }
       int lh=0, rh=0;
       bool isLeft = isBalancedUtil(root->left, lh);
       bool isRight = isBalancedUtil(root->right, rh);
       height = (lh > rh ? lh : rh) + 1;
       return (abs(lh-rh)<=1 && isLeft && isRight);
    }

};

//Notes: 
// I think the above solution should be more efficent than the below, 
//  but for leetcode, the below solution needs 60ms, the above needs 88ms
class Solution {
public:
    bool isBalanced(TreeNode *root) {
        if (root==NULL) return true;
        
        int left = treeDepth(root->left); 
        int right = treeDepth(root->right);
        
        if (left-right>1 || left-right < -1) {
            return false;
        }
        return isBalanced(root->left) && isBalanced(root->right);
    }
    
    int treeDepth(TreeNode *root) {
        if (root==NULL){
            return 0;
        }

        int left=1, right=1;
        
        left += treeDepth(root->left);
        right += treeDepth(root->right);
        
        return left>right?left:right;
    }

};
