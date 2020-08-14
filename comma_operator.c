#include <stdio.h>
void hello(){
    printf("hello!\n");
}
int main(){
    int a[3][3]={
        (0,1,2),
        (3,4,5),
        (6,7,8)
    };
    // int i=0,j=0;
    int i=0;
    int j=0;
    while(i<5)
        printf("i=%d\n",i),
        hello(),
        ++i;
        
    for(i=0;i<3;i++)
        for(int j=0;j<3;++j){
            printf("a[%d][%d]= %d\n",i,j,a[i][j]);
        }
    return 0;
}