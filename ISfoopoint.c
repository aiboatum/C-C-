#include <stdio.h>
#define COLS 3
int Isfoo(int (*)[COLS],int ,int ,int );
int Isfoo(int a[][COLS],int rows,int r,int c){
        for(int j=0;j<COLS;++j){
        if(a[r][c]<a[r][j])return 0;
        }
        for(int i=0;i<rows;i++){
        if(a[r][c]>a[i][c])return 0;
        }
        return 1;
}
int main(void){
    int a[][3]={{1,2,3},
    {2,34,5},
    {1,2,3}
    };
    for(int i=0;i<3;i++){
        for(int j=0;j<3;++j)  
        if(Isfoo(a,3,i,j))printf("rows: %d cols: %d\n",i+1,j+1);   
    }
}