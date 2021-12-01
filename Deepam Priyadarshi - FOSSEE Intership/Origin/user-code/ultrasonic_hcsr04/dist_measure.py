import os
import sys
cwd = os.getcwd()
(setpath, Examples) = os.path.split(cwd)
sys.path.append(setpath)

from Arduino.Arduino import Arduino
from time import sleep

class LED_ON:
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
        self.echoPin = 2
        self.trigPin = 3
        self.obj_arduino.cmd_lcd_size(16,2)
        while True:
            self.obj_arduino.cmd_digital_out(1, self.trigPin, 0)
            sleep(0.000001)
            self.obj_arduino.cmd_digital_out(1, self.trigPin, 1)
            sleep(0.000002)
            self.obj_arduino.cmd_digital_out(1, self.trigPin, 0)
            dist = round(float(self.obj_arduino.cmd_pulse_in(1,self.echoPin, 1)) * 0.034 / 2)
            sleep(0.7)
            self.obj_arduino.cmd_lcd_text_display("Dist: "+str(dist)+"cm")

    def exit(self):
        self.obj_arduino.close_serial()

def main():
    obj_led = LED_ON(115200)

if __name__== '__main__':
    main()
