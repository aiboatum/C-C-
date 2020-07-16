#include <iostream>
#include <algorithm>
#include <string>
#include <vector>


/***
 * AVL结点定义
 **/
struct AVLNode {
    std::string data;       // 数据字段
    AVLNode* LeftChild; // 指向左孩子
    AVLNode* RightChild;// 指向右孩子
    AVLNode(std::string str):data(str),LeftChild(nullptr),RightChild(nullptr){}
};

/***
 *  AVL树定义
 **/
class AVLTree {
public:
    /***
     * 构造函数
     * 初始时，构造一个空树
     ***/
    AVLTree() :root(nullptr) {}
    ~AVLTree() {Destroy(root);std::cout<<"该AVL树已被销毁"<<std::endl;}

    /***
     * 向AVL树中添加结点
     * 结点标识为string时，其排序原则基于字典序
     ***/
    void Add_AVLNode() {
        std::cout << "输入结点名称 （空格隔开，exit终止标识） " << std::endl;
        std::string str;
        while (std::cin >> str && str!="exit") {
            root = Insert(root, str);
        }
        std::cout << "结点添加完毕！\nAVL树总览：" << std::endl;
        AVLTree_show();
    }



    /***
     *  递归实现
     *  返回某结点为根节点的子树高度
     ***/
    int get_height(AVLNode* node){
        if(!node)return 0;
        return std::max(get_height(node->LeftChild),get_height(node->RightChild))+1;
    }

    /***
     * 输出AVL树信息
     ***/
    void AVLTree_show() {
        std::string out;
        std::cout << "Preoder traverse: ";
        
        AVLTree_preorder_Traverse(root,out);
        out=out.substr(0,out.length()-2);
        std::cout<<out<<std::endl;

        out.clear();
        std::cout<<"Inorder traverse: ";
        AVLTree_inorder_Traverse(root,out);
        out=out.substr(0,out.length()-2);
        std::cout<<out<<std::endl;
    }

    /***
     * 先序遍历AVL树
     ***/
    void AVLTree_preorder_Traverse(AVLNode* p,std::string &out){
        if (p) {
            out+=p->data+"->";
            AVLTree_preorder_Traverse(p->LeftChild,out);
            AVLTree_preorder_Traverse(p->RightChild,out);
        }
    }
    /***
     * 中序遍历AVL树
     ***/
    void AVLTree_inorder_Traverse(AVLNode* p,std::string &out) {
        if (p) {

            AVLTree_inorder_Traverse(p->LeftChild,out);
            out+=p->data+"->";
            AVLTree_inorder_Traverse(p->RightChild,out);
        }
    }

    

    /***
     * 返回key为str的结点指针
     ***/
    AVLNode* Search(std::string str) {
        AVLNode* p = root;
        while (p) {
            if (p->data == str)return p;
            else if (p->data < str)
                p = p->RightChild;
            else
                p = p->LeftChild;
        }
        return NULL;
    }

    /***
     * 返回子树最大值结点的指针
     ***/
    AVLNode* AVLTree_MAX(AVLNode* node) {
        if (!node)return NULL;
        while (node->RightChild)node = node->RightChild;
        return node;
    }

    /***
     * 返回子树最小值结点的指针
     ***/
    AVLNode* AVLTree_MIN(AVLNode* subTree) {
        if (!subTree)
            return NULL;
        while (subTree->LeftChild) {
            subTree = subTree->LeftChild;
        }
        return subTree;
    }
    void Insert(std::string str) {
        root = Insert(root, str);
    }

    void Remove(std::string str) {
        root = Remove(root, str);
    }
    /***
     * 插入结点Node
     * 返回插入位置的根节点
     * 包括四种旋转操作，即LL,RR,LR,RL等旋转操作
     * 对于左子树（右子树）的左孩子（右孩子）插入导致的不平衡通过将其右旋一次
     * 对于左子树的右孩子插入导致的不平衡，通过LL,RR操作的结合即可完成
     ***/
    AVLNode* LL_Rotation(AVLNode* Node){
        AVLNode* tmp = Node->LeftChild;
        Node->LeftChild = tmp->RightChild;
        tmp->RightChild = Node;
        return tmp;
    }; 
    AVLNode* RR_Rotation(AVLNode* Node){
        AVLNode* tmp = Node->RightChild;
        Node->RightChild = tmp->LeftChild;
        tmp->LeftChild = Node;
        return tmp;
    }
    AVLNode* RL_Rotation(AVLNode* Node){
        Node->RightChild = LL_Rotation(Node->RightChild);
        return RR_Rotation(Node);
    }
    AVLNode* LR_Rotation(AVLNode* tree){
        root->LeftChild = RR_Rotation(root->LeftChild);
        return LL_Rotation(root);
    }

    // 平衡操作
    AVLNode* Balance(AVLNode* tree){
        int bf = BF(tree);
        if (bf > 1) { 
            if (BF(tree->LeftChild) > 0)
                tree = LL_Rotation(tree);
            else
                tree = LR_Rotation(tree);
        }
        else if (bf < -1) //右子树更高
        {
            if (BF(tree->RightChild) > 0)
                //右孩子结点平衡因子>0说明新节点多在了左子树上，因此调用RL_Rotation
                tree = RL_Rotation(tree);
            else
                //右孩子结点平衡因子<0说明新节点多在了右子树上上，因此调用RR_Rotation
                tree = RR_Rotation(tree);
        }
        return tree;
    }

    // 插入操作
    AVLNode* Insert(AVLNode* tree, std::string str){
        if (!tree) tree = new AVLNode(str);
        else if (str > tree->data) { 
            tree->RightChild = Insert(tree->RightChild, str);
            tree = Balance(tree);
        }
        else if (str < tree->data) { 
            tree->LeftChild = Insert(tree->LeftChild, str);
            tree = Balance(tree);
        }
        return tree;
    }

    // 删除操作
    AVLNode* Remove(AVLNode* tree,std::string str){
        if (!Search(str)) {
            std::cout << "\"" << str << "\"结点未找到！" << std::endl;
            return root;
        }

        if (!root)  //root为空指针都直接返回NULL
            return root;

        // case1:当删除的结点恰好是根节点
        if (tree->data == str) {
            if (tree->LeftChild && tree->RightChild) {
                if (BF(tree) > 0) {
                    //左子树高于右子树，则根节点的值替换为其直接前驱的值，然后转化为删除
                    //其直接前驱(其位于左子树上，也就意味着去降低左子树高度)
                    AVLNode* tmp = AVLTree_MAX(tree->LeftChild); //直接前驱就是左子树的最大值
                    tree->data = tmp->data;
                    //递归调用Remove()删除subRoot的左子树上的前驱结点后，Remove()返回可能为
                    //新的subRoot的左子树根节点供subRoot更新左孩子结点((Remove()会调用Balance()函数平衡其操作的树))。
                    tree->LeftChild = Remove(tree->LeftChild, tmp->data);
                }
                else {
                    //右子树高于左子树，则根节点的值替换为其直接后继的值，
                    //然后转化为删除其直接后继(其位于右子树上，也就意味着去降低右子树高度)
                    AVLNode* tmp = AVLTree_MIN(tree->RightChild);
                    tree->data = tmp->data;
                    tree->RightChild = Remove(tree->RightChild, tmp->data);
                }
            }
            else //情况1.2：只存在一颗子树或者都不存在
            {
                //直接将根节点更新为其孩子结点(都不存在则为NULL)
                AVLNode* tmp = tree;
                tree = (tree->LeftChild) ? (tree->LeftChild) : (tree->RightChild);
                delete tmp;
                tmp = NULL;
            }
        }
        else if (str < tree->data) { //情况2：要删除的节点位于左子树上
            //递归调用,在subRoot的左子树上进行删除操作，并返回新的左子树根节点供subRoot更新左孩子指针
            tree->LeftChild = Remove(tree->LeftChild, str);
            //在subRoot的左子树上完成删除操作后,可能导致该树不平衡,故需要进行平衡操作并更新当前根节点
            if (BF(tree) < -1)
                tree = Balance(root);
        }
        else {//情况3：要删除的节点位于右子树上
            //递归调用,在subRoot的右子树上进行删除操作，并返回新的右子树根节点供subRoot更新右孩子指针
            tree->RightChild = Remove(tree->RightChild, str);
            //在subRoot的右子树上完成删除操作后,可能导致该树不平衡,故需要进行平衡操作并更新当前根节点
            if (BF(tree) > 1)
                tree = Balance(tree);
        }
        //返回该树当前根节点供其父节点更新孩子节点
        return tree;
    }

    // 销毁操作
    void Destroy(AVLNode* p) {
        if (p) {
            Destroy(p->LeftChild);
            Destroy(p->RightChild);
            delete p;
        }
    }

    // 返回某个节点的平衡因子
    int BF(const AVLNode* p) {
        return get_height(p->LeftChild) - get_height(p->RightChild);
    }
private:
    AVLNode* root;

};

int main() {
    AVLTree avl;
    
    std::cout << "************测试**********" << std::endl;
    std::cout << "1：测试插入操作:"<<std::endl;
    avl.Add_AVLNode();
    std::string input;
    std::cout<<"2：测试查找操作:(输入exit退出查找操作)"<<std::endl;
    while(std::cin>>input && input!="exit"){
        AVLNode *t=avl.Search(input);
        if(t)std::cout<<"该结点存在"<<std::endl;
        else std::cout<<"该结点不存在"<<std::endl;
    }

    std::cout<<"3：测试删除操作:(输入exit退出删除操作)"<<std::endl;
    while(std::cin>>input && input!="exit"){
        avl.Remove(input);
        std::cout<<"删除后，";
        avl.AVLTree_show();
    }
}