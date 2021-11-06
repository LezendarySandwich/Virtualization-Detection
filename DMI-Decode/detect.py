from dmidecode import DMIDecode
dmi= DMIDecode()

def detect_vmware():
    manufacturer= dmi.manufacturer().lower()
    model = dmi.model().lower()
    serial_number = dmi.serial_number().lower()
    vmware = 'vmware'
    return  ( manufacturer.find(vmware)+1) or ( serial_number.find(vmware)+1) or ( model.find(vmware)+1 )

def detect_virtual_box():
    return False

def detect_aws_xen():
    manufacturer= dmi.manufacturer().lower() 
    model = dmi.model().lower() 
    serial_number = dmi.serial_number().lower()
    xen = "xen"
    return (manufacturer.find(xen)+1) or (serial_number.find(xen)+1) or (model.find(xen)+1)

def detect():
    return  detect_vmware() or detect_virtual_box() or detect_aws_xen()

if detect():
    print("me vm uwu")
else:
    print("me no vm :/")
