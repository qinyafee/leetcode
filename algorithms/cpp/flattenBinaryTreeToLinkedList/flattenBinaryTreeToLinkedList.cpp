// 前序遍历，递归，还能优化
// https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/solution/er-cha-shu-zhan-kai-wei-lian-biao-by-leetcode-solu/
class Solution {
 public:
  void flatten(TreeNode* root) {
    vector<TreeNode*> l;
    preorderTraversal(root, l);
    int n = l.size();
    for (int i = 1; i < n; i++) {
      TreeNode *prev = l.at(i - 1), *curr = l.at(i);
      prev->left = nullptr;
      prev->right = curr;
    }
  }

  void preorderTraversal(TreeNode* root, vector<TreeNode*>& l) {
    if (root != NULL) {
      l.push_back(root);
      preorderTraversal(root->left, l);
      preorderTraversal(root->right, l);
    }
  }
};

//别人的实现
// 递归版1， 时间复杂度O(n)， 空间复杂度O(logn)
class Solution {
 public:
  void flatten(TreeNode* root) {
    helper(root, NULL);
  }
  // 把root所代表树变成链表后， tail跟在该链表后面
  TreeNode* helper(TreeNode* root, TreeNode* tail) {
    if (root == NULL) return tail;
    root->right = helper(root->left, helper(root->right, tail));
    root->left = NULL;
    return root;
  }
};

// clang-format off
// Source : https://oj.leetcode.com/problems/flatten-binary-tree-to-linked-list/
// Author : Hao Chen
// Date   : 2014-07-03

/********************************************************************************** 
* 
* Given a binary tree, flatten it to a linked list in-place.
* 
* For example,
* Given
* 
*          1
*         / \
*        2   5
*       / \   \
*      3   4   6
* 
* The flattened tree should look like:
* 
*    1
*     \
*      2
*       \
*        3
*         \
*          4
*           \
*            5
*             \
*              6
* 
* 
* Hints:
* If you notice carefully in the flattened tree, each node's right child points to 
* the next node of a pre-order traversal.
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
    void flatten(TreeNode *root) {
        
        vector<TreeNode*> v, stack;
        stack.push_back(root);
        while(stack.size()>0){
            TreeNode* node = stack.back();
            stack.pop_back();
            v.push_back(node);
            
            if (node && node->right){
                stack.push_back(node->right);
            }
            if (node && node->left){
                stack.push_back(node->left);
            }
        }
        
        v.push_back(NULL);
        for(int i=0; i<v.size(); i++){
            if (v[i]){
                v[i]->left = NULL;
                v[i]->right = v[i+1];
            }
        }
        
    }
};
