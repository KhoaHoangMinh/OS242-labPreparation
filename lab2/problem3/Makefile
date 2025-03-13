CC = gcc

all:	sum_serial sum_multi_thread

sum_serial: sum_serial.c
	$(CC) -o sum_serial sum_serial.c

sum_multi_thread: sum_multi_thread.c
	$(CC) -pthread -o sum_multi_thread sum_multi_thread.c

clean:
	rm -f sum_serial sum_multi_thread

