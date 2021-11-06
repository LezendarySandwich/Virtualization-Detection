import os

def detect():
    os.system("lsmod | grep vmwgfx >tmp.txt")
    is_vm = os.stat("tmp.txt").st_size != 0
    os.system("rm tmp.txt")
    return is_vm
