#coding: UTF-8
import os
import subprocess

def main():
    print("Input:")
    inp = raw_input()
    kekka=os.path.isfile(inp+".asm")
    if kekka == True:
        print("+----------------------------------+\n")
        subprocess.call("cat "+inp+".asm",shell=True)
        print("+----------------------------------+\n")
        print("completed Asembly\n")
        subprocess.call("asm "+inp+".asm "+"> "+inp+".sr",shell=True)
        subprocess.call("sr "+inp+".sr",shell=True)
    else:
        print("file not found\n")
main()
