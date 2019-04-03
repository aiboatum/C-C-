#include <stdio.h>
#define COLS 4
int main(void){
    int sum2d(const int [][COLS],int rows);
    int sum(const int [],int );
    int total1,total2,total3;
    int *pt1;
    int (*pt2)[COLS];
    pt1=(int [2]){10,20};
    pt2=(int [2][COLS]){{1,2,3,-9},{4,5,6,-8}};
    printf("total1 = %d",sum(pt1,2));
    putc('\n',stdout);
    printf("total2 = %d",sum2d(pt2,2));
    puts("");
    printf("total3 = %d\n",sum((int []){4,4,4,5,5,5},6));
    return 0;
}
int sum(const int *ar,int n){
    int tot=0;
    for(int i=0;i<n;++i)
    tot+=ar[i];
    return tot;
}
int sum2d(const int ar[][COLS],int rows){
    int tot=0;
    for(int r=0;r<rows;++r)
    for(int c=0;c<COLS;c++)
    tot+=ar[r][c];
    return tot;
}
