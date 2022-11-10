#include "linked_list.h"

void LL_addto_next(llNode_t *new_node, llNode_t *node)
{
	new_node->next = node->next;
	node->next = new_node;
}
