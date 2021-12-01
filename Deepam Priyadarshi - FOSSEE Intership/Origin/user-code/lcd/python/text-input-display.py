import os
import sys
cwd = os.getcwd()
(setpath, Examples) = os.path.split(cwd)
sys.path.append(setpath)

from Arduino.Arduino import Arduino
from time import sleep

class LCD_DISPLAY:
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
        self.lcd_col, self.lcd_row = [int(x) for x in input("Enter the no. of columns and rows of LCD: ").split()]
        self.obj_arduino.cmd_lcd_size(self.lcd_col, self.lcd_row)
        self.text = ""
        while(True):
            self.text = input("Enter the text message: ")
            self.obj_arduino.cmd_lcd_text_display(self.text)
            sleep(1)
            c = input("Do you want to continue?(y/n)")
            if(c != "y"):
                break
    
    def exit(self):
        self.obj_arduino.close_serial()

def main():
    obj_lcd = LCD_DISPLAY(115200);

if __name__=='__main__':
    main()
            
