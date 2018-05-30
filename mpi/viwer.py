#coding: UTF-8
import struct
file_name = input("ファイル名>>>")
buf1=()
buf2=()
with open(file_name+'.dat','rb') as f:
    nap_size = f.read(4)
    table_size = struct.unpack("i",f.read(4))
    print(table_size[0])
    for i in range(0,int(table_size[0])):
        if i % 2 == 0:
            buf1=struct.unpack("i",f.read(4))
        if i % 2 == 1:
            buf2=struct.unpack("i",f.read(4))
        print("weight->"+str(buf1[0])+"    value->"+str(buf2[0]))
