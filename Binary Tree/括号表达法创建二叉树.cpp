/*---------------------------------------------------------
*		根据括号表示法：1.创建二叉树	2. 搜索给定结点，并删除该结点
*		!删除子树的操作，应当返回根节点。	
*---------------------------------------------------------*/

#include <iostream>
#include <string>
#include <stack>
#include <stdio.h>

using namespace std;

enum Lchild_OR_Rchild {
	L=1,
	R
};

struct  BTNode {
	char data;
	struct BTNode* lchild;
	struct BTNode* rchild;
	struct BTNode* parent;	// 为了更方便的删除子树
	BTNode(const char & ch):
		data(ch),
		lchild(nullptr),
		rchild(nullptr)
		{}
};

void Destroy(struct BTNode* root);

struct BTNode* createBTree(string &str) {
	struct BTNode* root = nullptr;
	struct BTNode* p = root;

	int child=0;
	stack<BTNode *> s;
	for(auto ch:str){
		switch (ch)
		{
		case '(':
			s.push(p);
			child = L;	// 表明接下来的结点是前一个（栈顶）结点的左孩子结点
			break;
		case ')':
			s.pop();
			break;
		case ',':
			child = R;	// 表明接下来的结点是。。。。。的右孩子结点
			break;
		default:
			p=new BTNode(ch);
			if (!p) {
				printf("创建结点失败!\n");
				Destroy(root);
				exit(1);
			}

			if (!root)root = p;
			else if (child == L) {
				s.top()->lchild=p;
				p->parent=s.top();
			}
			else if (child == R) {
				s.top()->rchild=p;
				p->parent=s.top();
			}
			else {
				// do nothing
			}
			break;
		}
	}
	return root;
}



struct BTNode* search(struct BTNode* root, char x) {
	if (!root)return root;
	if (root->data == x)return root;
	struct BTNode* L = search(root->lchild, x);
	if (L)return L;

	struct BTNode* R = search(root->rchild, x);
	return R;
}

void Destroy(struct BTNode* root) {
	if (!root)return;
	if (root->lchild)Destroy(root->lchild);
	if (root->rchild)Destroy(root->rchild);
	free(root);
}


/***
 * 	删除子树应当返回根节点，以便及时更新root
 *  当删除node等于root时，应当将root返回NULL，以防再次调用destroy(root)时，再次free，而出现错误。
 **/
struct BTNode* remove_node(struct BTNode* root, char x) {
	struct BTNode* node = search(root, x);
	if (!node)return root;
	struct BTNode* p = node->parent;
	if (p && node == p->lchild) {
		p->lchild = nullptr;
	}
	if (p && node == p->rchild) {
		p->rchild = nullptr;
	}

	// special case:当删除的结点是root结点时，应当将其置为NULL
	if(node==root) root=nullptr;
	Destroy(node);
	return root;
}




void DispBTree(struct BTNode* root) {
	if (root) {
		printf("%c", root->data);
		if (root->lchild || root->rchild) {
			printf("(");
			DispBTree(root->lchild);
			if (root->rchild)printf(",");
			DispBTree(root->rchild);
			printf(")");
		}
	}
}

int main() {
	string str ="A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";
	struct BTNode* root = createBTree(str);
	DispBTree(root);
	printf("\n");
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == '(' || str[i] == ',' || str[i] == ')')continue;
		root = remove_node(root, str[i]);
		DispBTree(root);
		printf("\n");
	}
	Destroy(root);
}