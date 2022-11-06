all: assembler2

assembler2:liblinked_list.a assembler2.c
	gcc assembler2.c -o assembler2 -Wall -L . -l linked_list 



.PHONY: clean
clean:
	rm -f *.o
	rm -f *.exe
	rm -f *.out

.PHONY: dump
dump:
	gcc -D assembler2


.PHONY: gdb
gdb:
	@echo "Press Ctrl-C and then input 'quit' to exit GDB"
	@echo "-------------------------------------------------------"
	assembler2 -s -S &
	gdb assembler2 -q -x gdbinit

.PHONY: run
run:
	@assembler2 test.s

