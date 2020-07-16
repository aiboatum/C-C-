#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcpy,strcmp等
#include <math.h> // pow

#define STRING_SIZE 20
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

// 员工信息
typedef struct Info{
    char _name[STRING_SIZE];
    int _salary;
}InfoType;


// 二叉链表实现二叉树
typedef struct BSTreeNode{
    char _key[STRING_SIZE]; // 结点的key字段
    int  _salary;           // 存储工资              
    struct BSTreeNode *_left;    // 左孩子
    struct BSTreeNode *_right;    // 右孩子
    struct BSTreeNode *_parent;    // 父结点，方便后续的删除等操作
}BSTreeNode, *BSTree;




// 返回树的高度，递归实现
int getHeight(BSTree tree){
    if(!tree)return 0;
    int L=getHeight(tree->_left);
    int R=getHeight(tree->_right);
    return max(L,R)+1;
}

// 按层次遍历二叉排序树
// 层次遍历需要的队列，为方便起见，使用数组实现队列
void BSTree_Levelorder_Traverse(BSTree tree){
    printf("员工信息总览：\n");
    printf("-------------------------------------------\n");
    BSTreeNode * q[100];
    int front = 0, rear = 0;
    BSTreeNode * p;
    if (tree == NULL) return;
    q[rear] = tree;
    rear = (rear + 1) % 100;

    // 以下冗余部分仅为了分行显示
    int height=getHeight(tree);
    int h=1;
    int cnt=0;
    while(front != rear){
        if(h==height+1)break;
        p = q[front];
        front = (front + 1) % 100;
        if(p)printf("%s,%d\t", p->_key,p->_salary);
        else printf("NULL\t");
        ++cnt;

        if(cnt==(int)(pow(2,h))-1){
            printf("\n");
            ++h;
        }

        if (p){
            q[rear] = p->_left;
            rear = (rear + 1) % 100;
        }
        else {
            q[rear]=NULL;
            rear=(rear+1)%100;
        }
        if (p){
            q[rear] = p->_right;
            rear = (rear + 1) % 100;
        }
        else{
            q[rear] = NULL;
            rear = (rear + 1) % 100;
        }
    }
    printf("-------------------------------------------\n");
}

// 查找tree中键值为_key的节点
BSTreeNode* BSTree_Search(BSTree tree, char * _key){
    BSTreeNode * p=tree;
    while ((p!=NULL) && strcmp(p->_key,_key)!=0){
        if(strcmp(_key,p->_key)<0)
            p = p->_left;
        else
            p = p->_right;
    }
    return p;
}

// 查找最小结点：返回tree为根结点的二叉树的最小结点。
BSTreeNode* min_BSTNode(BSTree tree){
    if (tree == NULL)
        return NULL;

    while(tree->_left != NULL)
        tree = tree->_left;
    return tree;
}

// 查找最大结点：返回tree为根结点的二叉树的最大结点。
BSTreeNode* max_BSTNode(BSTree tree){
    if (!tree)return NULL;

    while(tree->_right != NULL)
        tree = tree->_right;
    return tree;
}

// 找结点(x)的后继结点。即，查找"二叉树中数据值大于该结点"的"最小结点"。
BSTreeNode* BSTNode_successor(BSTreeNode *x){

    if (x->_right != NULL)
        return min_BSTNode(x->_right);
    BSTreeNode* y = x->_parent;
    while ((y!=NULL) && (x==y->_right)){
        x = y;
        y = y->_parent;
    }

    return y;
}

// 找结点(x)的前驱结点。即，查找"二叉树中数据值小于该结点"的"最大结点"。
BSTreeNode* BSTree_predecessor(BSTreeNode *x){
    if (x->_left != NULL)
        return max_BSTNode(x->_left);
    BSTreeNode* y = x->_parent;
    while ((y!=NULL) && (x==y->_left)){
        x = y;
        y = y->_parent;
    }

    return y;
}


// 创建二叉树结点
BSTreeNode* Construct_BSTNode(char * _key,int _salary, BSTreeNode *_parent, BSTreeNode *_left, BSTreeNode* _right){
    BSTreeNode* p;
    if ((p = (BSTreeNode *)malloc(sizeof(BSTreeNode))) == NULL)
        return NULL;
    strcpy(p->_key,_key);
    p->_salary=_salary;
    p->_left = _left;
    p->_right = _right;
    p->_parent = _parent;
    return p;
}

// 插入结点z到二叉搜索树中
BSTreeNode* BSTree_Insert(BSTree tree, BSTreeNode *z){
    BSTreeNode *y = NULL;
    BSTreeNode *x = tree;
    while (x){
        y = x;
        if(strcmp(z->_key,x->_key)<0)
            x = x->_left;
        else
            x = x->_right;
    }

    z->_parent = y;
    if (y==NULL)
        tree = z;
    else if(strcmp(z->_key,y->_key)<0)
        y->_left = z;
    else
        y->_right = z;

    return tree;
}


// 新建结点，key字段为_key，并将其插入到二叉树中
BSTreeNode* Insert_BSTree(BSTree tree, char *_key,int _salary){
    BSTreeNode *z;    // 新建结点
    // 如果新建结点失败，则返回。
    if ((z=Construct_BSTNode(_key, _salary,NULL, NULL, NULL)) == NULL)
        return tree;

    return BSTree_Insert(tree, z);
}


// 删除结点(z)，并返回根节点
BSTreeNode* BSTNode_delete(BSTree tree,struct BSTreeNode *z){
    struct BSTreeNode *x=NULL;
    struct BSTreeNode *y=NULL;

    if ((z->_left == NULL) || (z->_right == NULL) )
        y = z;
    else
        y = BSTNode_successor(z);

    if (y->_left != NULL)
        x = y->_left;
    else
        x = y->_right;

    if (x != NULL)
        x->_parent = y->_parent;

    if (y->_parent == NULL)
        tree = x;
    else if (y == y->_parent->_left)
        y->_parent->_left = x;
    else
        y->_parent->_right = x;

    if (y != z)
        strcpy(z->_key,y->_key);

    if (y!=NULL)
        free(y);

    return tree;
}

// 删除结点(key为_key的结点)，并返回根节点
BSTreeNode* Delete_BSTNode(BSTree tree, char * _key){
    BSTreeNode *z, *node;

    if ((z = BSTree_Search(tree, _key)) != NULL)
        tree = BSTNode_delete(tree, z);

    return tree;
}

// 销毁操作，回收资源
// 递归实现
void Destroy_BSTree(BSTree tree){
    if (tree==NULL)return ;
    if (tree->_left != NULL)
        Destroy_BSTree(tree->_left);
    if (tree->_right != NULL)
        Destroy_BSTree(tree->_right);
    free(tree);
}


// 默认的员工数据
InfoType arr[8]={
    "liuk",4500,
    "qiao",5600,
    "ruhui",5700,
    "aijun",5000,
    "caopi",4800,
    "qin",6000,
    "daire",4600,
    "caocao",5300
};

// 添加员工操作
BSTree Insert(BSTree root){
    char _name[STRING_SIZE];
    int _salary;
    printf("输入员工信息（格式为zhangsan 90），输入exit退出:\n");
    while(scanf("%s",_name)&&strcmp(_name,"exit")!=0&&scanf("%d",&_salary)){
        root = Insert_BSTree(root, _name,_salary);
        printf("添加员工后，");
        BSTree_Levelorder_Traverse(root);
        printf("继续添加 or 输入exit退回菜单界面:\n");
    }
    system("cls");
    return root;
}

void Search(BSTree root){
    char _name[STRING_SIZE];
    printf("输入想要查找的员工姓名，输入exit退出:\n");
    while(scanf("%s",_name)&&strcmp(_name,"exit")!=0){
        BSTree_Levelorder_Traverse(root);
        BSTreeNode* bt= BSTree_Search(root,_name);
        if(!bt)
            printf("该员工不存在，请重新输入!\n");
        else        
            printf("员工姓名：%s，工资为：%d\n",bt->_key,bt->_salary);
        printf("继续查询 or 输入exit退回菜单界面:\n");
    }
    system("cls");
}

BSTree Delete(BSTree root){
    char _name[STRING_SIZE];
    printf("输入想要删除的员工姓名，输入exit退出:\n");
    while(scanf("%s",_name)&&strcmp(_name,"exit")!=0){
        root=Delete_BSTNode(root,_name);
        printf("删除后，");
        BSTree_Levelorder_Traverse(root);
        printf("继续删除 or 输入exit退回菜单界面:\n");
    }
    system("cls");
    return root;
}

BSTree Modification(BSTree root){
    char _name[STRING_SIZE];
    printf("输入想要修改的员工姓名，输入exit退出:\n");
    while(scanf("%s",_name)&&strcmp(_name,"exit")!=0){
        BSTreeNode* bt= BSTree_Search(root,_name);
        if(!bt){
            printf("该员工不存在，请重新输入!\n");
            continue;
        }
        else        
            printf("输入工资修改值：\n");
        // int _salary;
        scanf("%d",&bt->_salary);
        printf("修改后，");
        BSTree_Levelorder_Traverse(root);
        printf("继续修改 or 输入exit退回菜单界面:\n");
    }
    system("cls");
    return root;
}

double Average_Salary(BSTree root){
    double ret=0.0;
    if(!root)return ret;
    else ret=(double)root->_salary;
    return Average_Salary(root->_left)+Average_Salary(root->_right)+ret;
}

int main(){
    BSTree root=NULL;
    int input;
    printf("\n*************************************************");
    printf("\n\
        MEMU:\n\
        1: 添加员工信息\n\
        2: 查找员工信息\n\
        3: 删除员工信息\n\
        4: 修改员工工资\n\
        5: 计算员工的平均工资\n\
        6: 退出");
    printf("\n*************************************************\n");
    scanf("%d",&input);
    getchar();// 去掉\n影响
    while(input!=6){
        switch(input){
            case 1:
                system("cls");
                root = Insert(root);
                break;
            case 2:
                system("cls");
                if(!root){
                    printf("暂无员工信息，请先添加!\n");
                    break;
                }
                Search(root);
                break;
            case 3:
                system("cls");
                root = Delete(root);
                break;
            case 4:
                system("cls");
                root = Modification(root);
                break;
            case 5:
                system("cls");
                printf("员工平均工资为:%f\n",Average_Salary(root));
                break;
        }
    printf("\n*************************************************");
    printf("\n\
        MEMU:\n\
        1: 添加员工信息\n\
        2: 查找员工信息\n\
        3: 删除员工信息\n\
        4: 修改员工工资\n\
        5: 计算员工的平均工资\n\
        6: 退出");
    printf("\n*************************************************\n");
        scanf("%d",&input);
        getchar();
    }
    Destroy_BSTree(root);
    if(input==6)
    exit(0);
    return 0;

    // 使用默认员工数据
    // for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++){
    //     printf("%s ", arr[i]);
    //     root = Insert_BSTree(root, arr[i]._name,arr[i]._salary);
    // }

    //BSTree_Levelorder_Traverse(root);

    // Destroy_BSTree(root);
}