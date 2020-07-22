#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> solution(n,std::string(n,'-'));
        solve(res,solution,n,0,0,0);
        return res;
    }
    void solve(vector<vector<string>> &res,vector<string> &solution,int n,int row, int ld ,int rd){
        if(((1<<n)-1)==row){
            res.push_back(solution);
            return;
        }
        int D= ((1<<n)-1)&(~(row|rd|ld));
        while(D){
            int bit=D&(~D+1);
            solution[rowcount(row)][n-colcount(bit)]='Q';
            solve(res,solution,n,row|bit,(ld|bit)<<1,(rd|bit)>>1);
            solution[rowcount(row)][n-colcount(bit)]='-';
            D=D^bit;
        }
    }
    int rowcount(int row){
        int cnt=0;
        while(row){
            cnt+=row&0x1;
            row>>=1;
        }
        return cnt;
    }
    int colcount(int col){
        int cnt=0;
        while(col){
            cnt++;
            col>>=1;
        }
        return cnt;
    }
};
int main(){
    int n=8;
    vector<vector<string> > out=Solution().solveNQueens(n);
    for(auto vec:out){
        for(auto str:vec){
            cout<<str<<endl;
            
        }
        cout<<endl;
    }
}