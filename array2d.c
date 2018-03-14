#include <stdio.h>
#define ROWS 3
#define COLS 4
void sum_rows(int ar[][COLS],int rows);
void sum_cols(int [][COLS],int);
int sum2d(int (*ar)[COLS],int);
int main(void){
    int FUCK[ROWS][COLS]={
        {2,4,6,8},
        {3,5,7,9},
        {12,10,8,6}
    };
    int tot=0;
    for(int r=0;r<ROWS;++r){
        for(int c=0;c<COLS;++c){
            printf("FUCK[%d][%d] :%d\n",r,c,FUCK[r][c]);
        }
    }
    sum_rows(FUCK,ROWS);
    sum_cols(FUCK,ROWS);
    printf("Sum of all elements = %d\n",sum2d(FUCK,ROWS));
    return 0;
}
void sum_rows(int ar[][COLS],int rows){
    int r;
    int c;
    int tot;
    for (r=0;r<rows;++r){
        tot=0;
        for(c=0;c<COLS;++c)tot+=ar[r][c];
        printf("row %d:sum = %d\n",r,tot);
    }
}
void sum_cols(int ar[][COLS],int rows){
    //int tot;
    for(int c=0;c<COLS;++c){
        int tot=0;
        for(int r=0;r<rows;++r){
            tot+=ar[r][c];
        }
        printf("cols %d:sum = %d\n",c,tot);
    }
}
int sum2d(int ar[][COLS],int rows){
    int tot=0;
    for(int r=0;r<rows;++r){
        for(int c=0;c<COLS;++c){
            tot+=ar[r][c];
        }
    }
    return tot;
}