// Source : https://oj.leetcode.com/problems/binary-search-tree-iterator/
// Author : Hao Chen
// Date   : 2014-12-31

/********************************************************************************** 
 * 
 * Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.
 * 
 * Calling next() will return the next smallest number in the BST.
 * 
 * Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree. 
 * 
 * Credits:Special thanks to @ts for adding this problem and creating all test cases.
 *               
 **********************************************************************************/

/** 我的实现
考察非递归的中序遍历。 这道题本质上是写一个二叉树的中序遍历的迭代器。
内部设置一个栈， 初始化的时候， 存储从根节点到最左叶子节点的路径。 
在遍历的过程中， 每次从栈中弹出一个元素， 作为当前的返回结果， 
同时探测一下当前节点是否存在右孩子， 如果有， 则进入右孩子， 
并把从该右孩子到最左叶子节点的所有节点入栈。
*/
class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        while(root){
            stk.push(root);
            root = root->left;
        }
    }
    stack<TreeNode*> stk;
    /** @return the next smallest number */
    int next() {
        TreeNode* tmp= stk.top();
        stk.pop();
        TreeNode* p = tmp->right;
        while(p){
           stk.push(p);
           p = p->left; 
        }
        return tmp->val;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !stk.empty();
    }
};


class BSTIterator {
    private:
        vector<int> v; 
        int pos;
    public:
        //Travse the Tree in-order and covert it to an array
        BSTIterator(TreeNode *root) {
            pos = 0;
            vector<TreeNode*> stack;
            while(stack.size()>0 || root !=NULL) {
                if (root){
                    stack.push_back(root);
                    root = root->left;
                }else{
                    root = stack.back();
                    stack.pop_back();
                    v.push_back(root->val);
                    root = root->right;
                }
            }
        }

        /** @return whether we have a next smallest number */
        bool hasNext() {
            return pos < v.size();
        }

        /** @return the next smallest number */
        int next() {
            return v[pos++];
        }
};
