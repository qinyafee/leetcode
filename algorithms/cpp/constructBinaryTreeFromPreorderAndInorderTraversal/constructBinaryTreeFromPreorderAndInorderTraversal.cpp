// Source : https://oj.leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
// Author : Hao Chen
// Date   : 2014-07-09

/********************************************************************************** 
* 
* Given preorder and inorder traversal of a tree, construct the binary tree.
* 
* Note:
* You may assume that duplicates do not exist in the tree.
* 
*               
**********************************************************************************/
//链接：https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/solution/cong-qian-xu-yu-zhong-xu-bian-li-xu-lie-gou-zao-9/
//time O(n), space O(n)
class Solution {
private:
    unordered_map<int, int> index; //中序遍历<inorder[i], i>

public:
    TreeNode* myBuildTree(const vector<int>& preorder, const vector<int>& inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right) {
        //递归终止条件，当前的树中，一个元素也没有。
        if (preorder_left > preorder_right) {//等同于 inorder_left>inorder_right
            return nullptr;
        }
        
        // 1.前序遍历中的第一个节点就是根节点
        int preorder_root = preorder_left;
        // 2.在中序遍历中定位根节点
        int inorder_root = index[preorder[preorder_root]];
        
        // 3.先把根节点建立出来
        TreeNode* root = new TreeNode(preorder[preorder_root]);

        // 4.得到左子树中的节点数目
        int size_left_subtree = inorder_root - inorder_left; //因为不包含root，所以不+1
        
        // 5.递归地构造左子树，并连接到根节点
        // 先序遍历中「从 左边界+1 开始的 size_left_subtree」个元素就对应了中序遍历中「从 左边界 开始到 根节点定位-1」的元素
        root->left = myBuildTree(preorder, inorder, preorder_left + 1, preorder_left + size_left_subtree, inorder_left, inorder_root - 1);
        
        // 6.递归地构造右子树，并连接到根节点
        // 先序遍历中「从 左边界+1+左子树节点数目 开始到 右边界」的元素就对应了中序遍历中「从 根节点定位+1 到 右边界」的元素
        root->right = myBuildTree(preorder, inorder, preorder_left + size_left_subtree + 1, preorder_right, inorder_root + 1, inorder_right);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        // 构造哈希映射，帮助我们快速定位根节点
        for (int i = 0; i < n; ++i) {
            index[inorder[i]] = i;
        }
        return myBuildTree(preorder, inorder, 0, n - 1, 0, n - 1);
    }
};




#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode *buildTree(vector<int>& preorder, int& preidx, vector<int>& inorder);

TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    int preidx=0;
    return buildTree(preorder, preidx, inorder);
}

TreeNode *buildTree(vector<int>& preorder, int& preidx, vector<int>& inorder) {

    if (preorder.size()<=0 || inorder.size()<=0 ) return NULL;

    TreeNode *root = new TreeNode(preorder[preidx]);
    if (inorder.size()==1){
        return root;
    }

    int i;
    for(i=0; i<inorder.size(); i++){
        if (inorder[i] == preorder[preidx]){
            break;
        }
    }

    //error: not found
    if (i == inorder.size()) return NULL;

    if (preidx+1 >= preorder.size()){
        return root;
    }

    
    vector<int> v(inorder.begin(), inorder.begin()+i);
    if (v.size()>0) {
        preidx++;
        root->left = buildTree(preorder, preidx, v);
    }

    v.clear();
    v.assign(inorder.begin()+i+1, inorder.end());
    if (v.size()>0) {
        preidx++;
        root->right = buildTree(preorder, preidx, v);
    }

    return root;
}

void printTree_pre_order(TreeNode *root)
{
    if (root == NULL){
        printf("# ");
        return;
    }
    printf("%c ", root->val );

    printTree_pre_order(root->left);
    printTree_pre_order(root->right);
}

void printTree_in_order(TreeNode *root)
{
    if (root == NULL){
        printf("# ");
        return;
    }

    printTree_in_order(root->left);
    printf("%c ", root->val );
    printTree_in_order(root->right);
}


void printTree_level_order(TreeNode *root)
{
    queue<TreeNode*> q;
    q.push(root);
    while (q.size()>0){
        TreeNode* n = q.front();
        q.pop();
        if (n==NULL){
            printf("# ");
            continue;
        }
        printf("%c ", n->val);
        q.push(n->left);
        q.push(n->right);
    }
    printf("\n");
}


int main()
{
    int pre_order[]={'F', 'B', 'A', 'D', 'C', 'E', 'G', 'I', 'H'};
    int  in_order[]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    vector<int> preorder( pre_order, pre_order + 9 );
    vector<int>  inorder(  in_order,  in_order + 9 );

    TreeNode* tree = buildTree(preorder, inorder);

    printTree_level_order(tree);
    printTree_pre_order(tree);
    printf("\n");
    printTree_in_order(tree);
    printf("\n");
    
    return 0;
}
