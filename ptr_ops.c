//ptr_ops --- pointer operation
#include <stdio.h>
int main(void){
    int urn[5]={100,200,300,400,500};
    int *ptr1=urn,*ptr2=&urn[2];
    printf("pointer value,dereference pointer,pointer address:\n");
    printf("ptr1= %p,*ptr1= %d,&ptr1= %p\n",ptr1,*ptr1,&ptr1);
    int *ptr3=ptr1+4;
    printf("\nadding an int to a pointer:\n");
    printf("ptr1+4= %p,*(ptr1+4)= %d\n",ptr1+4,*(ptr1+4));
    ptr1++;
    printf("\nvalues after ptr1++:");
    printf("ptr1= %p,*ptr1= %d,&ptr1= %p\n",ptr1,*ptr1,&ptr1);
    ptr2--;
    printf("\nvalues after ptr2--:");
    printf("ptr2= %p,*ptr2 =%d,&ptr2 =%p\n",ptr2,*ptr2,&ptr2);
    --ptr1;
    ++ptr2;
    printf("Pointers to reset to original values:\n");
    printf("ptr1= %p,ptr2= %p",ptr1,ptr2);
    //pointer deduct another one
    printf("\nptr3--: %d",*(--ptr3));
    printf("\nsubtracting one pointer from another:\n");
    printf("ptr2 =%p,ptr1 %p,ptr2-ptr1= %ld\n",ptr2,ptr1,ptr2-ptr1);
    printf("\nsubtracting an int from a pointer:\n");
    printf("ptr3 =%p,ptr3-2 =%p,ptr3-1 =%p\n",ptr3,ptr3-2,ptr3-1);
    return 0;
}