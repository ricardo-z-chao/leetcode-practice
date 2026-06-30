#pragma once

typedef struct hashTableEntry* HashTable;

typedef struct {
  int capacity;
  int size;
  struct node* linkedListHead;  // 指向双向链表的头节点
  struct node* linkedListTail;  // 指向双向链表的尾节点
  HashTable hashTable;  // 哈希表，用于快速查找键对应的节点
} LRUCache;

LRUCache* lRUCacheCreate(int capacity);

int lRUCacheGet(LRUCache* obj, int key);

void lRUCachePut(LRUCache* obj, int key, int value);

void lRUCacheFree(LRUCache* obj);
