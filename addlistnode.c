#include <stdio.h>
#include <stdlib.h>
#define  SIZE 3
//Definition for singly-linked list.带头结点，头结点的val值为-1
typedef struct ListNode {
	int val;
	struct ListNode *next;
}ListNode;

struct ListNode *addTwoNumbers(struct ListNode *, struct ListNode *);
void Init(struct ListNode *);
void destroy(struct ListNode *);
void addnode(struct ListNode *, int);
void Init(struct ListNode *l) {
	l->val = -1;
	l->next = NULL;
}
struct ListNode *addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	struct ListNode *p1 = l1->next, *p2 = l2->next;//两个工作节点
	int tag = 0;//标记是否有进位
	if (!p1)return l2;
	if (!p2)return l1;
	struct ListNode * sum = malloc(sizeof(struct ListNode));
	Init(sum);
	sum->val=(p1->val + p2->val+tag ) % 10;
    tag = ((p1->val + p2->val)>9) ? 1 : 0;
    sum->next=NULL;
    if(!p1->next&&!p2->next){
    if((p2->val+p1->val+tag)>9){
	addnode(sum,(p2->val+tag)%10);
	addnode(sum,tag);
    }
	}
    p1 = p1->next;
    p2 = p2->next;
	while (p1&&p2) {

		addnode(sum, (p1->val + p2->val+tag ) % 10);
		tag = ((p1->val + p2->val)>9) ? 1 : 0;
		p1 = p1->next;
		p2 = p2->next;
	}
	while (p1) {//p1较长
		if(p1->next)//最后一个节点特殊处理
		addnode(sum, (p1->val + tag) % 10);
		else{ 
		if((p1->val+tag)>9){
		addnode(sum,(p1->val+tag)%10);
		addnode(sum,tag);
		}
		else
		addnode(sum,p1->val+tag);
		}
		p1=p1->next;
	}
	while (p2) {
		if(p2->next)
		addnode(sum, (p2->val + tag) % 10);
		else{ 
		if((p2->val+tag)>9){
		addnode(sum,(p2->val+tag)%10);
		addnode(sum,tag);
		}
		else
		addnode(sum,p2->val+tag);
		}
		tag = ((p2->val + tag)>9) ? 1 : 0;
		p2=p2->next;
	}
	//sum->next=NULL;
	return sum;
}

void destroy(struct ListNode * l) {
	//ListNode *p=l;
	while (l) {
		struct ListNode *p = l;
		l = l->next;
		free(p);
	}
	free(l);
}
void addnode(struct ListNode * l, int val) {
	struct ListNode *p = malloc(sizeof(struct ListNode));
    struct ListNode *r = l;
	while (r->next)r= r->next;
	p->val=val;
	p->next=r->next;
	r->next=p;
	r=p;
	/*头插
	// p->val = val;
	// p->next = l->next;
	// l->next = p;
	*/
	//free(r);//不能加free（r)
}
int main(void) {
	ListNode *l1 = malloc(sizeof(struct ListNode));
	Init(l1);
	int temp[SIZE]={0};
	for (int i = 0; i<1; i++) {
		scanf("%d", &temp[i]);
		addnode(l1, temp[i]);
	}

	ListNode *l2 = malloc(sizeof(struct ListNode));
	Init(l2);

	for (int i = 0; i<1; ++i) {
		scanf("%d", &temp[i]);
		addnode(l2, temp[i]);
	}
	ListNode *t = addTwoNumbers(l1, l2);
	struct ListNode *p = t->next;
	while (p) {

		(p->next)?printf("%d->", p->val):printf("%d",p->val);
		p = p->next;
	}
	free(p);
	destroy(l1);
	destroy(l2);
	destroy(t);
	return 0;

}