test: hello.o
	mpicc -O2 hello.o -lmpich -L/usr/lib64/mpich/lib
hello.o:	hello.c
	mpicc -O2 -c hello.c -lmpich -L/usr/lib64/mpich/lib
test2: hello.o
clean:
	rm hello.o
