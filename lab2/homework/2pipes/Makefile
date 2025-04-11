all: a b pipes

a: program_a.c
	g++ -pthread -o program_a program_a.c
	
b: program_b.c
	g++ -pthread -o program_b program_b.c

clean: program_a program_b
	rm program_a program_b
	rm fifo_to_A fifo_to_B

pipes:
	mkfifo fifo_to_A
	mkfifo fifo_to_B
