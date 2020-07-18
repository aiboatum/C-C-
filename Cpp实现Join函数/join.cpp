#include <iostream>
#include <string>
#include <vector>
using namespace std;
string join(vector<string> &str,const string & delim = " "){
    string ret;
    for(auto iter=str.begin();iter!=str.end();++iter){
        ret += *iter;
        if(iter!=str.end()-1)ret += delim;
    }
    return ret;
}
 
int main() {
    vector<string> input(3);
    for(int i=0;i<3;++i)getline(cin,input[i]);

    cout<<join(input,"----->");
}