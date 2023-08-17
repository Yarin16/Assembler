all: first_pass.o labels.o main.o data_structers.o exceptions.o  functions.o statements.o second_pass.o  tools.o  pre_assembler.o
	gcc -g -ansi -pedantic -Wall first_pass.o labels.o main.o data_structers.o exceptions.o functions.o statements.o second_pass.o  tools.o  pre_assembler.o -o assembler


main.o: main.c  labels.h 
	gcc -c -ansi -pedantic -Wall main.c

first_pass.o: first_pass.c statements.h functions.h labels.h
	gcc -c -ansi -pedantic -Wall first_pass.c

labels.o: labels.c data_structers.h
	gcc -c -ansi -pedantic -Wall labels.c
	
data_structers.o: data_structers.c data_structers_structs.h exceptions.h
	gcc -c -ansi -pedantic -Wall data_structers.c

exceptions.o: exceptions.c
	gcc -c -ansi -pedantic -Wall exceptions.c

functions.o: functions.c data_structers.h
	gcc -c -ansi -pedantic -Wall functions.c

pre_assembler.o: pre_assembler.c data_structers.h
	gcc -c -ansi -pedantic -Wall pre_assembler.c

statements.o: statements.c exceptions.h data_structers.h
	gcc -c -ansi -pedantic -Wall statements.c

second_pass.o: second_pass.c data_structers.h tools.h
	gcc -c -ansi -pedantic -Wall second_pass.c

tools.o: tools.c labels.h
	gcc -c -ansi -pedantic -Wall tools.c


clear:
	rm first_pass.o labels.o main.o data_structers.o exceptions.o  functions.o pre_assembler.o statements.o second_pass.o tools.o linked_list.o assembler
