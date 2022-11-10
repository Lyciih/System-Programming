#include "linked_list.h"

void LL_delete_next(llNode_t * node)//(從node所在的 Linked List 中刪除此點)
{
	llNode_t * temp;
	if(node->next == NULL)
	{
		printf("there are not have next node");
	}
	else
	{
		temp = node->next; 
		node->next = node->next->next;
		temp->next = NULL;
	}
}
