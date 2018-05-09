addi  R4,2
jmp main
proc:
push  R5
loadr  R5,R4
addi  R4,1
load  R0,-3(BR)
store  R0,10000
load  R0,-2(BR)
store  R0,10001
load  R0,10000
load  R1,10001
addr  R0,R1
store  R0,10002
load  R0,10002
store  R0,-3(BR)
load  R0,-3(BR)
writed  R0
loadi  R0,10
writec  R0
loadr  R4,R5
pop  R5
return
main:
loadi  R0,1
store  R0,10003
load  R0,10003
store  R0,101
loadi  R0,3
store  R0,10004
load  R0,10004
store  R0,102
halt
