test: kaiseki.o comp.o getsym.o struct_cal.o express_fun.o
	#gcc -o test kaiseki.o comp.o
	gcc -L${HOME}/github/mat_reserch/share_program/prg/lib -lics -o test.exe kaiseki.o comp.o getsym.o struct_cal.o express_fun.o
kaiseki.o:	kaiseki.c
	#gcc -c kaiseki.c
	gcc -c  -I${HOME}/github/mat_reserch/share_program/prg/include kaiseki.c
comp.o:	comp.c
	#gcc -c comp.c
	gcc -c  -I${HOME}/github/mat_reserch/share_program/prg/include comp.c
express_fun.o:	express_fun.c struct_cal.c
	#gcc -c comp.c
	gcc -c  -I${HOME}/github/mat_reserch/share_program/prg/include express_fun.c struct_cal.c
struct_cal.o:	struct_cal.c
	#gcc -c comp.c
	gcc -c  -I${HOME}/github/mat_reserch/share_program/prg/include struct_cal.c
getsym.o:	getsym.c
	#gcc -c comp.c
	gcc -c  -I${HOME}/github/mat_reserch/share_program/prg/include getsym.c
test2: kaiseki.o comp.o getsym.o
clean:
	rm kaiseki.o comp.o getsym.o struct_cal.o express_fun.o
