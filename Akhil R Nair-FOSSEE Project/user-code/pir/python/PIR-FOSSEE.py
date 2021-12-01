import os 
import sys
cwd = os.getcwd()
(setpath, Examples) = os.path.split(cwd)
sys.path.append(setpath)

from Arduino.Arduino import Arduino
from time import sleep

class PIR:
    def __init__(self,baudrate):
        self.baudrate = baudrate
        self.setup()
        self.run()
        self.exit()

    def setup(self):
        self.obj_arduino = Arduino()
        self.port = self.obj_arduino.locateport()
        self.obj_arduino.open_serial(1, self.port, self.baudrate)

    def run(self):
        self.pir = 6
        #Declaring digital 6 to connect PIR
        pirstate = 0
        for i in range(100):
            val = self.obj_arduino.cmd_digital_in(1, self.pir)
            #function to get digital input
            if val=="1":
               pirstate=1
               print("Motion Detected!")
               sleep(0.5)
            elif val=="0"and pirstate==1:
                print("Motion Ended!")
                sleep(0.5)
            else:
                print("No Motion!")
                sleep(0.5)
                                


    def exit(self):
        self.obj_arduino.close_serial()

def main():
    obj_pir = PIR(115200)

if __name__=='__main__':
    main()
