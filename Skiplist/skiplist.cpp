/*------------------------------------------------------------
*       C++实现skiplist
*       reference: https://www.geeksforgeeks.org/skip-list/?ref=lbp
*       文档见skiplist.md介绍skiplist
*-------------------------------------------------------------*/
#include <iostream>
#include <string.h>
#include <time.h>
#include <vector>
using namespace std; 

// skiplist中的结点定义
struct SkipListNode { 
	int key; 
    // 每个skiplist结点维持一个forward数组，该数组大小和该结点的高度有关
    // forward[i]存储一个指向skplist结点的指针，即当前结点在level i，其下一个结点位置
    vector<SkipListNode *> forward;
	SkipListNode(int key, int level){
        this->key = key;
        this->forward.resize(level + 1,NULL);
    } 
}; 

// skiplist定义
class SkipList {
private: 
	// skiplist允许的最大高度 
	int MAXLVL; 

    // P就是一个概率，每一个结点有概率P，向上增加一个高度
	// P is the fraction of the nodes with level 
	// i pointers also having level i+1 pointers 
	float P; // 一般设置为0.5

    // 当前skiplist中除去头结点，其余结点最高的level
	int level; 

	// pointer to header node 
	SkipListNode *header; 
    void freeNode(SkipListNode *root){
        if(!root)return ;
        // 由于最底层的level中，每个SkipListNode是完整的链表
        // 每个结点中的vector自己会回收资源
        // 因此我们只需要针对forward[0]即可
        freeNode(root->forward[0]);
        root->forward[0]=nullptr;
        delete root;
        root=nullptr;
    }
public: 
	SkipList(int, float); 
    ~SkipList(){
        freeNode(header);
        header=nullptr;
    }
	int randomLevel(); 
	SkipListNode* createNode(int, int); 
	void insertElement(int); 
    void deleteElement(int);
	void searchElement(int);
	void displayList(); 
}; 

SkipList::SkipList(int MAXLVL, float P) { 
	this->MAXLVL = MAXLVL; 
	this->P = P; 
	level = 0; 
    // heard结点起辅助作用，不存储真正的结点 
	header = new SkipListNode(-1, MAXLVL); 
}; 

int SkipList::randomLevel() 
{ 
	float r = (float)rand()/RAND_MAX; 
	int lvl = 0; 
	while (r < P && lvl < MAXLVL) 
	{ 
		lvl++; 
		r = (float)rand()/RAND_MAX; 
	} 
	return lvl; 
}; 

SkipListNode* SkipList::createNode(int key, int level) 
{ 
	SkipListNode *n = new SkipListNode(key, level); 
	return n; 
}; 


// 插入操作
void SkipList::insertElement(int key){
	SkipListNode *current = header; 
    // update的作用：是将新插入的结点正确连接到各层链表的辅助数组
    vector<SkipListNode *> update(MAXLVL+1,NULL);

	// 从hearder开始搜索，从最高层依次向最底层搜索
	// 如果node的next（即响应的forward[i]）的key大于等于新插入的key
	// 则向下一层的链表搜索
	// for循环结束，cur指向的next节点：1. 大于新插入的key 2. 等于
	for (int i = level; i >= 0; i--) 
	{ 
		// 查找第一个node的next节点的key不小于（可能等于）新插入节点的key
		while (current->forward[i] != NULL && 
			current->forward[i]->key < key) 
			current = current->forward[i];
		// 说明如果新建入的节点有level i层，则其在level i层链表中，应插到这里的update[i]后 
		update[i] = current; 
	} 
	current = current->forward[0]; 

	// 等同于insert_unique，存在相同元素则不插入
	// 如果去掉下面的条件，则是insert_multi
	if (current == NULL || current->key != key) 
	{ 
		int rlevel = randomLevel(); 
        // 如果新插入的node，其高度大于当前skiplist的高度，则更新level的值
        // 并且update全置为header
		if (rlevel > level) 
		{ 
			for (int i=level+1;i<rlevel+1;i++) 
				update[i] = header; 

			// Update the list current level 
			level = rlevel; 
		} 

		// create new node with random level generated 
		SkipListNode* new_node = createNode(key, rlevel); 

		// insert node by rearranging pointers 
		for (int i=0;i<=rlevel;i++) 
		{ 
            // 将new_node的结点链接好
			new_node->forward[i] = update[i]->forward[i]; 
			update[i]->forward[i] = new_node; 
		} 
		cout << "Successfully Inserted key " << key << "\n"; 
	} 
}; 


// Delete element from skip list 
void SkipList::deleteElement(int key) 
{ 
	SkipListNode *current = header; 

	// create update array and initialize it 
    // update的作用是将结点连接起来
    vector<SkipListNode *> update(MAXLVL+1,NULL);
    for(int i = level; i >= 0; i--) 
    { 
        while(current->forward[i] != NULL  && 
              current->forward[i]->key < key) 
            current = current->forward[i]; 
        update[i] = current; 
    } 
  
    current = current->forward[0]; 
  
    // If current node is target node 
    if(current != NULL && current->key == key) 
    { 
        for(int i=0;i<=level;i++) 
        { 
            if(update[i]->forward[i] != current) 
                break; 
  
            update[i]->forward[i] = current->forward[i]; 
        } 
		delete current;
  
        // Remove levels having no elements  
        while(level>0 && 
              header->forward[level] == 0) 
            level--; 
         cout<<"Successfully deleted key "<<key<<"\n"; 
    } 
}; 


void SkipList::searchElement(int key) {
	SkipListNode* cur = header;
	for (int i = level; i > -1; --i) {
		while (cur->forward[i]&& cur->forward[i]->key < key)cur = cur->forward[i];
	}
	cur = cur->forward[0];
	if (cur && cur->key == key) {
		cout << "Found Key: " << key << endl;
	}
	else {
		cout<< "Not found key: "<<key<<endl;
	}
}

// Display skip list level wise 
void SkipList::displayList() 
{ 
	cout<<"\n*****Skip List*****"<<"\n"; 
	for (int i=0;i<=level;i++) 
	{ 
		SkipListNode *node = header->forward[i]; 
		cout << "Level " << i << ": "; 
		while (node != NULL) 
		{ 
			cout << node->key<<" "; 
			node = node->forward[i]; 
		} 
		cout << "\n"; 
	} 
}; 

// Driver to test above code 
int main() 
{ 
	// Seed random number generator 
	srand((unsigned)time(0)); 

	// create SkipList object with MAXLVL and P 
	SkipList lst(3, 0.5); 
    for(int i=0;i<(1<<10);++i){
        lst.insertElement(i);
    }
	// lst.insertElement(3); 
	// lst.insertElement(6); 
	// lst.insertElement(7); 
	// lst.insertElement(9); 
	// lst.insertElement(12); 
	// lst.insertElement(19); 
	// lst.insertElement(17); 
	// lst.insertElement(26); 
	// lst.insertElement(21); 
	// lst.insertElement(25); 
	lst.displayList(); 


    //Search for node 19 
	lst.searchElement(19);

	//Delete node 19 
	lst.deleteElement(19);
	lst.displayList();
} 
