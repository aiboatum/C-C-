
/*----------------------------------------------------
*       c++实现huffman编码
*       1.使用priority_queue实现Huffman树的构建
*       2.通过map完成编码和解码的映射
*----------------------------------------------------*/

#include <iostream>
#include <vector>
#include <fstream>  // 文件操作相关
#include <string>
#include <queue>    // priority_queue
#include <sstream>
#include <map>
using namespace std; 


// Huffman树结点定义
struct HuffmanTreeNode  { 
    // 频率默认使用double
    // 如需要可使用int类型
    using freq_type = int; 
    using data_type = char; 
	data_type data; 
	freq_type freq; 

	HuffmanTreeNode  *left;
    HuffmanTreeNode  *right; 

    // 构造函数
	HuffmanTreeNode (data_type data, freq_type freq) :
        left(nullptr),
        right(nullptr),
        data(data),
        freq(freq)
        {}
}; 

class HuffmanTree{
private:
	HuffmanTreeNode *_root;
    // 字符和huffman编码之间的映射
    map<char, string> codes;
    // 记录每个字符出现的次数
    map<char,int> freqs;

	void destroy(HuffmanTreeNode *root){
		if(!root)return ;
		if(root->left)destroy(root->left);
		if(root->right)destroy(root->right);
		delete root;
	}

public:
	HuffmanTree():_root(nullptr){}
    // 根据输入的字符串str构建huffman树
	HuffmanTree(string str){
        for(int i=0;i<str.size();++i)freqs[str[i]]++;
        

		HuffmanTreeNode *left,*right,*top;

		auto cmp=[](const HuffmanTreeNode  *lhs,const HuffmanTreeNode  * rhs)->bool{
			return lhs->freq>rhs->freq;
		};
    	// 构建一个最小堆，并将data中的元素都插入进去
		priority_queue<HuffmanTreeNode  *, vector<HuffmanTreeNode  *>, decltype(cmp)> pq(cmp);

        for(auto iter:freqs){
            pq.push(new HuffmanTreeNode(iter.first,iter.second));
        }

		while (pq.size() != 1) { 
        	// 取出freq最小的两个结点
			left = pq.top(); 
			pq.pop(); 
			right = pq.top(); 
			pq.pop(); 
			// 由以上两个结点作为左右子孩子结点，
			// 并构建一个"用不到"的中间结点，该结点以特殊字符标记
			// 该结点的freq是left和right的相加
			top = new HuffmanTreeNode ('#', left->freq + right->freq); 
			top->left = left; 
			top->right = right; 
			pq.push(top); 
		} 

		// 返回的即构造的huffman树的根节点
		_root=pq.top();

        // 构建字符和huffman编码之间的映射
        _HuffmanCodesToString(_root,"");
	}
	void _HuffmanCodesToString(HuffmanTreeNode * root, string str);

    string HuffmanTreeToString();

    map<char,int> get_freqs()const{return freqs;}
    map<char,string> get_codes()const{return codes;}

    string encode(string str);
    string decode(string str);
    ~HuffmanTree(){destroy(_root);}

};

// 建立编码和原字符的映射
inline void HuffmanTree::_HuffmanCodesToString(HuffmanTreeNode * root, string str){ 
	if (!root) return; 
	if (root->data != '#')
        codes[root->data]=str; 
	_HuffmanCodesToString(root->left, str + "0"); 
	_HuffmanCodesToString(root->right, str + "1"); 
} 

// 根据输入的str，返回其编码后的01串
inline string HuffmanTree::encode(string str){
    string ret;
    for(auto ch:str)ret+=codes[ch];
    return ret;
}

// 借助构建好的huffman树decode
inline string HuffmanTree::decode(string str){
    string ret;
    HuffmanTreeNode *cur=_root;
    for(int i=0;i<str.size();++i){
        if(str[i]=='0')cur=cur->left;
        else cur=cur->right;

        if(!cur->left&&!cur->right){
            ret+=cur->data;
            cur=_root;
        }
    }
    return ret;
}

// huffman树序列化
inline string HuffmanTree::HuffmanTreeToString() {
    if (_root == nullptr) {
      return "[]";
    }
    string output = "";
    queue<HuffmanTreeNode*> q;
    q.push(_root);
    while(!q.empty()) {
        HuffmanTreeNode* node = q.front();
        q.pop();

        if (node == nullptr) {
          output += "null, ";
          continue;
        }

        output += node->data + ", ";
        q.push(node->left);
        q.push(node->right);
    }
    return "[" + output.substr(0, output.length() - 2) + "]";
}


int main() { 
    string str = "geeksforgeeks"; 
    string encodedString, decodedString; 
    HuffmanTree huffman(str);
    cout << "Character With there Frequencies:\n"; 
    auto codes=huffman.get_codes();
    for (auto v=codes.begin(); v!=codes.end(); v++) 
        cout << v->first <<' ' << v->second << endl; 
  
    encodedString=huffman.encode(str); 
  
    cout << "\nEncoded Huffman data:\n" << encodedString << endl; 
  
    decodedString = huffman.decode(encodedString);
    cout << "\nDecoded Huffman Data:\n" << decodedString << endl; 
	return 0; 
} 
