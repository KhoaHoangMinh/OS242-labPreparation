myapp: hello.o in.c
	gcc -o hello hello.o in.o

hello.o: hello.c
	gcc -c -o hello.o hello.c

in.o: in.c
	gcc -c -o in.o in.c

clean:
	rm -f *.o
	rm myapp

all: myapp
