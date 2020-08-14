#include<iostream>
#include<cstring>
using namespace std ;
int main(){
    int a[101];
    memset(a,258, sizeof(a));
    for(int i=1;i<=10;i++)cout<<a[i]<<" ";
    return 0;
}