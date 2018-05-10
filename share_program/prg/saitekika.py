#coding: UTF-8
import os
import subprocess
def fileio(filename):
    assembly=[]
    tmp = []
    i=0
    t = 0
    proglines=0
    with open(filename+'.asm','r') as f:
        for line in f.readlines():
            linetmp=line.strip()
            linetmp = linetmp.replace(',',' ')
            spline = linetmp.split()
            if(spline[0]=="store" and spline[1] == "R0"):
                temp = spline[2]
                print(spline)
                falsestr=line
                i+=1

                print(i)
            if(spline[0]=="load" and i==1 and spline[1] == "R0" and temp == spline[2]):
                #print(proglines)
                print(assembly[len(assembly)-1])
                del assembly[len(assembly)-1]
                i=0
            else:
                assembly.append(line)
                if(i==1 and spline[0] != "store"):
                    i=0
            proglines+=1
    outfile=open(filename+"kai.asm",'w')
    for i in assembly:
        outfile.write(i)
    outfile.close()
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
