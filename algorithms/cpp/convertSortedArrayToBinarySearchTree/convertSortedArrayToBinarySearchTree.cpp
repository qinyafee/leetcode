// my implm
// 给定二叉搜索树的中序遍历，不能唯一地确定二叉搜索树， 因为任何一个数字都可以作为二叉搜索树的根节点。
// 要求二叉搜索树的高度平衡：
// 如果偶数个节点，不能唯一确定(两种根节点选择)；如果奇数个节点，可以唯一确定。
// https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/solution/jiang-you-xu-shu-zu-zhuan-huan-wei-er-cha-sou-s-33/

//自顶向下的二分法，递归
class Solution {
 public:
  TreeNode* sortedArrayToBST(vector<int>& nums) {
    return helper(nums, 0, nums.size() - 1);
  }

  TreeNode* helper(vector<int>& nums, int left, int right) {
    if (left > right) {
      return nullptr;
    }

    // 总是选择中间位置左边的数字作为根节点
		// 当然也可以选右边的
    int mid = (left + right) / 2;

    TreeNode* root = new TreeNode(nums[mid]);
    root->left = helper(nums, left, mid - 1);
    root->right = helper(nums, mid + 1, right);
    return root;
  }
};

// clang-format off
// Source : https://oj.leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
// Author : Hao Chen
// Date   : 2014-06-23

/********************************************************************************** 
* 
* Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
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
    TreeNode *sortedArrayToBST(vector<int> &num) {
        if(num.size()==0){
            return NULL;
        }
        if(num.size()==1){
            return new TreeNode(num[0]);
        }
        int mid = num.size()/2;
        
        TreeNode *node = new TreeNode(num[mid]);
        
        vector<int>::const_iterator first;
        vector<int>::const_iterator last;

        first = num.begin();
        last = num.begin()+mid;
        vector<int> v(first, last);
        node->left = sortedArrayToBST(v);
        
        if (mid==num.size()-1){
            node->right = NULL;
        }else{
            first = num.begin()+mid+1;
            last = num.end();
            vector<int> v(first, last);
            node->right = sortedArrayToBST(v);
        }
        return node;
    }
};
