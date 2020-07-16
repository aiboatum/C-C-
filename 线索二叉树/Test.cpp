  
#include "BInaryTreeThread.h"
#include "BinartTree.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
using namespace std;

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
	unordered_map<int,int> index_map;
	for(int i=0;i<inorder.size();++i)index_map[inorder[i]]=i;
	
	stack<TreeNode *> s;
	TreeNode *root=(preorder.size()<1)?nullptr:new TreeNode(preorder[0]);
	s.push(root);
	TreeNode *cur=nullptr;
	
	for(int i=1;i<preorder.size();++i){
		cur=s.top();
		TreeNode *node=new TreeNode(preorder[i]);
		if(index_map[preorder[i]]<index_map[cur->val]){
			cur->left=node;
			s.push(node);
		}
		else{
			// find the parent node where the node preorder[i] belongs to
			TreeNode *parent=nullptr;
			while(!s.empty()){
				cur=s.top();
				if(index_map[cur->val]>index_map[preorder[i]])break;
				parent=cur;
				s.pop();
			}
			parent->right=node;
			s.push(node);
		}
		
	}
	return root;
}


// string到int数组的转换
vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

// string到普通二叉树结点的转换
TreeNode* stringToTreeNode(string input) {
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    if (!input.size()) {
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
            node->left = new TreeNode(leftNumber);
            nodeQueue.push(node->left);
        }

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int rightNumber = stoi(item);
            node->right = new TreeNode(rightNumber);
            nodeQueue.push(node->right);
        }
    }
    return root;
}

// 普通二叉树结点到string的格式转换
string treeNodeToString(TreeNode* root) {
    if (root == nullptr) {
      return "[]";
    }

    string output = "";
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (node == nullptr) {
          output += "null, ";
          continue;
        }

        output += to_string(node->val) + ", ";
        q.push(node->left);
        q.push(node->right);
    }
    return "[" + output.substr(0, output.length() - 2) + "]";
}

// 注意：一个树只可以被线索化一次
int main() {
    string line;
    while (getline(cin, line)) {
        vector<int> preorder = stringToIntegerVector(line);
        getline(cin, line);
        vector<int> inorder = stringToIntegerVector(line);
        
        TreeNode* ret = buildTree(preorder, inorder);

		cout<<"Construct Binary Tree from Preorder and Inorder Traversal:"<<endl;
        string out = treeNodeToString(ret);
        cout << out << endl;

		BinaryTreeThread treadTree(out);
		treadTree.PostOrderThreading();
		treadTree.PostOrderNonR();
    }
    return 0;
}