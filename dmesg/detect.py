import os

def detect_vmware():
    os.system("dmesg | grep virtual | grep Detected >tmp.txt")
    is_vm = os.stat("tmp.txt").st_size != 0
    os.system("rm tmp.txt")
    return is_vm
    
    
def detect():
    if detect_vmware():return 1
    return 0
    
