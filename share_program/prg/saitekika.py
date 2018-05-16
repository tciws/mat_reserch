#coding: UTF-8
import os
import subprocess
def fileio(filename):
    assembly=[]
    tmpassembly=[]
    completeassembly=[]
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
                temp =spline[2]
                tmp.append(spline[2])
                #print(spline)
                falsestr=line
                i+=1

                #print(i)
            if(spline[0]=="load" and i==1 and spline[1] == "R0" and temp == spline[2]):
                #print(proglines)
                #print(assembly[len(assembly)-1])
                del assembly[len(assembly)-1]
                i=0
            else:
                if(spline[0]=="load" and spline[1] == "R1"):
                    #print(assembly[len(assembly)-2])
                    #print(assembly[len(assembly)-3])
                    #assembly.insert(len(assembly)-3,"loadr  R1,R0\n")
                    #tmpassembly.insert(len(tmpassembly)-3,"['loadr','R1','R0']")
                    print(tmpassembly[len(tmpassembly)-5])
                    print(assembly[len(assembly)-5])
                    #del assembly[len(assembly)-5]
                    #del tmpassembly[len(tmpassembly)-5]
                    #del assembly[len(assembly)-5]
                else:
                    tmpassembly.append(spline)
                assembly.append(line)
                #if(i == 2):
                if(i==2):
                    i=0
            proglines+=1
        i=0
        proglines=0
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
