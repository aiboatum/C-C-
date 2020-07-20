#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h> // INT_MAX
#include <string.h> 

#define STRING_SIZE 20
#define MAX         100                 // 矩阵最大容量
// 邻接矩阵
typedef struct graph{
    char vexs[MAX][STRING_SIZE];       // 顶点集合
    int vexnum;           // 顶点数
    int edgnum;           // 边数
    int matrix[MAX][MAX]; // 邻接矩阵
}Graph, *PGraph;

// 边的结构体
typedef struct Edge{
    char start[STRING_SIZE]; // 边的起点
    char end[STRING_SIZE];   // 边的终点
    int weight; // 边的权重
}Edge;


// 返回结点名称对应的位置
int get_position(Graph G, char *str){
    int i;
    for(i=0; i<G.vexnum; i++)
        if(strcmp(G.vexs[i],str)==0)
            return i;
    return -1;
}

// 用户自己创建城市地图
Graph* _Construct_Graph(){
    char c1[STRING_SIZE]={'\0'}, c2[STRING_SIZE]={'\0'};
    int v, e;
    int i, j, weight, p1, p2;
    Graph* pG;
    
    // 输入"顶点数"和"边数"
    printf("输入城市个数（小于100）: ");
    scanf("%d", &v);
    printf("输入城市之间连通的个数（边的个数）: ");
    scanf("%d", &e);
    if ( v < 1 || e < 1 || (e > (v * (v-1)))){
        printf("输入格式错误!\n");
        return NULL;
    }
    
    // 创建地图
    if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
        return NULL;
    // 初始化
    memset(pG, 0, sizeof(Graph));

    // 初始化"顶点数"和"边数"
    pG->vexnum = v;
    pG->edgnum = e;
    // 初始化"顶点"
    for (i = 0; i < pG->vexnum; i++){
        printf("城市名称: ", i);
        scanf("%s",(pG->vexs[i]));
    }

    // 初始化"边"的权值
    for (i = 0; i < pG->vexnum; i++){
        for (j = 0; j < pG->vexnum; j++){
            if (i==j)
                pG->matrix[i][j] = 0;
            else
                pG->matrix[i][j] = INT_MAX;
        }
    }
    // 初始化"边"的权值: 根据用户的输入进行初始化
    for (i = 0; i < pG->edgnum; i++){
        // 读取边的起始顶点，结束顶点，权值
        printf("输入两个城市之间的距离：（格式如，xian beijing 3200）", i);
        scanf("%s %s",c1,c2);
        scanf("%d", &weight);

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);
        if (p1==-1 || p2==-1){
            printf("输入格式错误!\n");
            free(pG);
            return NULL;
        }
        pG->matrix[p1][p2] = weight;
        pG->matrix[p2][p1] = weight;
    }

    return pG;
}

// 使用默认数据构造地图
Graph* __Construct_default_graph(){
    char vexs[7][STRING_SIZE] = {"beijing", "xian","zhengzhou", "xuzhou", "chengdu", "guangzhou", "shanghai"};
    int matrix[][9] = {
        // "beijing", "xian",  "zhengzhou",  "xuzhou",  "chengdu",  "guangzhou",  "shanghai"
        {     0,    2553,    695,    704,INT_MAX,INT_MAX,INT_MAX},
        {  2553,       0,    511,INT_MAX,    812,INT_MAX,INT_MAX},
        {   695,     511,      0,    349,INT_MAX,   1579,INT_MAX},
        {   704, INT_MAX,    349,      0,INT_MAX,INT_MAX,    651},
        {INT_MAX,    812,INT_MAX,INT_MAX,INT_MAX,   2369,INT_MAX},
        {INT_MAX,INT_MAX,   1579,INT_MAX,   2369,      0,   1385},
        {INT_MAX,INT_MAX,INT_MAX,    651,INT_MAX,   1385,      0}
        };
    int vlen = sizeof(vexs)/sizeof(vexs[0]);
    int i, j;
    Graph* pG;
    
    // 输入"顶点数"和"边数"
    if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(Graph));

    // 初始化"顶点数"
    pG->vexnum = vlen;
    // 初始化"顶点"
    for (i = 0; i < pG->vexnum; i++)
        strcpy(pG->vexs[i],vexs[i]);
        // pG->vexs[i] = vexs[i];

    // 初始化"边"
    for (i = 0; i < pG->vexnum; i++)
        for (j = 0; j < pG->vexnum; j++)
            pG->matrix[i][j] = matrix[i][j];

    // 统计边的数目
    for (i = 0; i < pG->vexnum; i++)
        for (j = 0; j < pG->vexnum; j++)
            if (i!=j && pG->matrix[i][j]!=INT_MAX)
                pG->edgnum++;
    pG->edgnum /= 2;

    return pG;
}

// 返回顶点v的第一个邻接顶点的索引，若无则返回-1
int first_vertex(Graph G, int v){
    int i;
    if (v<0 || v>(G.vexnum-1))
        return -1;
    for (i = 0; i < G.vexnum; i++)
        if (G.matrix[v][i]!=0 && G.matrix[v][i]!=INT_MAX)
            return i;
    return -1;
}


// 返回顶点v相对于w的下一个邻接顶点的索引，若无则返回-1
int next_vertix(Graph G, int v, int w){
    int i;
    if (v<0 || v>(G.vexnum-1) || w<0 || w>(G.vexnum-1))
        return -1;
    for (i = w + 1; i < G.vexnum; i++)
        if (G.matrix[v][i]!=0 && G.matrix[v][i]!=INT_MAX)
            return i;
    return -1;
}


// 深度优先搜索遍历某个连通图的递归实现
void DFS(Graph G, int i, int *visited){                                   
    int w; 
    visited[i] = 1;
    printf("%s ", G.vexs[i]);
    // 遍历该顶点的所有邻接顶点。若是没有访问过，那么继续往下走
    for (w = first_vertex(G, i); w >= 0; w = next_vertix(G, i, w))
    {
        if (!visited[w])
            DFS(G, w, visited);
    }
}


// 深度优先搜索遍历整个图
void DFSTraverse(Graph G,int v){
    int i;
    int visited[MAX];       // 顶点访问标记
    // 初始化所有顶点都没有被访问
    for (i = 0; i < G.vexnum; i++)
        visited[i] = 0;

    printf("DFS traverse: ");
    for (i = v; i < G.vexnum; i++)
    {
        if (!visited[i])
            DFS(G, i, visited);
    }
    printf("\n");
}

/*
 * Dijkstra算法求最短路径。
 * 即，图(G)中"起点vs"到各个可到结点的最短路径。
 * 其中prev前驱顶点数组。prev[i]的值是"顶点vs"到"顶点i"的最短路径所经历的全部顶点中，位于"顶点i"之前的那个顶点。
 * dist，长度数组。即，dist[i]是"顶点vs"到"顶点i"的最短路径的长度。
 */
void dijkstra(Graph G, int vs, int prev[], int dist[]){
    int i,j,k;
    int min;
    int tmp;
    int flag[MAX];      // flag[i]=1表示"顶点vs"到"顶点i"的最短路径已成功获取。
    
    // 初始化
    for (i = 0; i < G.vexnum; i++){
        flag[i] = 0;              // 顶点i的最短路径还没获取到。
        prev[i] = 0;              // 顶点i的前驱顶点为0。
        dist[i] = G.matrix[vs][i];// 顶点i的最短路径为"顶点vs"到"顶点i"的权。
    }

    // 对"顶点vs"自身进行初始化
    flag[vs] = 1;
    dist[vs] = 0;

    // 遍历G.vexnum-1次；每次找出一个顶点的最短路径。
    for (i = 1; i < G.vexnum; i++){
        // 寻找当前最小的路径；
        // 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
        min = INT_MAX;
        for (j = 0; j < G.vexnum; j++){
            if (flag[j]==0 && dist[j]<min){
                min = dist[j];
                k = j;
            }
        }
        // 标记"顶点k"为已经获取到最短路径
        flag[k] = 1;

        // 修正当前最短路径和前驱顶点
        // 即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
        for (j = 0; j < G.vexnum; j++)
        {
            tmp = (G.matrix[k][j]==INT_MAX ? INT_MAX : (min + G.matrix[k][j])); // 防止溢出
            if (flag[j] == 0 && (tmp  < dist[j]) )
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }
    // 打印dijkstra最短路径的结果
    printf("dijkstra(%s): \n", G.vexs[vs]);
    for (i = 0; i < G.vexnum; i++)
        printf("(%s, %s)=%d\n", G.vexs[vs], G.vexs[i], dist[i]);

}

/*
* 查询给定两个城市之间的最短距离
* vs起始点，ve终止点
*/
void __Query_shortest_path(Graph G,int prev[], int dist[]){
    char str_s[STRING_SIZE];
    char str_e[STRING_SIZE];
    printf("输入查询的两个城市名称：（格式如，beijing nanjing，输入exit退出查询）：");
    while(scanf("%s",str_s)&&strcmp(str_s,"exit")!=0&&scanf("%s",str_e)){
        int vs=get_position(G,str_s);
        int ve=get_position(G,str_e);
        int i,j,k;
        int min;
        int tmp;
        int flag[MAX];     
        // 初始化
        for (i = 0; i < G.vexnum; i++){
            flag[i] = 0;              // 顶点i的最短路径还没获取到。
            prev[i] = 0;              // 顶点i的前驱顶点为0。
            dist[i] = G.matrix[vs][i];// 顶点i的最短路径为"顶点vs"到"顶点i"的权。
        }

        // 对"顶点vs"自身进行初始化
        flag[vs] = 1;
        dist[vs] = 0;

        // 遍历G.vexnum-1次；每次找出一个顶点的最短路径。
        for (i = 1; i < G.vexnum; i++)
        {
            // 寻找当前最小的路径；
            // 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
            min = INT_MAX;
            for (j = 0; j < G.vexnum; j++)
            {
                if (flag[j]==0 && dist[j]<min)
                {
                    min = dist[j];
                    k = j;
                }
            }
            flag[k] = 1;

            // 修正当前最短路径和前驱顶点
            // 即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
            for (j = 0; j < G.vexnum; j++)
            {
                tmp = (G.matrix[k][j]==INT_MAX ? INT_MAX : (min + G.matrix[k][j])); // 防止溢出
                if (flag[j] == 0 && (tmp  < dist[j]) )
                {
                    dist[j] = tmp;
                    prev[j] = k;
                }
            }
        }

        // 打印dijkstra最短路径的结果
        printf("城市%s到城市%s的最短路径为: ", G.vexs[vs],G.vexs[ve]);
        printf(" %d\n",dist[ve]);
    }
    
}

// 指定出发城市显示所有搜索线路上的城市清单
void __Query_path(Graph G){
    char beg[STRING_SIZE];
    printf("请输入想要查询的“出发”城市（exit退出查询）\n");
    while( scanf("%s",beg) && strcmp(beg,"exit")!=0 ){
        int i=get_position(G,beg);
        printf("出发城市%s可到达的城市有：\n",beg);
        DFSTraverse(G,i);
    }
}

int main()
{
    int prev[MAX] = {0};
    int dist[MAX] = {0};
    Graph* pG;
    // 默认地图
    pG = __Construct_default_graph();
    // DFSTraverse(*pG,5);
    // dijkstra(*pG, 4, prev, dist);
    // free(pG);
    // return 1;
    int input;
    printf("\n************菜单项************");
    printf("\n\
        1: 创建地图\n\
        2: 查询路线\n\
        3: 显示路线\n\
        4: 退出");
    printf("\n******************************\n");
    scanf("%d",&input);
    getchar();// 去掉\n影响
    while(input!=4){
        switch(input){
            case 1:
                if(pG)free(pG);
                pG=_Construct_Graph();     //添加城市
                break;
            case 2:
                __Query_shortest_path(*pG,prev,dist);
                break;
            case 3:
                __Query_path(*pG);
                break;
            case 4:
                break;
        }
        printf("\n************菜单项************");
        printf("\n\
            1: 创建地图\n\
            2: 查询路线\n\
            3: 显示路线\n\
            4: 退出");
        printf("\n******************************\n");
        scanf("%d",&input);
        getchar();
    }
    if(input==4)
    exit(0);
    return 1;
}