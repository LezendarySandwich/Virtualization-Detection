import os
    
def detect():
    os.system("dmesg | grep virtual >tmp.txt")
    is_vm = os.stat("tmp.txt").st_size != 0
    os.system("rm tmp.txt")
    return is_vm
    
