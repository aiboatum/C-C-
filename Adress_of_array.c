#include <stdio.h>
int main(void){
    int zippo[4][2]={{2,4},{6,8},{1,3},{5,7}};
    int array[]={1,23};
    printf("    zippo =%20p,zippo+1 =%+20p\n",zippo,zippo+1);
    printf("zippo[0]  =%20p,zippo[0]+1= %+17p\n",zippo[0],zippo[0]+1);
    printf(" *zippo   =%20p,*zippo+1 =%+19p\n",*zippo,*zippo+1);
    printf("&zippo[0] =%20p,&zippo+1 =%19p\n",&zippo[0],&zippo[0]+1);
    printf("&zippo[0][0] =%17p,&zippo[0][0]+1 =%17p\n",&zippo[0][0],
    &zippo[0][0]+1);
    //zippo[0]=xxx;//error: zippo[0] is constant 
    printf("array is  :%10p\n&array is :%10p\n*array is :%2d\n",array,&array,
    *array);
    //array[]:the value of array is equal to &array.
    //in this case,the expression '&array' represent that getting the address
    //of the array[]
    //and so:
    printf("array+1=%p\n&array+1=%p",array+1,&array+1);
    //array+1表示首地址+sizeof(元素类型)。
    //&array虽然值为数组首元素地址，
    //但类型为：类型 (*)[数组元素个数],所以&array+1大小为：首地址+sizeof(array)
    //数组名是只是个常量（一个值为数组首元素地址的常量），所以不能进行++或者--运算。
    //而常量更是无法取地址的，而之所以有&a，
    //其实这里的a的意义早已经不是当初那个数组名了，它此时代表了整个数组
    return 0;
}//结果显示以上值均相同，即均指向同一个地址