#pragma once

char* reverseVowels(char*);

typedef struct MyLinkedList MyLinkedList;

MyLinkedList* myLinkedListCreate();

int myLinkedListGet(MyLinkedList*, int);

void myLinkedListAddAtHead(MyLinkedList*, int);

void myLinkedListAddAtTail(MyLinkedList*, int);

void myLinkedListAddAtIndex(MyLinkedList*, int, int);

void myLinkedListDeleteAtIndex(MyLinkedList*, int);

void myLinkedListFree(MyLinkedList*);
