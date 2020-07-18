/***
 * Date: 2020-7-16
 * 主要功能：   根据输入的多项式，输出其导数
 * 例子：       输入: 100x-10x^2+100
 *            输出: -20x+100
 * 输入限制：    输入的系数可以为负数，次数不可以为负数
 ***/
#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <algorithm>
#include <stack>
#include <string>

using namespace std;


void trimLeftTrailingSpaces(string &input) {
    
    input.erase(input.begin(), find_if(input.begin(), input.end(), 
                [](const int ch)->bool{return !isspace(ch);}
                ));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), 
                [](const int ch)->bool{return !isspace(ch);}
                ).base(), input.end());
}

struct PolyNode {
    int  coef;
    int  exp;
    //struct PolyNode *next;
    PolyNode():coef(0),exp(0){}
    PolyNode(const int c,const int e):coef(c),exp(e){}
    friend ostream & operator<<(ostream &os,const PolyNode &rhs){
        os<<"coef = "<<rhs.coef<<", exp = "<<rhs.exp<<endl;
        return os;
    }
};


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
    sort(ret.begin(),ret.end(),
        [](const PolyNode &a,const PolyNode &b){
            return a.exp>b.exp;
        });
    return ret;
}

void split(const string &s,vector<string> &tokens,const string& delim = " "){
    tokens.clear();
    size_t lastpos=s.find_first_not_of(delim,0);
    size_t pos=s.find_first_of(delim,lastpos);   // 从lastpos开始查询，第一个分隔符的位置
    while(lastpos!=string::npos){   
        tokens.emplace_back(s.substr(lastpos,pos-lastpos));
        lastpos=s.find_first_not_of(delim,pos);
        pos=s.find_first_of(delim,lastpos);
    }
}

int main(){
    string input;
    getline(cin,input);
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);

    vector<PolyNode > Poly;

    if(input.empty())return -1;
    vector<string> item_vec;


    // 预处理input，每个-号前加一个分隔符'+'
    string processed_input;
    for(auto ch:input){
        if(ch=='-')processed_input.push_back('+');
        processed_input.push_back(ch);
    }

    split(processed_input,item_vec,string("+"));

    for(auto item:item_vec){
        auto x_pos=find_if(item.begin(),item.end(),[](const char ch){return ch=='x';});
        PolyNode node;
        if(x_pos==item.end()){  // 假设item不为空
            node.coef=atoi(item.c_str());
            node.exp=0;
        }
        else{
            if(item.begin()==x_pos) // 系数为1
                node.coef=1;   
            else {
                node.coef=atoi(string(item.begin(),x_pos).c_str());
            }
                

            if(item.end()-1==x_pos) // 次数为1
                node.exp=1;
            else 
                node.exp=atoi(string(x_pos+2,item.end()).c_str());
        }
        Poly.push_back(node);
    }

    
    vector<PolyNode> out=Difference(Poly);

    string output;
    for(vector<PolyNode>::iterator iter=out.begin();iter!=out.end();++iter){
        string item;
        // 处理系数
        // special case： 系数为0，不需要考虑次数
        
        if(iter->coef==0){
            item+="+0";
            output+=item;
            continue;
        }
        if(iter->coef>0)item+="+"+to_string(iter->coef);
        else item+=to_string(iter->coef);

        // 处理次数
        if(iter->exp==1)item+="x";
        else if(iter->exp!=0) item+="x^"+to_string(iter->exp);
        output+=item;
    }
    if(output[0]=='+')output=output.substr(1,output.length());
    cout<<output<<endl;
}