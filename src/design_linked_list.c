/**
 * @brief LeetCode 707. 设计链表
 *
 * 链表的基本操作，包括：
 * - myLinkedListCreate: 创建链表
 * - myLinkedListGet: 获取指定索引的节点值
 * - myLinkedListAddAtHead: 在头部添加节点
 * - myLinkedListAddAtTail: 在尾部添加节点
 * - myLinkedListAddAtIndex: 在指定索引添加节点
 * - myLinkedListDeleteAtIndex: 删除指定索引的节点
 * - myLinkedListFree: 释放链表内存
 *
 * @link https://leetcode.cn/problems/design-linked-list/description/
 */

#include <stdlib.h>

/**
 * @struct MyLinkedList
 *
 * 定义链表的节点
 */
typedef struct MyLinkedList {
  int val; /**< 节点存储的整数值 */
  struct MyLinkedList* next; /**< 指向下一个节点的指针 */
} MyLinkedList;

/**
 * @brief 创建一个新链表
 *
 * 初始化一个空链表，返回链表头指针，首节点为虚拟头节点，不存储实际数据
 *
 * @return 返回新创建的链表头指针，失败返回 NULL
 */
MyLinkedList* myLinkedListCreate() {
  return calloc(1, sizeof(MyLinkedList));
}

/**
 * @brief 获取链表中下标为 index 的节点的值。如果下标无效，则返回 -1
 * @param[in] obj   头节点指针
 * @param[in] index 要获取的节点索引（从0开始）
 * @return 返回指定索引位置的节点值，索引无效返回 -1
 */
int myLinkedListGet(MyLinkedList* obj, int index) {
  MyLinkedList** current = &obj->next;
  for (int i = 0; i < index && *current != NULL; i++) {
    current = &(*current)->next;
  }
  return (*current) == NULL ? -1 : (*current)->val;
}

/**
 * @brief 将一个值为 val
 * 的节点插入到链表中第一个元素之前。在插入完成后，新节点会成为链表的第一个节点
 * @param[in] obj 头节点指针
 * @param[in] val 要添加的节点值
 */
void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
  MyLinkedList* node = calloc(1, sizeof(MyLinkedList));
  node->val = val;
  node->next = obj->next;
  obj->next = node;
}

/**
 * @brief 将一个值为 val 的节点追加到链表中作为链表的最后一个元素
 * @param[in] obj 头节点指针
 * @param[in] val 要添加的节点值
 */
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
  while (obj->next != NULL) obj = obj->next;
  MyLinkedList* node = calloc(1, sizeof(MyLinkedList));
  node->val = val;
  obj->next = node;
}

/**
 * @brief 将一个值为 val 的节点插入到链表中下标为 index 的节点之前
 *        如果 index 等于链表的长度，那么该节点会被追加到链表的末尾
 *        如果 index 比长度更大，该节点将不会插入到链表中
 * @param[in] obj   链表指针
 * @param[in] index 要插入的位置索引
 * @param[in] val   要添加的节点值
 */
void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
  MyLinkedList** current = &obj->next;
  int i = 0;
  while (i < index && *current != NULL) {
    current = &(*current)->next;
    i++;
  }
  /* 索引越界 */
  if (i < index) return;
  MyLinkedList* node = calloc(1, sizeof(MyLinkedList));
  node->val = val;
  node->next = *current;
  *current = node;
}

/**
 * @brief 如果下标有效，则删除链表中下标为 index 的节点
 * @param[in] obj   头节点指针
 * @param[in] index 要删除的节点索引
 */
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
  MyLinkedList** current = &obj->next;
  int i = 0;
  while (i < index && *current != NULL) {
    current = &(*current)->next;
    i++;
  }
  /* 索引越界 */
  if (i < index || *current == NULL) return;
  MyLinkedList* releasedNode = *current;
  *current = (*current)->next;
  free(releasedNode);
}

/**
 * @brief 释放链表占用的所有内存
 *
 * 遍历链表并释放所有节点的内存，防止内存泄漏
 *
 * @param[in] obj 头节点指针
 */
void myLinkedListFree(MyLinkedList* obj) {
  while (obj != NULL) {
    MyLinkedList* releasedNode = obj;
    obj = obj->next;
    free(releasedNode);
  }
}
