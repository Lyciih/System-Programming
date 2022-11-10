#include "linked_list.h"

void LL_add_tail(llNode_t * new_node, llNode_t *head)
{
	llNode_t *current = LL_get_tail(head);
	LL_addto_next(new_node, current);
}
