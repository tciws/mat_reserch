loadi  R0,0
store  R0,10000
load  R0,10000
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
store  R0,10006
load  R0,10006
loadr  R2,R0
cmpr  R0,R0
jge  L2
load  R0,2
store  R0,10007
load  R0,3
store  R0,10008
load  R0,10008
load  R1,10007
addr  R0,R1
store  R0,10009
load  R0,4
store  R0,10010
load  R0,10010
load  R1,10009
mulr  R0,R1
store  R0,10011
load  R0,2
store  R0,10012
load  R0,3
store  R0,10013
load  R0,10013
load  R1,10012
addr  R0,R1
store  R0,10014
load  R0,4
store  R0,10015
load  R0,10015
load  R1,10014
mulr  R0,R1
store  R0,10016
load  R0,E1
store  R0,10017
load  R0,10017
load  R1,10016
divr  R0,R1
store  R0,10018
load  R0,E2
store  R0,10019
load  R0,10019
load  R1,10018
mulr  R0,R1
store  R0,10020
load  R0,10020
load  R1,10011
subr  R0,R1
store  R0,10021
load  R0,10021
store  R0,2
load  R0,2
store  R0,10022
loadi  R0,10
store  R0,10023
load  R0,10023
load  R1,10022
divr  R0,R1
store  R0,10024
load  R0,10024
store  R0,2
load  R0,2
store  R0,10025
loadi  R0,10
store  R0,10026
load  R0,10026
load  R1,10025
divr  R0,R1
store  R0,10027
load  R0,10027
store  R0,7
load  R0,2
store  R0,10028
load  R0,3
store  R0,10029
load  R0,10029
load  R1,10028
addr  R0,R1
store  R0,10030
load  R0,4
store  R0,10031
load  R0,10031
load  R1,10030
mulr  R0,R1
store  R0,10032
load  R0,2
store  R0,10033
load  R0,3
store  R0,10034
load  R0,10034
load  R1,10033
addr  R0,R1
store  R0,10035
load  R0,4
store  R0,10036
load  R0,10036
load  R1,10035
mulr  R0,R1
store  R0,10037
load  R0,E3
store  R0,10038
load  R0,10038
load  R1,10037
divr  R0,R1
store  R0,10039
load  R0,E4
store  R0,10040
load  R0,10040
load  R1,10039
mulr  R0,R1
store  R0,10041
load  R0,10041
load  R1,10032
subr  R0,R1
store  R0,10042
load  R0,10042
store  R0,2
load  R0,2
store  R0,10043
loadi  R0,10
store  R0,10044
load  R0,10044
load  R1,10043
divr  R0,R1
store  R0,10045
load  R0,10045
store  R0,2
load  R0,2
store  R0,10046
loadi  R0,10
store  R0,10047
load  R0,10047
load  R1,10046
divr  R0,R1
store  R0,10048
load  R0,10048
store  R0,8
load  R0,7
store  R0,10049
load  R0,7
store  R0,10050
load  R0,10050
load  R1,10049
mulr  R0,R1
store  R0,10051
load  R0,8
store  R0,10052
load  R0,8
store  R0,10053
load  R0,10053
load  R1,10052
mulr  R0,R1
store  R0,10054
load  R0,10054
load  R1,10051
addr  R0,R1
store  R0,10055
load  R0,10055
loadr  R3,R0
load  R0,E5
store  R0,10056
load  R0,10056
loadr  R2,R0
cmpr  R0,R0
jge  L3
load  R0,6
store  R0,10057
loadi  R0,1
store  R0,10058
load  R0,10058
load  R1,10057
addr  R0,R1
store  R0,10059
load  R0,10059
store  R0,6
jmp  L4
L3:
L4:
load  R0,1
store  R0,10060
loadi  R0,1
store  R0,10061
load  R0,10061
load  R1,10060
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
load  R0,10064
load  R1,10063
mulr  R0,R1
store  R0,10065
load  R0,10065
store  R0,5
load  R0,5
writed  R0
loadi  R0,10
writec  R0
halt
E0:data 0
E1:data 100000
E2:data 100000
E3:data 100000
E4:data 100000
