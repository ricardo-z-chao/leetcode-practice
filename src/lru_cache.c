/**
 * @brief Leetcode 146. LRU 缓存
 * @link https://leetcode.cn/problems/lru-cache/
 * @note 这道题需要使用一个哈希表+双向链表来维护 LRU 缓存的数据结构，
 *       哈希表用于快速查找键对应的节点，双向链表用于维护节点的访问顺序。
 *       靠近链表头部的节点表示最近使用的节点，靠近链表尾部的节点表示最久未使用的节点。
 *       当缓存容量达到上限时，需要删除链表尾部的节点以腾出空间。
 *       不使用单向链表而选择双向链表是因为删除节点时需要将前后节点连接起来。
 */

#include "leetcode/lru_cache.h"

#include <stdlib.h>

struct node {
  int key;
  int value;
  struct node* prev;
  struct node* next;
};

struct hashTableEntry {
  struct node* node;
  struct hashTableEntry* next;
};

/**
 * @brief 哈希函数，将键映射到哈希表的索引
 * @param[in] key 键
 * @param[in] capacity 哈希表容量
 * @return 哈希表索引
 */
static int hash(int key, int capacity) {
  return key % capacity;
}

/**
 * @brief 创建 LRUCache 对象
 * @param[in] capacity 缓存容量
 * @return LRUCache 对象指针
 */
LRUCache* lRUCacheCreate(int capacity) {
  LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
  cache->capacity = capacity;
  cache->size = 0;
  struct node* dummyHead = (struct node*)malloc(sizeof(struct node));
  struct node* dummyTail = (struct node*)malloc(sizeof(struct node));
  dummyHead->prev = NULL;
  dummyHead->next = dummyTail;
  dummyTail->prev = dummyHead;
  dummyTail->next = NULL;
  cache->linkedListHead = dummyHead;
  cache->linkedListTail = dummyTail;
  cache->hashTable = malloc(sizeof(struct hashTableEntry) * capacity);
  for (int i = 0; i < capacity; i++) {
    cache->hashTable[i].node = NULL;
    cache->hashTable[i].next = NULL;
  }
  return cache;
}

/**
 * @brief 获取缓存中指定键的值
 * @param[in] obj LRUCache 对象指针
 * @param[in] key 键
 * @return 键对应的值，如果键不存在则返回 -1
 */
int lRUCacheGet(LRUCache* obj, int key) {
  int index = hash(key, obj->capacity);
  struct hashTableEntry* entry = obj->hashTable[index].next;
  while (entry && entry->node->key != key) {
    entry = entry->next;
  }
  if (entry) {
    /* 将节点移动到链表头部，表示最近使用 */
    struct node* node = entry->node;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = obj->linkedListHead->next;
    node->prev = obj->linkedListHead;
    obj->linkedListHead->next->prev = node;
    obj->linkedListHead->next = node;
    return node->value;
  } else {
    return -1;
  }
}

/**
 * @brief 将键值对插入缓存中，如果键已存在则更新值，并将节点移动到链表头部，表示最近使用。
 *        如果缓存容量达到上限，则删除链表尾部的节点以腾出空间。
 * @param[in] obj LRUCache 对象指针
 * @param[in] key 键
 * @param[in] value 值
 */
void lRUCachePut(LRUCache* obj, int key, int value) {
  int index = hash(key, obj->capacity);
  struct hashTableEntry* entry = obj->hashTable[index].next;
  while (entry && entry->node->key != key) {
    entry = entry->next;
  }
  if (entry) {
    /* 键已存在，更新值并将节点移动到链表头部 */
    struct node* node = entry->node;
    node->value = value;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = obj->linkedListHead->next;
    node->prev = obj->linkedListHead;
    obj->linkedListHead->next->prev = node;
    obj->linkedListHead->next = node;
  } else {
    /* 键不存在，创建新节点并插入链表头部 */
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->key = key;
    newNode->value = value;
    newNode->prev = obj->linkedListHead;
    newNode->next = obj->linkedListHead->next;
    obj->linkedListHead->next->prev = newNode;
    obj->linkedListHead->next = newNode;

    /* 将新节点插入哈希表 */
    struct hashTableEntry* newEntry = (struct hashTableEntry*)malloc(sizeof(struct hashTableEntry));
    newEntry->node = newNode;
    newEntry->next = obj->hashTable[index].next;
    obj->hashTable[index].next = newEntry;

    obj->size++;
    if (obj->size > obj->capacity) {
      /* 缓存容量达到上限，删除链表尾部的节点 */
      struct node* deleteNode = obj->linkedListTail->prev;
      deleteNode->prev->next = obj->linkedListTail;
      obj->linkedListTail->prev = deleteNode->prev;
      /* 同时从哈希表中删除尾部节点对应的键 */
      int deleteIndex = hash(deleteNode->key, obj->capacity);
      struct hashTableEntry* preEntry = &obj->hashTable[deleteIndex];
      while (preEntry->next && preEntry->next->node != deleteNode) {
        preEntry = preEntry->next;
      }
      if (preEntry) {
        struct hashTableEntry* deleteEntry = preEntry->next;
        preEntry->next = deleteEntry->next;
        free(deleteEntry);
        free(deleteNode);
        obj->size--;
      }
    }
  }
}

/**
 * @brief 释放 LRUCache 对象占用的内存
 */
void lRUCacheFree(LRUCache* obj) {
  while (obj->linkedListHead) {
    struct node* temp = obj->linkedListHead;
    obj->linkedListHead = obj->linkedListHead->next;
    free(temp);
  }
  for (int i = 0; i < obj->capacity; i++) {
    while (obj->hashTable[i].next) {
      struct hashTableEntry* temp = obj->hashTable[i].next;
      obj->hashTable[i].next = obj->hashTable[i].next->next;
      free(temp);
    }
  }
  free(obj->hashTable);
  free(obj);
}
