loadi  R0,0
store  R0,1
loadi  R0,0
store  R0,10001
load  R0,10001
store  R0,6
loadi  R0,3827
store  R0,10002
load  R0,10002
store  R0,2
loadi  R0,8358
store  R0,10003
load  R0,10003
store  R0,3
loadi  R0,3797
store  R0,10004
load  R0,10004
store  R0,4
L1:
load  R0,1
store  R0,10005
load  R0,10005
loadr  R3,R0
loadi  R0,1000
loadr  R2,R0
cmpr  R3,R2
jge  L2
load  R0,2
store  R0,10007
load  R0,3
store  R0,10008
load  R0,10007
load  R1,10008
addr  R0,R1
store  R0,10009
load  R0,4
store  R0,10010
load  R0,10009
load  R1,10010
mulr  R0,R1
store  R0,10011
load  R0,2
store  R0,10012
load  R0,3
store  R0,10013
load  R0,10012
load  R1,10013
addr  R0,R1
store  R0,10014
load  R0,4
store  R0,10015
load  R0,10014
load  R1,10015
mulr  R0,R1
store  R0,10016
load  R0,E1
store  R0,10017
load  R0,10016
load  R1,10017
divr  R0,R1
store  R0,10018
load  R0,E2
store  R0,10019
load  R0,10018
load  R1,10019
mulr  R0,R1
store  R0,10020
load  R0,10011
load  R1,10020
subr  R0,R1
store  R0,10022
loadi  R0,10
store  R0,10023
load  R0,10022
load  R1,10023
divr  R0,R1
store  R0,10025
loadi  R0,10
store  R0,10026
load  R0,10025
load  R1,10026
divr  R0,R1
store  R0,7
load  R0,2
store  R0,10028
load  R0,3
store  R0,10029
load  R0,10028
load  R1,10029
addr  R0,R1
store  R0,10030
load  R0,4
store  R0,10031
load  R0,10030
load  R1,10031
mulr  R0,R1
store  R0,10032
load  R0,2
store  R0,10033
load  R0,3
store  R0,10034
load  R0,10033
load  R1,10034
addr  R0,R1
store  R0,10035
load  R0,4
store  R0,10036
load  R0,10035
load  R1,10036
mulr  R0,R1
store  R0,10037
load  R0,E3
store  R0,10038
load  R0,10037
load  R1,10038
divr  R0,R1
store  R0,10039
load  R0,E4
store  R0,10040
load  R0,10039
load  R1,10040
mulr  R0,R1
store  R0,10041
load  R0,10032
load  R1,10041
subr  R0,R1
store  R0,10042
load  R0,10042
store  R0,10043
loadi  R0,10
store  R0,10044
load  R0,10043
load  R1,10044
divr  R0,R1
store  R0,10046
loadi  R0,10
store  R0,10047
load  R0,10046
load  R1,10047
divr  R0,R1
store  R0,8
load  R0,7
store  R0,10049
load  R0,7
store  R0,10050
load  R0,10049
load  R1,10050
mulr  R0,R1
store  R0,10051
load  R0,8
store  R0,10052
load  R0,8
store  R0,10053
load  R0,10052
load  R1,10053
mulr  R0,R1
store  R0,10054
load  R0,10051
load  R1,10054
addr  R0,R1
store  R0,10055
load  R0,10055
loadr  R3,R0
load  R0,E5
loadr  R2,R0
cmpr  R3,R2
jge  L3
load  R0,6
store  R0,10057
loadi  R0,1
store  R0,10058
load  R0,10057
load  R1,10058
addr  R0,R1
store  R0,6
jmp  L4
L3:
L4:
load  R0,1
store  R0,10060
loadi  R0,1
store  R0,10061
load  R0,10060
load  R1,10061
addr  R0,R1
store  R0,10062
load  R0,10062
store  R0,1
jmp  L1
L2:
load  R0,6
store  R0,10063
loadi  R0,4
store  R0,10064
load  R0,10063
load  R1,10064
mulr  R0,R1
store  R0,10065
load  R0,10065
writed  R0
loadi  R0,10
writec  R0
halt
E1:data 100000
E2:data 100000
E3:data 100000
E4:data 100000
E5:data 1000000
