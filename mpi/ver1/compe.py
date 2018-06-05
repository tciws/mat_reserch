#coding: UTF-8
import subprocess
from time import sleep
for i in range(0,1000):
    print("只今"+str(i)+"回目")
    subprocess.call("mpiexec -n 16 -f mpd.hosts /home/27115/ckl15040/mat_reserch/mpi/ver1/a.out >> seko", shell=True)
    print(str(i)+"回目終了")
    sleep(10)
