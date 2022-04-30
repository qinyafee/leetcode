// my implm
// 由于题目没有说节点的数据一定是正整数，必须要走到叶子节点才能判断,
// 因此中途没法剪枝， 只能进行朴素深搜。
class Solution {
public:
	bool hasPathSum(TreeNode* root, int sum) {
		if(root == nullptr) return false;
		// 叶子节点定义
		if(!root->left && !root->right) return sum == root->val;
		return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
	}
};

---------------
输入：
[]
0

预期结果：
false

所以下面给行不通
bool hasPathSum(TreeNode* root, int sum) {
    if(root == NULL) return sum == 0; //行不通
    return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}
--------------------

// clang-format off
// Source : https://oj.leetcode.com/problems/path-sum/
// Author : Hao Chen
// Date   : 2014-06-22

/********************************************************************************** 
* 
* Given a binary tree and a sum, determine if the tree has a root-to-leaf path 
* such that adding up all the values along the path equals the given sum.
* 
* For example:
* Given the below binary tree and sum = 22,
* 
*               5
*              / \
*             4   8
*            /   / \
*           11  13  4
*          /  \      \
*         7    2      1
* 
* return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
*               
**********************************************************************************/

#include <time.h>

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
    Solution(){
        srand(time(NULL));
    }
    bool hasPathSum(TreeNode *root, int sum) {
        return hasPathSum3(root, sum, 0);
        return hasPathSum2(root, sum);
        return hasPathSum1(root, sum);    
    }

    bool hasPathSum3(TreeNode* root, int sum, int s) {
        if ( root == NULL) return false;
        s += root->val;
        if ( !root->left && !root->right)  return s == sum;
        return (hasPathSum3(root->left, sum, s) || hasPathSum3(root->right, sum, s));
    }
    
    bool hasPathSum1(TreeNode *root, int sum) {
        if (root==NULL) return false;
        vector<TreeNode*> v;
        v.push_back(root);
        while(v.size()>0){
            TreeNode* node = v.back();
            v.pop_back();
            if (node->left==NULL && node->right==NULL){
                if (node->val == sum){
                    return true;
                }
            }
            if (node->left){
                node->left->val += node->val;
                v.push_back(node->left);
            }
            if (node->right){
                node->right->val += node->val;
                v.push_back(node->right);
            }
        }
        return false;
        
    }
    
    bool hasPathSum2(TreeNode *root, int sum) {
        
        if (root==NULL) return false;
        
        if (root->left==NULL && root->right==NULL ){
            return (root->val==sum);
        }
        
        if (root->left){
            root->left->val += root->val;
            if (hasPathSum2(root->left, sum)){
                return true;
            }
        }
        
        if (root->right){
            root->right->val += root->val;
            if (hasPathSum2(root->right, sum)){
                return true;
            }
        }
        
        return false;
    }

};
