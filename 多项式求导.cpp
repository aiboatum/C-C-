/***
 * Date: 2020-7-16
 * 主要功能：   根据输入的多项式，输出其导数
 * 例子：       输入x+x^1000+1000^289这种形式
 *            输出1000x^999+289000^288+1
 ***/
#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <algorithm>
#include <stack>
#include <string>

using namespace std;

bool cmp(int ch){return !isspace(ch);}
void trimLeftTrailingSpaces(string &input) {
    
    input.erase(input.begin(), find_if(input.begin(), input.end(), cmp));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), cmp).base(), input.end());
}

struct PolyNode {
    int  coef;
    int  exp;
    //struct PolyNode *next;
    PolyNode():coef(0),exp(0){}
    PolyNode(const int c,const int e):coef(c),exp(e){}
};

int my_cmp(const PolyNode &a,const PolyNode &b){
    return a.exp>b.exp;
}
vector<PolyNode> Difference(vector<PolyNode> &pa){
    vector<PolyNode> ret;
    for(vector<PolyNode>::iterator iter=pa.begin();iter!=pa.end();++iter){
        if(iter->exp==0)// 指数为0
            continue;
        iter->coef=iter->exp*iter->coef;
        iter->exp--;
        ret.push_back(*iter);
    }

    // 排序，按exp大小排序
    sort(ret.begin(),ret.end(),my_cmp);
    return ret;
}

int main(){
    std::stringstream ss;
    string input;
    getline(cin,input);
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);

    vector<PolyNode > Poly;

    if(input.empty())return -1;
    ss.str(input);
    string item;
    char delim='+';
    getline(ss,item,delim);
    auto x_pos=find_if(item.begin(),item.end(),[](const char ch){return ch=='x';});

    PolyNode node;
    if(x_pos==item.end()){  // 假设item不为空
        node.coef=atoi(item.c_str());
        node.exp=0;
    }
    else{
        if(item.begin()==x_pos) // 系数为1
            node.coef=1;   
        else 
            node.coef=atoi(string(item.begin(),x_pos).c_str());

        if(item.end()-1==x_pos) // 次数为1
            node.exp=1;
        else 
            node.exp=atoi(string(x_pos+2,item.end()).c_str());
    }
    Poly.push_back(node);

    while(true){
        if(!getline(ss,item,delim))break;
        cout<<"item : "<<item<<endl;
        auto x_pos=find_if(item.begin(),item.end(),[](const char ch){return ch=='x';});
        PolyNode node;
        if(x_pos==item.end()){  // 假设item不为空
            node.coef=atoi(item.c_str());
            node.exp=0;
        }
        else{
            if(item.begin()==x_pos) // 系数为1
                node.coef=1;   
            else 
                node.coef=atoi(string(item.begin(),x_pos).c_str());

            if(item.end()-1==x_pos) // 次数为1
                node.exp=1;
            else 
                node.exp=atoi(string(x_pos+2,item.end()).c_str());
        }
        Poly.push_back(node);
        //if(!getline(ss,item,delim))break;
    }

    vector<PolyNode> out=Difference(Poly);
    string output;
    for(vector<PolyNode>::iterator iter=out.begin();iter!=out.end();++iter){
        string item;
        if(iter->coef==0){
            item+="0";
            continue;
        }
        else if(iter->coef>1)item+=to_string(iter->coef);

        if(iter->coef==1&&iter->exp==0)item+="1";

        if(iter->exp==1)item+="x";
        else if(iter->exp>1)item+="x^"+to_string(iter->exp);
        // iter->exp==0 时，不用处理
        item+="+";
        output+=item;
    }
    output=output.substr(0,output.length()-1);
    cout<<output<<endl;
}