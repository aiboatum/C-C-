/*------------
*   前缀树，字典树，trieTree
*-------------*/

#include <iostream>
#include <cstring>
using namespace std;

#define Branch_Num 26

namespace test{

struct TireTreeNode{
    bool isStr; // 指明该节点是否是一个完整的字符串
    // 每个节点中 next数组的下标就对应着每一个alphabet
    TireTreeNode * next[Branch_Num];// 每一个节点有26个分支
    TireTreeNode():
        isStr(false){
            memset(next,NULL,sizeof(next));
        }
};

class TireTree{
private:
    TireTreeNode *_root;
public:
    TireTree():_root(new TireTreeNode()){}

    ~TireTree(){
        Delete(_root);
        cout<<"------------------"<<endl;
        cout<<"资源回收完毕！"<<endl;
    }

    void Insert(const char * );
    bool Search(const char * );
    void Delete(TireTreeNode * node);
    bool StartWith(const char *);
};

void TireTree::Insert(const char * word){
    TireTreeNode *location=_root;
    while(*word){
        // 结点的子结点为NULL，则新建一个子结点
        if(location->next[*word-'a']==NULL){
            TireTreeNode * newNode = new TireTreeNode();
            // 插入该新建结点
            location->next[*word-'a']=newNode;
        }
        // 沿着该前缀继续向下进行
        location=location->next[*word-'a'];
        ++word;
    }
    // 字符串已全部添加到tireTree中
    // 标识该结点为止是一个完整的字符串
    location->isStr=true;   // 实质上就是一个叶节点
}

// 遍历前缀树：查找指定字符串是否存在
bool TireTree::Search(const char * word){
    TireTreeNode * location=_root;
    while(*word && location!=NULL){
        location=location->next[*word-'a'];
        ++word;
    }
    return (location!=NULL && location->isStr);
}

bool TireTree::StartWith(const char *prefix){
    TireTreeNode * pos = _root;
    while(*prefix && pos){
        pos=pos->next[*prefix-'a'];
        ++prefix;
    }
    return pos;
}



void TireTree::Delete(TireTreeNode *location){
    if(location==NULL)return ;
    for(int i=0;i<Branch_Num;++i){
        if(location->next[i]!=NULL)Delete(location->next[i]);
    }
    delete location;
}

}
int main(){
    using namespace test;
    cout<<"--------Test------"<<endl;
    TireTree root;
    root.Insert("a");
    root.Insert("bcd");
    root.Insert("xyz");
    root.Insert("abcdef");

    if(root.Search("a")){
        cout<<"a exist!"<<endl;
    }
    if(root.StartWith("xy")){
        cout<<"xy prefix exitst!"<<endl;
    }
    return 0;
}
