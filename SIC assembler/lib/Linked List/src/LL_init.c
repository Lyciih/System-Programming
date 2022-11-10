#include "linked_list.h"

llNode_t * LL_init()
{
	llNode_t *init = (llNode_t*)malloc(sizeof(llNode_t));
	if(init == NULL)
	{
		printf(">>> Insufficient space (response from LL_init )\n");
	}
	else
	{
		init->next = NULL;
	}
	return init;
}
