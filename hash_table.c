#include <stdio.h>
#include <stdlib.h>
typedef struct _HashNode{
    int key;
    int index;
}HashNode;

typedef struct _HashMap{
    int size;
    HashNode ** stroage;
}HashMap;

HashMap *hash_create(int size);
void hash_destory(HashMap *hashmap);
void hash_set(HashMap *HashMap,int key ,int index);
HashNode * hash_get(HashMap *hashmap,int key);

HashMap *hash_create(int size){
    HashMap *hashmap=malloc(sizeof(*hashmap));
    hashmap->size=size;
    hashmap->stroage=(HashNode **)calloc(size,sizeof(HashNode*));
    return hashmap;
}
void hash_destory(HashMap *hashmap){
    for(int i=0;i<hashmap->size;++i){
        free(hashmap->stroage[i]);
    }
    free(hashmap->stroage);
    free(hashmap);
}
void hash_set(HashMap *hashmap,int key,int index){
    int hash=abs(key)%hashmap->size;//hash func
    HashNode *node;
    while(node=hashmap->stroage[hash]){
        hash=(hash+1)%hashmap->size;
    }
    node=malloc(sizeof(HashNode));
    node->key=key;
    node->index=index;
    hashmap->stroage[hash]=node;
}
HashNode * hash_get(HashMap *hashmap,int key){
    int hash=abs(key)%hashmap->size;
    HashNode*node;
    while(node=hashmap->stroage[hash]){
        if(node->key==key)return node;
        hash=(hash+1)%hashmap->size;
    }
    return NULL;
}