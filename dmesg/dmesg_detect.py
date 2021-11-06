import os
    
def detect():
    os.system("dmesg | grep virtual | grep Detected > tmp.txt")
    is_vm = os.stat("tmp.txt").st_size != 0
    os.system("rm tmp.txt")
    return is_vm

def output_string(a):
    if a:
        return "Yes"
    return "No"

print("Virtualization Detected: ", sep='', end='')

is_under_vm = detect()

print(output_string(is_under_vm))
