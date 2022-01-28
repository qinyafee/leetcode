// Source : https://oj.leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
// Author : Hao Chen
// Date   : 2014-07-10

/********************************************************************************** 
* 
* Given inorder and postorder traversal of a tree, construct the binary tree.
* 
* Note:
* You may assume that duplicates do not exist in the tree.
* 
*               
**********************************************************************************/

//链接：https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/solution/cong-zhong-xu-yu-hou-xu-bian-li-xu-lie-gou-zao-14/
// 时间复杂度：O(n)
// 空间复杂度：O(n)。我们需要使用 O(n) 的空间存储哈希表，以及 O(h)（其中 h 是树的高度）的空间表示递归时的栈空间。这里 h<n，所以总空间复杂度为 O(n)。

class Solution {
    int post_idx;
    unordered_map<int, int> idx_map;
public:
    TreeNode* helper(int in_left, int in_right, vector<int>& inorder, vector<int>& postorder){
        // 0.如果这里没有节点构造二叉树了，就结束。递归出口
        if (in_left > in_right) {
            return nullptr;
        }

        // 2.选择 post_idx 位置的元素作为当前子树根节点
        int root_val = postorder[post_idx];
        TreeNode* root = new TreeNode(root_val);

        // 3.根据 root 所在位置分成左右两棵子树
        int index = idx_map[root_val];

        // 下标减一
        post_idx--;
        // 构造右子树
        root->right = helper(index + 1, in_right, inorder, postorder);
        // 构造左子树
        root->left = helper(in_left, index - 1, inorder, postorder);
        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        // 从后序遍历的最后一个元素开始
        post_idx = (int)postorder.size() - 1;

        // 建立中序遍历（元素，下标）键值对的哈希表
        int idx = 0;
        for (auto& val : inorder) {
            idx_map[val] = idx++;
        }
        return helper(0, (int)inorder.size() - 1, inorder, postorder);
    }
};



/////////////////////////
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

TreeNode *buildTree(vector<int> &inorder, int in_offset, vector<int> &postorder, int post_offset, int n );

TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    return buildTree(inorder, 0, postorder, 0, postorder.size());
}

// n - how many number,  offset - start from where?
TreeNode *buildTree(vector<int> &inorder, int in_offset, vector<int> &postorder, int post_offset, int n ) {

    if ( n<=0 || postorder.size()<=0 || inorder.size()<=0 ) return NULL;

    TreeNode *root = new TreeNode(postorder[post_offset+n-1]);
    if ( n==1 ){
        return root;
    }

    //searching in inorder -- can be optimized by using <map>
    int i;
    for(i=in_offset; i<in_offset+n; i++){
        if (inorder[i] == postorder[post_offset+n-1]){
            break;
        }
    }

    //error: not found
    if (i == inorder.size()) return NULL;

    int left_n = i - in_offset;
    int right_n = in_offset + n - i - 1;
    root->left = buildTree(inorder, in_offset, postorder, post_offset, left_n );
    root->right = buildTree(inorder, i+1, postorder, post_offset+left_n, right_n);

    return root;
}

//cause the problem: memory limited error
TreeNode *buildTree2(vector<int> &inorder, vector<int> &postorder) {
    
    if (postorder.size()<=0 || inorder.size()<=0 ) return NULL;

    int post_n = postorder.size();
    TreeNode *root = new TreeNode(postorder[post_n-1]);
    if ( inorder.size()==1 && postorder.size()==1 ){
        return root;
    }

    //searching in inorder -- can be optimized by using <map>
    int i;
    for(i=0; i<inorder.size(); i++){
        if (inorder[i] == postorder[post_n-1]){
            break;
        }
    }

    //error: not found
    if (i == inorder.size()) return NULL;

    
    vector<int>   in(inorder.begin(), inorder.begin()+i);
    vector<int> post(postorder.begin(), postorder.begin()+i);
    if (in.size()>0) {
        root->left = buildTree(in, post);
    }

    in.clear();
    in.assign(inorder.begin()+i+1, inorder.end());
    post.clear();
    post.assign(postorder.begin()+i, postorder.end()-1);
    if (in.size()>0) {
        root->right = buildTree(in, post);
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
    int   in_order[]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    int post_order[]={'A', 'C', 'E', 'D', 'B', 'H', 'I', 'G', 'F'};
    vector<int>   inorder(  in_order,  in_order + 9 );
    vector<int> postorder( post_order, post_order + 9 );

    TreeNode* tree = buildTree(inorder, postorder);

    printTree_level_order(tree);
    printTree_pre_order(tree);
    printf("\n");
    printTree_in_order(tree);
    printf("\n");
    
    return 0;
}
