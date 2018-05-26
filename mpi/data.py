#coding: UTF-8
weight = [4,3,2,2]
value = [7,5,3,2]
head = [5,4]
with open('data4k.dat','wb') as f:
    f.write(head[0].to_bytes(4, byteorder='little'))
    f.write(head[1].to_bytes(4, byteorder='little'))
    for i in range(0,4):
        f.write(weight[i].to_bytes(4, byteorder='little'))
        f.write(value[i].to_bytes(4, byteorder='little'))
with open('data4k.dat','rb') as f:
    while True:
        d = f.read(1)
        if len(d) == 0:
            break
        print('%s ' % (ord(d)), end='')
