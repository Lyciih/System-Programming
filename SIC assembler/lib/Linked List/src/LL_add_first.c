#include "linked_list.h"

void LL_add_first(llNode_t * new_node, llNode_t * head)
{
	if(head->next == NULL)
	{
		head->next = new_node;
	}
	else
	{
		new_node->next = head->next;
		head->next = new_node;			
	}
}
