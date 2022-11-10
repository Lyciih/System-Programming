#include "linked_list.h"

llNode_t * LL_get_tail(llNode_t *head)
{
	llNode_t *current = head;
	if(current->next == NULL)
	{
		return current;
	}
	else
	{
		while(current->next != NULL)
		{
			current = current->next;
		}
	}
	return current;
}
