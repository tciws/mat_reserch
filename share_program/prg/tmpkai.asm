addi  R4,2
jmp main
proc:
push  R5
loadr  R5,R4
addi  R4,7
loadi  R0,1
store  R0,1(BR)
loadr  R3,R0
load  R0,-2(BR)
loadr  R2,R0
cmpr  R3,R2
jgt  L1
load  R0,-4(BR)
store  R0,5(BR)
loadi  R0,0
store  R0,6(BR)
load  R0,-3(BR)
store  R0,10005
loadi  R0,1
store  R0,10006
load  R0,10005
subr  R0,R1
store  R0,2(BR)
loadi  R0,0
store  R0,7(BR)
L2:
load  R0,2(BR)
loadr  R3,R0
loadi  R0,0
loadr  R2,R0
cmpr  R3,R2
jle  L3
load  R0,5(BR)
store  R0,10011
loadi  R0,10
store  R0,10012
load  R0,10011
divr  R0,R1
store  R0,10014
loadi  R0,10
store  R0,10015
load  R0,10014
mulr  R0,R1
store  R0,6(BR)
load  R0,5(BR)
store  R0,10017
load  R0,6(BR)
store  R0,10018
load  R0,10017
subr  R0,R1
loadr  R3,R0
load  R0,1(BR)
loadr  R2,R0
cmpr  R3,R2
jnz  L4
loadi  R0,1
store  R0,7(BR)
jmp  L5
L4:
load  R0,4(BR)
loadr  R3,R0
load  R0,1(BR)
store  R0,10024
load  R0,-3(BR)
store  R0,10025
load  R0,2(BR)
store  R0,10026
load  R0,10025
subr  R0,R1
store  R0,10027
load  R0,10024
addr  R0,R1
loadr  R2,R0
cmpr  R3,R2
jnz  L6
loadi  R0,1
store  R0,7(BR)
jmp  L7
L6:
load  R0,4(BR)
loadr  R3,R0
load  R0,1(BR)
store  R0,10031
load  R0,-3(BR)
store  R0,10032
load  R0,2(BR)
store  R0,10033
load  R0,10032
subr  R0,R1
store  R0,10034
load  R0,10031
subr  R0,R1
loadr  R2,R0
cmpr  R3,R2
jnz  L8
loadi  R0,1
store  R0,7(BR)
L8:
L7:
L5:
load  R0,5(BR)
store  R0,10037
loadi  R0,10
store  R0,10038
load  R0,10037
divr  R0,R1
store  R0,5(BR)
load  R0,2(BR)
store  R0,10040
loadi  R0,1
store  R0,10041
load  R0,10040
subr  R0,R1
store  R0,2(BR)
jmp  L2
L3:
load  R0,7(BR)
loadr  R3,R0
loadi  R0,0
loadr  R2,R0
cmpr  R3,R2
jnz  L10
load  R0,-4(BR)
store  R0,10045
loadi  R0,10
store  R0,10046
load  R0,10045
mulr  R0,R1
store  R0,10047
load  R0,1(BR)
store  R0,10048
load  R0,10047
addr  R0,R1
store  R0,3(BR)
load  R0,-3(BR)
loadr  R3,R0
load  R0,-2(BR)
loadr  R2,R0
cmpr  R3,R2
jnz  L12
load  R0,3(BR)
writed  R0
loadi  R0,10
writec  R0
load  R0,102
store  R0,10052
loadi  R0,1
store  R0,10053
load  R0,10052
addr  R0,R1
store  R0,102
jmp  L13
L12:
load  R0,3(BR)
push  R0
load  R0,-3(BR)
store  R0,10056
loadi  R0,1
store  R0,10057
load  R0,10056
addr  R0,R1
push  R0
load  R0,-2(BR)
push  R0
call  proc
subi  R4,3
L13:
L10:
load  R0,1(BR)
store  R0,10060
loadi  R0,1
store  R0,10061
load  R0,10060
addr  R0,R1
store  R0,1(BR)
jmp  L0
L1:
loadr  R4,R5
pop  R5
return
main:
loadi  R0,8
store  R0,101
loadi  R0,0
store  R0,102
loadi  R0,0
push  R0
loadi  R0,1
push  R0
load  R0,101
push  R0
call  proc
subi  R4,3
load  R0,102
writed  R0
loadi  R0,10
writec  R0
halt
