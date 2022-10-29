all: assembler 

assembler: assembler.c
	gcc assembler.c -o assembler



.PHONY: clean
clean:
	rm -f *.o
	rm -f *.exe
	rm -f *.out

.PHONY: dump
dump:
	gcc -D assembler


.PHONY: gdb
gdb:
	@echo "Press Ctrl-C and then input 'quit' to exit GDB"
	@echo "-------------------------------------------------------"
	assembler -s -S &
	gdb assembler -q -x gdbinit

.PHONY: run
run:
	@assembler test.s

