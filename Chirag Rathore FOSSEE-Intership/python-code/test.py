import sys
import serial
from serial import Serial

import serial.tools.list_ports as port_list

ports = list(port_list.comports())
port = []
for p in ports:
    port.append(p)

print(ports[0][0])
print(port[1][0])
