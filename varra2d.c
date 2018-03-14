#include <stdio.h>
#define ROWS 3
#define COLS 4
int sum2d(int rows,int cols,int ar[rows][cols]);
int main(void){
    int rs=3;
    int cs=10;
    int fuck[ROWS][COLS]={
        {2,4,6,8},
        {3,5,7,9},
        {12,10,8,6}
    };
    int morefuck[ROWS-1][COLS+2]={
        {20,30,40,50,60,70},
        {5,6,7,8,9,10}
    };
    int varrs[rs][cs];//variable_length array
    for(int i=0;i<rs;i++){
        for(int j=0;j<cs;++j)
        varrs[i][j]=i*j+j;
    }
    printf("3*5 array\n");
    printf("Sum of all elements = %d\n",sum2d(ROWS,COLS,fuck));
    printf("2*6 array\n");
    printf("Sum of all elements = %d\n",sum2d(ROWS-1,COLS+2,morefuck));
    printf("3*10 VLA\n");
    printf("Sum of all elements = %d\n",sum2d(rs,cs,varrs));
    
    return 0;
}
int sum2d(int rows,int cols,int ar[rows][cols]){
    int tot=0;
    for(int r=0;r<rows;++r){
        for(int c=0;c<cols;++c)
        tot+=ar[r][c];
    }
    return tot;
}