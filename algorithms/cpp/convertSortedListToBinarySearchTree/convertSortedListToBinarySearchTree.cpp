// my implm
// bottom-up 自底向上递归， 中序遍历
// https://leetcode-cn.com/problems/convert-sorted-list-to-binary-search-tree/solution/you-xu-lian-biao-zhuan-huan-er-cha-sou-suo-shu-1-3/
// 时间复杂度O(n)， 空间复杂度O(logn)
class Solution {
 public:
  TreeNode* sortedListToBST(ListNode* head) {
    int len = 0;
    ListNode* p = head;
    while (p) {
      len++;
      p = p->next;
    }
    return buildTree(head, 0, len - 1);
  }

 private:
  TreeNode* buildTree(ListNode*& head, int left, int right) {
    if (left > right) {
      return nullptr; //遍历到的位置对应着一个空节点
    }
    int mid = left + (right - left) / 2;
    TreeNode* root = new TreeNode();  // 占位节点
    root->left = buildTree(head, left, mid - 1);
    root->val = head->val;  // 遍历到中间节点，填值
    head = head->next;
    root->right = buildTree(head, mid + 1, right);
    return root;
  }
};

// clang-format off

// Source : https://oj.leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
// Author : Hao Chen
// Date   : 2014-07-03

/********************************************************************************** 
* 
* Given a singly linked list where elements are sorted in ascending order, 
* convert it to a height balanced BST.
*               
**********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


TreeNode* sortedListToBST(int low, int high, ListNode*& head);

TreeNode *sortedListToBST(ListNode *head) {
    int len = 0;
    
    for(ListNode* p=head; p!=NULL; p=p->next){
        len++;
    }
    return sortedListToBST(0, len-1, head);
}

TreeNode* sortedListToBST(int low, int high, ListNode*& head) {
    if (low>high || head==NULL) return NULL;

    int mid = low + (high - low)/2;

    TreeNode* leftNode = sortedListToBST(low, mid-1, head);

    TreeNode* node = new TreeNode(head->val);
    node->left = leftNode;
    head = head->next;

    TreeNode* rightNode = sortedListToBST(mid+1, high, head);
    node->right = rightNode;

    return node;
}

void printTree_level_order(TreeNode *root)
{
    queue<TreeNode*> q;
    q.push(root);
    while (q.size()>0){
        TreeNode* n = q.front();
        q.pop();
        if (n==NULL){
            cout << "# ";
            continue;
        }
        cout << n->val << " ";
        q.push(n->left);
        q.push(n->right);
    }
    cout << endl;
}

ListNode* createList(int a[], int n)
{
    ListNode *head=NULL, *p=NULL;
    for(int i=0; i<n; i++){
        if (head == NULL){
            head = p = new ListNode(a[i]);
        }else{
            p->next = new ListNode(a[i]);
            p = p->next;
        }
    }
    return head;
}

void printList(ListNode* h)
{
    while(h!=NULL){
        printf("%d -> ", h->val);
        h = h->next;
    }
    printf("NULL\n");
}


int main(int argc, char** argv)
{
    int n = 8;
    if (argc>1){
        n = atoi(argv[1]);
    }
    int *a = new int[n];
    for(int i=0; i<n; i++){
        a[i]=i+1;
    }
    ListNode* head = createList(a, n);
    printList(head);
    TreeNode* root = sortedListToBST(head); 
    printTree_level_order(root);
    delete[] a; 

    return 0;
}

