#include <string>
#include <vector>
#include <iostream>
#include <string.h> // strtok
#include <sstream>

using namespace std;

// 调用c库中的strtok
// string.c_str()转换未const char *
// 可以接收多个分隔符，较为灵活
void split(vector<string> &token,char * str,const char *delim=" "){
    token.clear();
    char *token_str=strtok(str,delim);
    while(token_str){
        token.push_back(string(token_str));
        token_str=strtok(NULL,delim);
    }
}

// c++，string成员函数实现，如find，find_first_not_of等
void split(const string &s,vector<string> &tokens,const string& delim = " "){
    tokens.clear();
    // find_first_not_of是可以接收多个查找元素的，即delim是string类型
    size_t lastpos=s.find_first_not_of(delim,0);
    // find_first_not_of lambda实现如下
    // auto string_find_first_not_of=[s,delim](size_t pos=0)->size_t{
    //     for(size_t i=pos;i<s.size();++i)if(s[i]!=delim)return i;
    // };
    size_t pos=s.find_first_of(delim,lastpos);   // 从lastpos开始查询，第一个分隔符的位置
    while(lastpos!=string::npos){   
        tokens.emplace_back(s.substr(lastpos,pos-lastpos));
        lastpos=s.find_first_not_of(delim,pos);
        pos=s.find_first_of(delim,lastpos);
    }
}

// stringstream 实现
// 只需要单个分隔符
void split(vector<string> &token,const string &str,const char delim){
    token.clear();
    stringstream ss(str);
    string item;
    while(getline(ss,item,delim)){
        token.push_back(item);
    }
}

int main(){
    vector<string> output;
    string str;
    getline(cin,str);
    split(str,output,"+-");
    for(auto iter:output)cout<<iter<<endl;

    // strtok会改变原来的字符串
    // split(output,const_cast<char *>(str.c_str()),"+-");
    // for(auto iter:output)cout<<iter<<endl;
    
    
    // getline(cin,str);
    // split(output,str,'+');
    // for(auto iter:output)cout<<iter<<endl;
    
}