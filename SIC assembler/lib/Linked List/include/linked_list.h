#ifndef DLLSPEC_H_INCLUDED
#define DLLSPEC_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
    struct node *next;
} llNode_t;


llNode_t * LL_init(); //建構一個空的 list

int LL_isEmpty(const llNode_t *head);// head 是否為空的list

llNode_t * LL_next_node(const llNode_t * node);//(下一個節點)

unsigned int LL_num_nodes(const llNode_t *head);//計算List中有幾個node

void LL_add_first(llNode_t * new_node, llNode_t * head);//(將新new_node加入到head List 的第一個)

void LL_add_tail(llNode_t * new_node, llNode_t *head);//(將新new_node加入到head List 的最後一個)

void LL_addto_next(llNode_t *new_node, llNode_t *node);// (將新new_node加入到node的後一個)

void LL_delete_next(llNode_t * node);//(從node所在的 Linked List 中刪除此點)

llNode_t * LL_concate(llNode_t *srcList, llNode_t * dstList);//(將srcList 串在dstList之後)



//-------------以下是自己加的function----------------------------------------------------------------------------------------------------------------------

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define return_to_user_struct_pointer(USER_STRUCT, MEMBER_NAME, MEMBER_POINT)  ((USER_STRUCT *)((size_t)MEMBER_POINT - offsetof(USER_STRUCT, MEMBER_NAME)))

llNode_t *LL_get_tail(llNode_t *head);//取得list的尾巴

void LL_free_head(llNode_t *head);//釋放空的head

#endif
