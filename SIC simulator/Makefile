CFLAG = -I include

OBJ = \
	obj/sic_simulator.o \
	obj/load.o \
	obj/run.o \
	obj/show.o \
	obj/tool.o \


all : sic_simulator

sic_simulator : $(OBJ)
	gcc -Wall $(CFLAG) -o sic_simulator $^

./obj/%.o : ./src/%.c
	gcc -Wall $(CFLAG) -c -o $@ $<

PHONY : clean run

clean :
	rm -rf sic_simulator obj/*.o

run :
	./sic_simulator 3000