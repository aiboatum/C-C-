#include <assert.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
using namespace std;

enum PointerTag
{
    THREAD, // 标志该节点被线索化
    LINK    // 标志该节点是普通连接节点
};

// 线索树结点
struct BinaryTreeThreadNode{
	int _data;  
	BinaryTreeThreadNode* _left;
	BinaryTreeThreadNode* _right;
    BinaryTreeThreadNode* _parent;   // 后序需要用到
	PointerTag _leftTag;  
	PointerTag _rightTag;

	BinaryTreeThreadNode(const int& x = int())
		: _data(x)
		, _left(nullptr)
		, _right(nullptr)
        ,_parent(nullptr)
		, _leftTag(LINK)
		, _rightTag(LINK)
	{}
};

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

// string转换为树，返回根节点
// 用于反序列化，构建树
BinaryTreeThreadNode * stringToTreeThreadNode(string input) {
    using TreeNode = BinaryTreeThreadNode ;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    if (!input.size()) {    // 处理edge case
        return nullptr;
    }

    string item;
    stringstream ss;
    ss.str(input);

    getline(ss, item, ',');
    TreeNode* root = new TreeNode(stoi(item));
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);

    while (true) {
        TreeNode* node = nodeQueue.front();
        nodeQueue.pop();

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int leftNumber = stoi(item);
            node->_left = new TreeNode(leftNumber);
            node->_left->_parent=node;
            nodeQueue.push(node->_left);
        }

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int rightNumber = stoi(item);
            node->_right = new TreeNode(rightNumber);
            node->_right->_parent=node;
            nodeQueue.push(node->_right);
        }
    }
    return root;
}


// 树序列化，转换为string形式，方便输出
string treeNodeToString(BinaryTreeThreadNode * root) {
    if (root == nullptr) {
      return "[]";
    }

    string output = "";
    queue<BinaryTreeThreadNode *> q;
    q.push(root);
    while(!q.empty()) {
        BinaryTreeThreadNode* node = q.front();
        q.pop();

        if (node == nullptr) {
          output += "null, ";
          continue;
        }

        output += to_string(node->_data) + ", ";
        q.push(node->_left);
        q.push(node->_right);
    }
    return "[" + output.substr(0, output.length() - 2) + "]";
}

// 线索树
class BinaryTreeThread{
	typedef BinaryTreeThreadNode Node;
public:
	BinaryTreeThread()
		: _root(nullptr)
	{}
    
    BinaryTreeThread(string &line){
        _root = stringToTreeThreadNode(line);
    }

    // 中序遍历线索二叉树，递归版本
	void InOrder(){
		_inOrder(_root);
		cout << endl;
	}

    // 中序遍历线索二叉树，非递归版本
	void InOrderNonR(){
        cout<<"TreadTree inorder traverse:"<<endl;
		Node *cur = _root;
		while (cur)
		{
			while (cur->_leftTag == LINK)
				cur = cur->_left;
			cout << cur->_data << " ";
			while (cur && cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				if (cur)
					cout << cur->_data << " ";
			}
			if (cur->_rightTag == LINK)
				cur = cur->_right;
		}
		cout << endl;
	}

    // 中序线索化
	void InOrderThreading(){
		Node *prev = nullptr;
		_inOrderThreading(_root, prev);
	}
    
    // 先序遍历，递归版本
	void PreOrder(){
		_preOrder(_root);
		cout << endl;
	}
    // 先序遍历，非递归版本
	void PreOrderNonR(){
        cout<<"TreadTree preoder traverse:"<<endl;
		Node *cur = _root;
		while (cur)
		{
			while (cur->_leftTag == LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			cur = cur->_right;
		}
		cout << endl;
	}

	void PreOrderThreading(){
		Node *prev = nullptr;
		_preOrderThreading(_root, prev);
	}

    // 后序遍历
	void PostOrder(){
        cout<<"post order:"<<endl;
        _PostOrder(_root);
        cout<<endl;
    }

    void PostOrderNonR(){
        cout<<"TreadTree postorder traverse:"<<endl;
        if(_root==nullptr) return ;

        Node * cur=_root;
        Node * pre=nullptr;
        Node * par=nullptr;
        while(cur){
            // 最左侧的子结点
            while(cur->_left&&cur->_leftTag==LINK && cur->_left!=pre){
                cur=cur->_left;
            }


            while(cur && cur->_rightTag==THREAD){
                cout<<cur->_data<<" ";
                pre=cur;
                cur=cur->_right;
            }

            if(cur==_root&&cur->_right==pre){
                cout<<cur->_data<<endl;
                return ;
            }

            while(cur &&cur->_right==pre){
                cout<<cur->_data<<" ";
                pre=cur;
                cur=cur->_parent;
            }

            if(cur&& cur->_rightTag==LINK){
                cur=cur->_right;
            }
        }
        cout<<endl;
    }
    void PostOrderThreading(){
        Node *prev=nullptr;
        _PostOrderTreading(_root,prev);
    }
private:

    // 中序线索化实现
	void _inOrderThreading(Node *cur, Node *& prev){
		if (!cur)return;

        // 递归线索化左子树
		if (cur->_leftTag == LINK)
			_inOrderThreading(cur->_left, prev);
		
        // 处理当前结点
		if (cur->_left == nullptr){
			cur->_left = prev;
			cur->_leftTag = THREAD;
		}

        // 只有该结点的pre结点不为空，且其右孩子结点为空时，将其连接
		if (prev && prev->_right == nullptr){
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}

		prev = cur;
        // 递归线索化右子树
		if (cur->_rightTag == LINK)
			_inOrderThreading(cur->_right, prev);
	}

    // 先序线索化实现
	void _preOrderThreading(Node *cur, Node *& prev){
		if (cur == nullptr)
			return;
    
        // 先处理当前结点
		if (cur->_left == nullptr)
		{
			cur->_left = prev;
			cur->_leftTag = THREAD;
		}
        
		if (prev && prev->_right == nullptr)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}

		prev = cur;
        // 递归处理左子树
		if (cur->_leftTag == LINK)
			_preOrderThreading(cur->_left, prev);
		// 递归处理右子树
		if (cur->_rightTag == LINK)
			_preOrderThreading(cur->_right, prev);
	}

    // 后序线索化实现
    void _PostOrderTreading(Node *cur,Node * &prev){
        if(!cur)return;

        // 递归线索化左子树
        _PostOrderTreading(cur->_left,prev);
        
        if(cur->_rightTag==LINK)// 不满足此条件，说明右子树无需线索化
            _PostOrderTreading(cur->_right,prev);
        
        // 处理当前结点
        if(cur->_left==nullptr){
            cur->_left=prev;
            cur->_leftTag=THREAD;
        }
        if(prev && prev->_right == nullptr){
            prev->_right=cur;
            prev->_rightTag=THREAD;
        }
        prev=cur;
    }
    // 递归中序遍历实现
	void _inOrder(Node* root)
	{
		if (root == NULL)
			return;

		if (root->_leftTag == LINK)
			_inOrder(root->_left);

		cout << root->_data << " ";

		if (root->_rightTag == LINK)
			_inOrder(root->_right);
	}

    // 递归后序遍历实现
    void _PostOrder(Node *root){
        if(!root)return ;
        _PostOrder(root->_left);
        _PostOrder(root->_right);
        cout<<root->_data<<" ";
    }
    // 递归先序遍历实现
	void _preOrder(Node *root)
	{
		if (root == NULL)
			return;
		cout << root->_data << " ";
		if (root->_leftTag == LINK)
			_preOrder(root->_left);
		if (root->_rightTag == LINK)
			_preOrder(root->_right);
	}
public:
	Node *_root;
};

