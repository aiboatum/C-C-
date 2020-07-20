#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/*----------------------------------
*       C：使用数组实现MinStack
*-----------------------------------*/


typedef struct _pair {
    int first;
    int second;
}pair;

typedef struct _MinStack {
    int top; 
    struct _pair * data;       
    int capacity;
}MinStack;

// typedef struct _pair pair;
// typedef struct _MinStack MinStack;

/** initialize your data structure here. */
MinStack* minStackCreate(int capacity) {
    MinStack * minstack=(MinStack *)malloc(sizeof(*minstack));
    minstack->data=(pair *)malloc(capacity*sizeof(*(minstack->data)));
    minstack->top=-1;
    minstack->capacity=capacity;
    return minstack;
}

int Isfull(MinStack * obj){
    return obj->top==obj->capacity-1;
}

int IsEmpty(MinStack *obj){
    return obj->top==-1;
}

int _min(int x,int y){
    return x<y?x:y;
}

void minStackPush(MinStack* obj, int x) {
    if(Isfull(obj))return ;

    if(IsEmpty(obj)){
        obj->data[++obj->top].first=x;
        obj->data[obj->top].second=x;
    }
    else {
        obj->data[++obj->top].first=x;
        obj->data[obj->top].second=_min(x,obj->data[obj->top-1].second);
    }
}

void minStackPop(MinStack* obj) {
    if(IsEmpty(obj)) return ;
    obj->top--;
}

int minStackTop(MinStack* obj) {
    if(IsEmpty(obj))return INT_MAX;
    return obj->data[obj->top].first;
}

int minStackGetMin(MinStack* obj) {
    if(IsEmpty(obj))return INT_MAX;
    return obj->data[obj->top].second;
}
void minStackFree(MinStack* obj) {
    free(obj->data);
    free(obj);
}

int main(){
    int maxsize=30;
    MinStack* obj = minStackCreate(maxsize);
    int x=20;
    minStackPush(obj, x);
    // minStackPop(obj);
    int param_3 = minStackTop(obj);
    int param_4 = minStackGetMin(obj);
    printf("%d,%d",param_3,param_4);
    minStackFree(obj);
}