

SRCS_C = \
	LL_add_first.c \
	LL_add_tail.c \
	LL_addto_next.c \
	LL_concate.c \
	LL_delete_next.c \
	LL_free_head.c \
	LL_get_tail.c \
	LL_init.c \
	LL_isEmpty.c \
	LL_next_node.c \
	LL_num_nodes.c \
	

TEST_C = \
	test.c \

OBJS = $(SRCS_C:.c=.o)
TEST = $(TEST_C:.c=.o)

INCLUDE = -I ./include


all: test

test: liblinked_list.a ${TEST} 
	gcc -o test  $(INCLUDE) test.o -L . -l linked_list  


%.o : %.c
	gcc -c -o $@ $< $(INCLUDE)

%.a : ${OBJS}
	ar -rcs liblinked_list.a  $^ 

%.o : ./src/%.c 
	gcc -c -o $@ $< $(INCLUDE)

.PHONY: clean run
clean:
	rm test *.o *.a

run:
	./test
