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
	// create header node and initialize key to -1
    // heard结点起辅助作用，不存储真正的结点 
	header = new SkipListNode(-1, MAXLVL); 
}; 

// create random level for node 
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

// create new node 
SkipListNode* SkipList::createNode(int key, int level) 
{ 
	SkipListNode *n = new SkipListNode(key, level); 
	return n; 
}; 

// Insert given key in skip list 
void SkipList::insertElement(int key){
	SkipListNode *current = header; 

	// create update array and initialize it 
    // update的作用是将结点连接起来
    vector<SkipListNode *> update(MAXLVL+1,NULL);

	/* start from highest level of skip list 
		move the current pointer forward while key 
		is greater than key of node next to current 
		Otherwise inserted current in update and 
		move one level down and continue search 
	*/
	for (int i = level; i >= 0; i--) 
	{ 
		while (current->forward[i] != NULL && 
			current->forward[i]->key < key) 
			current = current->forward[i]; 
		update[i] = current; 
	} 

	/* reached level 0 and forward pointer to 
	right, which is desired position to 
	insert key. 
	*/
	current = current->forward[0]; 

	/* if current is NULL that means we have reached 
	to end of the level or current's key is not equal 
	to key to insert that means we have to insert 
	node between update[0] and current node */
	if (current == NULL || current->key != key) 
	{ 
		// Generate a random level for node 
		int rlevel = randomLevel(); 

		// If random level is greater than list's current 
		// level (node with highest level inserted in 
		// list so far), initialize update value with pointer 
		// to header for further use 
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


void SkipList::deleteElement(int key) {
	SkipListNode* cur = header;
	vector<SkipListNode*> update(MAXLVL + 1, NULL);
	for (int i = level; i > -1; --i) {
		while (cur->forward[i] != NULL && cur->forward[i]->key < key) {
			cur = cur->forward[i];
		}
		update[i] = cur;
	}
	while (level > 0 && header->forward[level] == 0)level--;
	cout << "Successfully deleted key " << key << endl;
}


void SkipList::searchElement(int key) {
	SkipListNode* cur = header;
	for (int i = level; i > -1; --i) {
		while (cur->forward[i]&& cur->forward[i]->key < key)cur = cur->forward[i];
	}
	cur = cur->forward[0];
	if (cur && cur->key == key) {
		cout << "Found Key: " << key << endl;
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
    for(int i=0;i<(1<<20);++i){
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
