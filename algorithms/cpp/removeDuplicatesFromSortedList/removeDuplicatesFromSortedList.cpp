// Source : https://oj.leetcode.com/problems/remove-duplicates-from-sorted-list/
// Author : Hao Chen
// Date   : 2014-06-21

/********************************************************************************** 
* 
* Given a sorted linked list, delete all duplicates such that each element appear only once.
* 
* For example,
* Given 1->1->2, return 1->2.
* Given 1->1->2->3->3, return 1->2->3.
* 
*               
**********************************************************************************/
// my implm
// 双指针：
// 如果相等，prev不动，curr向前走
// 如果不等，两个都向前走
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* p1, *p2; //第二个* 容易忘
        p1=head;
        p2=head->next;
        while(p2){
            if(p1->val == p2->val) {// p1不动，p2向前走
                p1->next = p2->next;
                ListNode* tmp = p2;
                p2 = p2->next;
                delete tmp; //容易忘，释放内存
            } else { // p1、p2都向前走
                p1 = p2;
                p2 = p2->next;
            }
        }
        return head;
    }
};

#include <stdio.h>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *deleteDuplicates(ListNode *head) {

    for(ListNode *p=head; p && p->next; ){
        if (p->val == p->next->val){
            p->next = p->next->next;
            continue;
        }
        p=p->next;
    }
    return head;
}

void printList(ListNode* h)
{
    while(h!=NULL){
        printf("%d ", h->val);
        h = h->next;
    }
    printf("\n");
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


int main()
{
    int a[]={1,1,2,3,3};
    int b[]={1,1,1};

    printList(deleteDuplicates(createList(a, sizeof(a)/sizeof(int))));
    printList(deleteDuplicates(createList(b, sizeof(b)/sizeof(int))));
    return 0;
}

