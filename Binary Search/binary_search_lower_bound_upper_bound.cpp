#include <iostream>
#include <vector>

/*-----------------------------------
*   #include <algorithm>
*   这三个涉及到二分搜索的函数,binary_search,lower_bound,upper_bound
*   三者的区间都是左闭右开[first,last)
*   lower_bound(first,last,target)：返回第一个不小于targe的元素
*   upper_bound(first,last,target)：返回第一个大于target的位置
*------------------------------------*/

using namespace std;

template<typename _ElemType>
int binary_search(vector<_ElemType> &arr,_ElemType target){
    int lo=0,hi=arr.size()-1;
    int mid;
    while(lo<=hi){
        mid=(lo+hi)/2;  // 即向下取整，或写成 lo+(hi-lo)/2
        if(arr[mid]==target)return mid;
        else if(arr[mid]<target)lo=mid+1;
        else hi=mid-1;
    }
    return lo;
}

template<typename _ElemType>
int lower_bound(vector<_ElemType> &arr,_ElemType target){
    int lo=0,hi=arr.size()-1;
    int mid;
    while(lo<=hi){
        mid=(lo+hi)/2;  // 即向下取整，或写成 lo+(hi-lo)/2
        if(arr[mid]<target)lo=mid+1;    
        else hi=mid-1;  // 相等时，向左移动
    }
    return lo;
}

template<typename _ElemType>
int upper_bound(vector<_ElemType> &arr,_ElemType target){
    int lo=0,hi=arr.size()-1;
    int mid;
    while(lo<=hi){
        mid=(lo+hi)/2;  // 即向下取整，或写成 lo+(hi-lo)/2
        if(arr[mid]<=target)lo=mid+1; // 相等时，向右移动
        else hi=mid-1; 
    }
    return lo;
}

int main(){
    vector<int> arr;
    for(int i=0;i<10;++i)arr.push_back(i);
    cout<<lower_bound<int>(arr,-1);
}