#include "linked_list.h"

void LL_free_head(llNode_t *head)
{
	memset(head, 0, sizeof(llNode_t));
	free(head);
	head = NULL;
	printf(">>> The head of the source list has been freed (response from LL_free_head )\n");
}
