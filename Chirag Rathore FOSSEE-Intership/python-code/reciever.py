import os
import sys

import serial
cwd = os.getcwd()
(setpath,examples) = os.path.split(cwd)
sys.path.append(setpath)

from Arduino.Arduino import Arduino
from time import sleep

class Receiver:
    def __init__(self,baudrate):
        self.baudrate = baudrate
        self.setup()
        self.run()
        self.exit()

    def setup(self):
        self.obj_arduino = Arduino()
        self.port = self.obj_arduino.locateport2()
        print(self.port)
        self.obj_arduino.open_serial(2,self.port,self.baudrate)

    def run(self):
        while True:
            val = self.obj_arduino.receive_msg(2)  # receiving potentiometer value  
            self.obj_arduino.lcd_print(2,val)
            print(val)
            sleep(0.5)

    def exit(self):
        self.obj_arduino.close_serial()

def main():
    obj_rec = Receiver(115200)

if __name__ == '__main__':
    main()
