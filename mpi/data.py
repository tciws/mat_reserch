#coding: UTF-8
from numpy.random import *
def main():
    ans_data = []
    weight1 = []
    weight2 = []
    value1 = []
    value2 = []
    data_set = []
    data_set2 = []
    file_name = input("ファイル名>>>")     #ファイル名入力
    nap_size = int(input("ナップサックサイズ>>>"))      #ナップサックのサイズ入力
    object_number = int(input("荷物の個数>>>")) #オブジェクトの個数入力
    object_weight_min = int(input("荷物の重さの最小値>>>"))
    object_weight_max = int(input("荷物の重さの最大値>>>"))
    #object_value_min = int(input("荷物の価値の最小値>>>"))
    #object_value_max = int(input("荷物の価値の最大値>>>"))
    while 1:
        k = randint(object_weight_min,object_weight_max)
        tmp = poisson(lam=k)
        if object_weight_min <= tmp and tmp <= object_weight_max:
            print('価値'+str(2*tmp/object_weight_max))
            break
    costp = 2*tmp/object_weight_max
    for i in range(0,int(nap_size/10)):
        tmp = 10
        ans_data.append(int(tmp))
        value = tmp * costp * 100
        ans_data.append(int(value))
    for i in range(0,int(object_number/2)):
        while 1:
            k = randint(object_weight_min,object_weight_max)
            tmp = poisson(lam=k/3)
            if object_weight_min <= tmp and tmp <= object_weight_max:
                #print(tmp)
                weight1.append(int(tmp))
                break
        #value_tmp = tmp * costp
        #print(int(value_tmp))
        #value1.append(int(value_tmp))
        while 1:
            k = randint(object_weight_min,object_weight_max)
            tmp = poisson(lam=3*k/5)
            if object_weight_min <= tmp and tmp <= object_weight_max:
                #print(tmp)
                weight2.append(int(tmp))
                break
        #value_tmp = costp * tmp
        #print(int(value_tmp))
        #value2.append(int(value_tmp))
    weight1.sort(reverse = True)
    weight2.sort()
    for i in range(0,int(object_number/2)):
        tmp=weight1[i]
        data_set.append(int(tmp))
        value_tmp = tmp * costp
        #print(int(value_tmp))
        data_set.append(int(value_tmp))
        tmp=weight2[i]
        data_set2.append(int(tmp))
        value_tmp = tmp * costp
        #print(int(value_tmp))
        data_set2.append(int(value_tmp))
    data_set.extend(data_set2)
    data_set.extend(ans_data)
    print(data_set)
    object_number = object_number + int(nap_size/10)
    with open(file_name+'.dat','wb') as f:
        f.write(nap_size.to_bytes(4, byteorder='little'))
        f.write(object_number.to_bytes(4, byteorder='little'))
        for i in data_set:
            print(i)
            f.write(i.to_bytes(4, byteorder='little'))
    print("correct..")
main()
