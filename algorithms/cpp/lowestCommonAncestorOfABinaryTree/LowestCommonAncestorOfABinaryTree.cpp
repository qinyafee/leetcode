// my implm
// 自底向上(bottom-up)，看看是否能在 root 的左子树中找到 p 或 q ，再看看能否在右子树中找到
// 如果两边都能找到， 说明当前节点就是最近公共祖先
// 如果左边没找到， 则说明 p 和 q 都在右子树
// 如果右边没找到， 则说明 p 和 q 都在左子树
// https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/solution/236-er-cha-shu-de-zui-jin-gong-gong-zu-xian-hou-xu/
class Solution {
 public:
 	// 递归对二叉树进行先序遍历，当遇到节点 p 或 q 时返回。
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || root == p || root == q) return root;
    TreeNode* lson = lowestCommonAncestor(root->left, p, q);
    TreeNode* rson = lowestCommonAncestor(root->right, p, q);
    if (lson == nullptr) return rson;
    if (rson == nullptr) return lson;
    return root;
  }

	// 4种情况分别写：
  TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || root == p || root == q) return root;  // 终止条件
    TreeNode* lson = lowestCommonAncestor(root->left, p, q);
    TreeNode* rson = lowestCommonAncestor(root->right, p, q);
    if (lson == nullptr && rson == nullptr) return nullptr;  // 1.root 的左/右子树中都不包含p,q
    if (lson == nullptr) return rson;  // 3.p,q不在左子树中，返回 right
    if (rson == nullptr) return lson;  // 4.p,q不在右子树中，返回 left
    return root;  // 2. if(lson != null and rson != null), 说明 p,q 分列在 root的 异侧
  }
};

// clang-format off
// Source : https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
// Author : Hao Chen
// Date   : 2015-07-17

/********************************************************************************** 
 * 
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the 
 * tree.
 * 
 * According to the definition of LCA on Wikipedia: “The lowest common ancestor is 
 * defined between two nodes v and w as the lowest node in T that has both v and w as 
 * descendants (where we allow a node to be a descendant of itself).”
 * 
 *         _______3______
 *        /              \
 *     ___5__          ___1__
 *    /      \        /      \
 *    6      _2       0       8
 *          /  \
 *          7   4
 * 
 * For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example 
 * is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according 
 * to the LCA definition.
 *               
 *               
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
    bool findPath(TreeNode* root, TreeNode* p, vector<TreeNode*>& path) {
        if (root==NULL) return false;
        if (root == p) {
            path.push_back(p);
            return true;
        }
        
        path.push_back(root);
        if (findPath(root->left, p, path)) return true;
        if (findPath(root->right, p, path)) return true;
        path.pop_back();
        
        return false;
    }

    //Ordinary way, find the path and comapre the path.
    TreeNode* lowestCommonAncestor01(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        vector<TreeNode*> path1, path2;
        
        if (!findPath(root, p, path1)) return NULL;
        if (!findPath(root, q, path2)) return NULL;
        
        int len = path1.size() < path2.size() ? path1.size() : path2.size();
        TreeNode* result = root;
        for(int i=0; i<len; i++) {
            if (path1[i] != path2[i]) {
                return result;
            }
            result = path1[i];
        }
        return result;
    }
    
    //Actually, we can do the recursive search in one time
    TreeNode* lowestCommonAncestor02(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        //return if found or not found, return NULL if not found
        if (root==NULL || root == p || root == q) return root;
        
        //find the LCA in left tree
        TreeNode* left = lowestCommonAncestor02(root->left, p, q);
        //find the LCA in right tree
        TreeNode* right = lowestCommonAncestor02(root->right, p, q);
        
        //left==NULL means both `p` and `q` are not found in left tree.
        if (left==NULL) return right;
        //right==NULL means both `p` and `q` are not found in right tree.
        if (right==NULL) return left;
        // left!=NULL && right !=NULL, which means `p` & `q` are seperated in left and right tree.
        return root;
    }
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        srand(time(0));
        if (random()%2) {
            return lowestCommonAncestor02(root, p, q);
        }
        return lowestCommonAncestor01(root, p, q);
    }
};
