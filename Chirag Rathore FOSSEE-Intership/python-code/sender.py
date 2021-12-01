import os
import sys
cwd = os.getcwd()
(setpath,examples) = os.path.split(cwd)
sys.path.append(setpath)

from Arduino.Arduino import Arduino
from time import sleep

class transmitter:
    def __init__(self,baudrate):
        self.baudrate = baudrate
        self.setup()
        self.run()
        self.exit()
    
    def setup(self):
        self.obj_arduino = Arduino()
        self.port = self.obj_arduino.locateport1()
        print(self.port)
        self.obj_arduino.open_serial(1,self.port,self.baudrate)

    def run(self):
        self.potpin = 0  #initializing potentiometer pin
        val = 0          #decalring potentiometer value = 0
        while True:
            val = self.obj_arduino.cmd_analog_in(1,self.potpin)  #reading potentiometer value
            val = self.obj_arduino._map(val,0,1023,0,255)   #mapping potentiometer value 
            self.obj_arduino.send_msg(1,val) # sending potentiometer value
            print(val)
            sleep(0.5)

    def new_method(self, val):
        self.obj_arduino.send_msg(1,val)

    def exit(self):
        self.obj_arduino.close_serial()

def main():
    obj_send = transmitter(115200)

if __name__ == '__main__':
    main()