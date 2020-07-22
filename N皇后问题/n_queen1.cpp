#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        std::string row(n,'-');
        vector<string> solution(n,row);
        solve(res,solution,n,0);
        return res;
    }

    // 检查即将插入的row，col位置是否引发冲突
    // 即是否可以在row，col位置出放置queen
    // ！无需检查行是否冲突：因为枚举各行已经规避了放置的queen位于不同行
    bool check(vector<string> &s,int n, int row,int col){
        // 检查row，col是否合法，即是否越界
        if(row>=n||col>=n)return false;

        // 检查列是否存在冲突
        for(int r=0;r<row;++r){
            if(s[r][col]=='Q')return false;
        }
        // 对于对角线只需要检查以下两部分
        // 检查↖对角线
        for(int ld_row=row-1,ld_col=col-1;ld_row!=-1&&ld_col!=-1;--ld_row,--ld_col){
            if(s[ld_row][ld_col]=='Q')return false;
        }
        // 检查↗对角线
        for(int rd_row=row-1,rd_col=col+1;rd_row!=-1&&rd_col!=-1;--rd_row,++rd_col){
            if(s[rd_row][rd_col]=='Q')return false;
        }
        return true;
    }
    void solve(vector<vector<string>> &res,vector<string> &solution,int n,int row) {
        if(row==n)return;
            for(int c=0;c<n;++c){
                if(check(solution,n,row,c)){
                    solution[row][c]='Q';
                    if(row==n-1)res.push_back(solution);    // 此时说明已经找到一个解决方案
                    solve(res,solution,n,row+1);            // 递归进行
                    solution[row][c]='-';                   // 回溯点
                }
            }
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