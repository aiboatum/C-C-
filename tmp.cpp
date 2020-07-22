#include <stdio.h>
#include <string.h>
#include <stdlib.h>
vector<int> m;
#include <vector>
using namespace std;
#define MAX_SIZE 20000

enum L_OR_R{
	L=1,
	R
};

struct  BTNode  {
    char data;
    struct BTNode *lchild;
    struct BTNode *rchild;
	struct BTNode *parent;    
};

struct BTNode * createBTree(char *str){
	struct BTNode *root = NULL;
	struct BTNode *p = root;

	int top=-1;	
	// 使用数组模拟stack
	struct BTNode* stack[MAX_SIZE];
	
	int j=0;
	int child=0;
	char ch = str[j];
	while(ch){
		switch (ch)
		{
		case '(':
			stack[++top] = p;
			child=L;
			break;
		case ')':
			top--;
			break;
		case ',':
			child=R;
			break;
		default:
			p=(struct BTNode *)malloc(sizeof(*p));
			p->data=ch;
			p->lchild=p->rchild=p->parent=NULL;
			if(!root)root=p;
			else if(child==L) {
				stack[top]->lchild=p;
				p->parent=stack[top];
			}
			else if(child==R){
				stack[top]->rchild=p;
				p->parent=stack[top];
			} 
			else {
			}
			
			break;
		}
		ch=str[++j];
	}
	return root;
}



struct BTNode * search(struct BTNode *root,char x){
	if(!root)return root;
	if(root->data==x)return root;
	struct BTNode *L=search(root->lchild,x);
	if(L)return L;

	struct BTNode *R=search(root->rchild,x);
	return R;
}

void Destroy(struct BTNode  *root){
	if(!root)return ;
	if(root->lchild)Destroy(root->lchild);
	if(root->rchild)Destroy(root->rchild);
	free(root);
	root=NULL;
}

void remove_node(struct BTNode *root,char x){
	struct BTNode * node=search(root,x);
	if(!node)return ;
	struct BTNode * p=node->parent;
	if(p&&node==p->lchild){
		p->lchild=NULL;
	}
	else if(p&&node==p->rchild){
		p->rchild=NULL;
	}
	else {
		
	}
	Destroy(node);
	node=NULL;
}




void DispBTree(struct BTNode  *root){
    if(root){
        printf("%c",root->data);
        if(root->lchild||root->rchild){
            printf("(");
            DispBTree(root->lchild);
            if(root->rchild)printf(",");
            DispBTree(root->rchild);
            printf(")");
        }
    }
}

void delet(int * &root){
    free(root);
    root=NULL;
}
int main(){

    int * p=(int *)malloc(sizeof(int));
    delet(p);
    printf("%d",p==NULL);
    return 0;
	// char mystr[]="A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";
	// struct BTNode *root=createBTree(mystr);
	// DispBTree(root);
	// printf("\n");
	// for(int i=0;i<strlen(mystr);++i){
	// 	if(mystr[i]=='('||mystr[i]==','||mystr[i]==')')continue;
	// 	remove_node(root,mystr[i]);
	// 	DispBTree(root);
	// 	printf("\n");
	// }
	// Destroy(root);
}