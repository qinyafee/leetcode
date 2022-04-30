// 116. 此题是完美二叉树，用117.的解法就行
// 层次遍历可以解，但是空间复杂度不是O(1)
// 使用已建立的 next指针，已经保存了每层队列顺序。

// 递归
// 时间复杂度O(n)， 空间复杂度O(1)
class Solution {
 public:
  Node* connect(Node* root) {
    if (root == nullptr) return nullptr;
    Node dummy(-1);  // 虚拟节点，方便找到下一层的最左边节点
    for (Node *curr = root, *prev = &dummy; curr; curr = curr->next) {  // 遍历当前层
      if (curr->left != nullptr) {                                      // 建立下一层的next
        prev->next = curr->left;
        prev = prev->next;
      }
      if (curr->right != nullptr) {
        prev->next = curr->right;
        prev = prev->next;
      }
    }
    connect(dummy.next);  // 遍历下一层，从最左边节点开始
    return root;
  }
};

// 迭代
// 时间复杂度O(n)， 空间复杂度O(1)
class Solution {
 public:
  void connect(Node* root) {
    while (root) {
      Node* next = nullptr;  // the first node of next level
      Node* prev = nullptr;  // previous node on the same level
      for (; root; root = root->next) {
        if (!next) next = root->left ? root->left : root->right;
        if (root->left) {
          if (prev) prev->next = root->left;
          prev = root->left;
        }
        if (root->right) {
          if (prev) prev->next = root->right;
          prev = root->right;
        }
      }
      root = next;  // turn to next level
    }
  }
};

// clang-format off
// Source : https://oj.leetcode.com/problems/populating-next-right-pointers-in-each-node/
// Author : Hao Chen
// Date   : 2014-06-19

/********************************************************************************** 
* 
* Given a binary tree
* 
*     struct Node {
*       Node *left;
*       Node *right;
*       Node *next;
*     }
* 
* Populate each next pointer to point to its next right node. 
* If there is no next right node, the next pointer should be set to NULL.
* 
* Initially, all next pointers are set to NULL.
* 
* Note:
* 
* You may only use constant extra space.
* You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
* 
* For example,
* Given the following perfect binary tree,
* 
*          1
*        /  \
*       2    3
*      / \  / \
*     4  5  6  7
* 
* After calling your function, the tree should look like:
* 
*          1 -> NULL
*        /  \
*       2 -> 3 -> NULL
*      / \  / \
*     4->5->6->7 -> NULL
* 
*               
**********************************************************************************/

#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

/**
 * Definition for binary tree with next pointer.
 */
struct Node {
    int val;
    Node *left, *right, *next;
    Node(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
};


void connect(Node *root) {

    if (root==NULL){
        return;
    }
    if (root->left && root->right){
        root->left->next = root->right;
    }
    if (root->next && root->right){
        root->right->next = root->next->left;
    }
    connect(root->left);
    connect(root->right);

}

void connect1(Node *root) {

    if (root==NULL){
        return;
    }

    vector<Node*> v;    
    v.push_back(root);
    int i = 0;
    
    while (i < v.size()){
        if (v[i]->left){
            v.push_back(v[i]->left);
        }
        if (v[i]->right) {
            v.push_back(v[i]->right);
        }
        i++;
    }

    i=1;
    while(i<v.size()){
        for (int j=i-1; j<2*(i-1); j++){
           v[j]->next = v[j+1]; 
        }
        i *= 2; 
    }

}

void connect2(Node *root) {

    if (root==NULL){
        return;
    }
    
    vector<Node*> v;

    v.push_back(root);
    
    while(v.size()>0){
        
        if (root->left && root->right && root->left->next == NULL ) {
            root->left->next = root->right;
            
            if (root->next){
                root->right->next = root->next->left;
            }
            
            v.push_back(root->right);
            v.push_back(root->left);
        }
        root=v.back();
        v.pop_back();
    }
}

void connect3(Node *root) {
    if(root == NULL) return;

    queue<Node*> q;
    Node *prev, *last;
    prev = last = root;

    q.push(root);
    while(!q.empty()) {
        Node* p = q.front();
        q.pop();

        prev->next = p;
        if(p->left ) q.push(p->left);
        if(p->right) q.push(p->right);

        if(p == last) { // meets last of current level
            // now, q contains all nodes of next level
            last = q.back();
            p->next = NULL; // cut down.
            prev = q.front();
        }
        else {
            prev = p;
        }
    }
}

// constant space
// key point: we can use `next` pointer to represent
//      the buffering queue of level order traversal.
void connect4(Node *root) {
    if(root == NULL) return;

    Node *head, *tail;
    Node *prev, *last;

    head = tail = NULL;
    prev = last = root;

#define push(p) \
    if(head == NULL) { head = tail = p; } \
    else { tail->next = p; tail = p; }

    push(root);
    while(head != NULL) {
        Node* p = head;
        head = head->next; // pop

        prev->next = p;
        if(p->left ) push(p->left);
        if(p->right) push(p->right);

        if(p == last) {
            last = tail;
            p->next = NULL; // cut down.
            prev = head;
        }
        else {
            prev = p;
        }
    }
#undef push
}

void printTree(Node *root){
    if (root == NULL){
        return;
    }
    printf("[%d], left[%d], right[%d], next[%d]\n", 
            root->val, 
            root->left ? root->left->val : -1, 
            root->right ? root->right->val : -1, 
            root->next?root->next->val : -1 );    

    printTree(root->left);
    printTree(root->right);
 
}

int main()
{
    const int cnt = 7; 
    Node a[cnt];
    for(int i=0; i<cnt; i++){
        a[i].val = i+1;
    } 

    
    for(int i=0, pos=0;  pos < cnt-1; i++ ){
        a[i].left = &a[++pos];
        a[i].right = &a[++pos];
    }
    
    connect(&a[0]); 

    printTree(&a[0]);

    return 0;
}
