from dmidecode import DMIDecode
dmi= DMIDecode()
print('Manufacturer:\t', dmi.manufacturer())
