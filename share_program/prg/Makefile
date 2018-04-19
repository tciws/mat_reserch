test: kaiseki.o comp.o getsym.o struct_cal.o
	#gcc -o test kaiseki.o comp.o
	gcc -L${HOME}/exam/prg/lib -lics -o test.exe kaiseki.o comp.o getsym.o struct_cal.o
kaiseki.o:	kaiseki.c
	#gcc -c kaiseki.c
	gcc -c  -I${HOME}/exam/prg/include kaiseki.c
comp.o:	comp.c
	#gcc -c comp.c
	gcc -c  -I${HOME}/exam/prg/include comp.c
getsym.o:	getsym.c
	#gcc -c comp.c
	gcc -c  -I${HOME}/exam/prg/include getsym.c
struct_cal.o:	struct_cal.c
	#gcc -c comp.c
	gcc -c  -I${HOME}/exam/prg/include struct_cal.c
test2: kaiseki.o comp.o getsym.o
clean:
	rm kaiseki.o comp.o getsym.o
