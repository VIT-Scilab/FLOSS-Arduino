import os 
import sys
import time

cwd = os.getcwd()
(setpath,Examples) = os.path.split(cwd)
sys.path.append(setpath)

from Arduino import Arduino
from time import sleep

class HCSR04:
    def __init__(self, baudrate):
        self.baudrate = baudrate
        self.setup()
        self.run()
        self.exit()

    def setup(self):
        self.obj_arduino = Arduino()
        self.port = self.obj_arduino.locateport()
        self.obj_arduino.open_serial(1, self.port, self.baudrate)

    def run(self):
        self.echo = 8
        self.trig = 9
        while True:
            st=self.obj_arduino.cmd_dist(1,self.trig,self.echo)
            print(st)
            sleep(1)
            
    def exit(self):
        self.obj_arduino.close_serial()

def main():
    obj_hcsr04 = HCSR04(115200)

if __name__=='__main__':
    main()
