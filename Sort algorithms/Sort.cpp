#include <iostream>
#include <utility>
#include <vector>
#include <type_traits>
#include <queue>

using namespace std;

int partition(vector<int> &arr,int beg,int end){
    int pivot=arr[(beg+end)/2];
    int i=beg-1;
    int j=end+1;
    while(true){
        do{
            ++i;
        }while(arr[i]<pivot);
        do{
            --j;
        }while(arr[j]>pivot);
        if(i>=j)return i;
        std::swap(arr[i],arr[j]);
    }
}


void quick_sort(vector<int> &arr,int beg,int end){
    if(beg>=end)return ;
    int q=partition(arr,beg,end);
    quick_sort(arr,beg,q);
    quick_sort(arr,q+1,end);
}

void merge(vector<int> &tmp,vector<int> &arr,int b1,int e1,int b2,int e2){
    int i=b1;
    int start=b1;
    for(;b1<=e1&&b2<=e2;){
        if(arr[b1]<arr[b2])tmp[i++]=arr[b1++];
        else tmp[i++]=arr[b2++];
    }
    while (b1<=e1)
    {
        tmp[i++]=arr[b1++];
    }
    while(b2<=e2){
        tmp[i++]=arr[b2++];
    }
    for(int i=start;i<=e2;++i){
        arr[i]=tmp[i];
    }
    
}

void merge_sort(vector<int> &tmp,vector<int> &arr,int beg,int end){
    if(beg>=end)return ;
    int mid=(beg+end)/2;
    merge_sort(tmp,arr,beg,mid);
    merge_sort(tmp,arr,mid+1,end);
    merge(tmp,arr,beg,mid,mid+1,end);
}


void heap_sort(vector<int> &arr,int beg,int end){
    auto cmp=[](const int &a,const int &b){
        return a>b;
    };
    std::priority_queue<int,vector<int>,decltype(cmp)> max_heap(cmp,arr);
    vector<int> ret;
    while(!max_heap.empty()){
        ret.push_back(max_heap.top());
        max_heap.pop(); // 自动heapfy()
    }
    arr=std::move(ret);
}

void bubble_sort(vector<int> &arr,int beg,int end){
    for(int i=end;i>-1;--i){
        for(int j=0;j<i;++j){
            if(arr[j]>arr[j+1])swap(arr[j],arr[j+1]);
        }
    }
}

void insert_sort(vector<int> &arr,int beg,int end){
    if(beg>=end)return ;
    for(int i=beg+1;i<=end;++i){
        if(arr[i]<arr[i-1]){
            int val=arr[i];
            int j;
            for(j=i;j>0&&arr[j-1]>=val;--j){
                arr[j]=arr[j-1];
            }
            arr[j]=val;
        }
    }
}

void shell_sort(vector<int> &arr,int beg,int end){
    if(beg>=end)return ;
    int size=end-beg+1;
    for(int step=size/2;step>=1;step/=2){
        for(int i=beg+step;i<=end;i+=step){
            if(arr[i]<arr[i-step]){
                int val=arr[i];
                int j;
                for(int j=i;j>beg&&arr[j-step]>val;j-=step){
                    arr[j]=arr[j-step];
                }
                arr[j]=val;
            }
        }
    }
}


int main(){
    vector<int> arr={1,23,4,9,2};
    // vector<int> tmp(arr);
    shell_sort(arr,0,arr.size()-1);
    for(auto iter:arr){
        cout<<iter<<endl;
    }
}

