import os 
import sys
cwd = os.getcwd()
(setpath, Examples) = os.path.split(cwd)
sys.path.append(setpath)

from Arduino.Arduino import Arduino
from time import sleep

class LCD:
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
        #declaring pins
        self.pir = 6
        pirstate = 0
        motend = 0
        motdet = 1
        nomot = 2
        for i in range(1000):
            val = self.obj_arduino.cmd_digital_in(1, self.pir)
            if val=="1":
               pirstate=1
               self.obj_arduino.cmd_lcd_out(1,motdet)
               #function to display "Motion detected!" on LCD
               sleep(0.5)
            elif val=="0" and pirstate==1:
                self.obj_arduino.cmd_lcd_out(1,motend)
                #function to display "Motion Ended!" on LCD
                sleep(0.5)
            else:
                self.obj_arduino.cmd_lcd_out(1,nomot)
                #function to display "No Motion!" on LCD
                sleep(0.5)
                                


    def exit(self):
        self.obj_arduino.close_serial()

def main():
    obj_lcd = LCD(115200)

if __name__=='__main__':
    main()
