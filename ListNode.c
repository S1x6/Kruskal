#include "ListNode.h"

int pop(ListNode ** head)
{
	ListNode * ln = *head;
	int res = ln->value;
	*head = ln->next;
	free(ln);
	return res;
}

ListNode * push(int data, ListNode *head)
{
	ListNode * newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->value = data;
	newNode->next = head;
	return newNode;
}
