#coding: UTF-8
import os
import subprocess
def fileio(filename):
    assembly=[]
    tmp = []
    i=0
    with open(filename+'.asm','r') as f:
        for line in f.readlines():
            line=line.strip()
            line = line.replace(',',' ')
            spline = line.split()
            assembly.append(spline)
            if(spline[0]=="store" and spline[1] == "R0"):
                i+=1
                temp = spline[2]
                print(spline)
                #print(spline)
            if(spline[0]=="load" and i==1 and temp == spline[2]):
                print(spline)
                i=0
        #print(assembly)
def main():
    print("Input:")
    inp = raw_input()
    kekka=os.path.isfile(inp+".asm")
    if kekka == True:
        print("show before Asembly\n")
        print("+----------------------------------+\n")
        subprocess.call("cat "+inp+".asm",shell=True)
        print("+----------------------------------+\n")
        fileio(inp)
main()
