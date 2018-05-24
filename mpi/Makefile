test: dp.o branch_and_bound.o
	gcc -o test.exe dp.o branch_and_bound.o
branch_and_bound.o: branch_and_bound.c
	gcc -O2 -c branch_and_bound.c
dp.o:	dp.c
	gcc -O2 -c dp.c
test2: dp.o
clean:
	rm dp.o branch_and_bound.o
