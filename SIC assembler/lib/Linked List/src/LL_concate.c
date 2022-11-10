#include "linked_list.h"

llNode_t * LL_concate(llNode_t *srcList, llNode_t * dstList)//(將srcList 串在dstList之後)
{
	llNode_t *tail = LL_get_tail(dstList);
	tail->next = srcList->next;
	srcList->next = NULL;
	LL_free_head(srcList);
}
