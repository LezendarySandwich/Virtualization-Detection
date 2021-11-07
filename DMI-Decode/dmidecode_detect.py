from dmidecode import DMIDecode
dmi= DMIDecode()

def detect_vmware():
    manufacturer= dmi.manufacturer().lower()
    model = dmi.model().lower()
    serial_number = dmi.serial_number().lower()
    vmware = 'vmware'
    return  ( manufacturer.find(vmware)+1) or ( serial_number.find(vmware)+1) or ( model.find(vmware)+1 )

def detect_virtual_box():
    manufacturer =  dmi.manufacturer().lower()
    model = dmi.model().lower()
    serial_number =  dmi.serial_number().lower()
    virtual_box= 'virtualbox'
    return (manufacturer.find(virtual_box)+1) or (serial_number.find(virtual_box)+1) or (model.find(virtual_box)+1)

def detect_aws_xen():
    manufacturer= dmi.manufacturer().lower() 
    model = dmi.model().lower() 
    serial_number = dmi.serial_number().lower()
    xen = "xen"
    return (manufacturer.find(xen)+1) or (serial_number.find(xen)+1) or (model.find(xen)+1)

def detect_google_cloud():
    manufacturer= dmi.manufacturer().lower() 
    model = dmi.model().lower() 
    serial_number = dmi.serial_number().lower()
    gc='googlecloud'
    return (manufacturer.find(gc)+1) or (serial_number.find(gc)+1) or (model.find(gc)+1)

def detect():
    return  detect_vmware() or detect_virtual_box() or detect_aws_xen() or detect_google_cloud()

def output_string(a):
    if a:
        return "Yes"
    return "No"

print("Virtualization Detected: ", sep='', end='')

is_under_vm = detect()

print(output_string(is_under_vm))
