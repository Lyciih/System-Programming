all : sic_simulator

sic_simulator : sic_simulator.c
	gcc -Wall -o sic_simulator $^



PHONY : clean run

clean :
	rm -rf sic_simulator sic_simulator.o

run :
	./sic_simulator 3000