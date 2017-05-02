#ifndef _LISTNODE_H
#define _LISTNODE_H
#include <stdio.h>
#include <malloc.h>
typedef struct _ListNode {
	int value;
	struct ListNode * next;
} ListNode;

int pop(ListNode ** head);
ListNode * push(int data, ListNode *head);

#endif // !_LISTNODE_H