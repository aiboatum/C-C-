
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct _MyHashSetNode {
    int key;
    struct _MyHashSetNode* next;
}MyHashSet_Node;

typedef struct {
    int size;
    MyHashSet_Node** bucket;
} MyHashSet;


MyHashSet* myHashSetCreate() {
    MyHashSet* hash_map = (MyHashSet*)malloc(sizeof(*hash_map));
    assert(hash_map);
    hash_map->size = 1000037;  // 大于1000000的素数
    hash_map->bucket = (MyHashSet_Node* *)calloc(hash_map->size,sizeof(*hash_map->bucket));
    assert(hash_map->bucket);
    assert(hash_map->bucket);
    // memset(hash_map->bucket,0,sizeof(hash_map->bucket));
    printf("[--------------------创建完成!----------------------]\n");
    return hash_map;
}

int hash_func(int key) {
    return key;
}

void myHashSetAdd(MyHashSet* obj, int key) {
    int hash_value = hash_func(key);
    MyHashSet_Node* position = obj->bucket[hash_value % obj->size];
    if (!position) {
        MyHashSet_Node* new_node = (MyHashSet_Node*)malloc(sizeof(*new_node));
        if (!new_node) {
            fprintf(stderr, "创建失败");
            return;
        }
        new_node->key = key;
        new_node->next = NULL;
        obj->bucket[hash_value % obj->size] = new_node;
        return;
    }
    MyHashSet_Node* next_node = position->next;
    while (next_node) {
        if (position->key == key)return;
        position->next = next_node;
        next_node = position->next;
    }
    // position是尾结点
    if (position->key == key)return;

    MyHashSet_Node* new_node = (MyHashSet_Node*)malloc(sizeof(*new_node));
    if (!new_node) {
        fprintf(stderr, "创建失败");
        return;
    }
    new_node->key = key;
    new_node->next = NULL;
    position->next = new_node;
}

void myHashSetRemove(MyHashSet* obj, int key) {
    int hash_value = hash_func(key);
    MyHashSet_Node* position = obj->bucket[hash_value % obj->size];
    if (!position)return;
    if (position->key == key) {   // 删除头结点
        obj->bucket[hash_value % obj->size] = position->next;
        free(position);
        return;
    }
    // 从第二个结点开始查找
    MyHashSet_Node* next_node = position->next;
    while (next_node && next_node->key != key) {
        position = next_node;
        next_node = position->next;
    }

    if (!next_node)return;   // 不存在key值的结点

    position->next = next_node->next;
    free(next_node);
}

/** Returns true if this set contains the specified element */
bool myHashSetContains(MyHashSet* obj, int key) {
    int hash_value = hash_func(key);
    MyHashSet_Node* position = obj->bucket[hash_value % obj->size];
    while (position && position->key != key)position = position->next;
    return position;
}

void FreeNode(MyHashSet_Node* node) {
    MyHashSet_Node* cur = node;
    while (cur) {
        MyHashSet_Node* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

void myHashSetFree(MyHashSet* obj) {
    for (int i = 0; i < obj->size; ++i) {
        if (obj->bucket[i]) {
            FreeNode(obj->bucket[i]);
        }
    }

    free(obj->bucket);
    free(obj);
    printf("\n[--------------------回收完成!----------------------]\n");
}
int main() {
    MyHashSet* obj = myHashSetCreate();
    myHashSetAdd(obj, 2);
    printf("%d\n", myHashSetContains(obj, 1));
    printf("%d\n", myHashSetContains(obj, 3));
    myHashSetAdd(obj, 2);
    printf("%d\n", myHashSetContains(obj, 2));
    myHashSetRemove(obj, 2);
    printf("%d\n", myHashSetContains(obj, 2));
    myHashSetFree(obj);

}