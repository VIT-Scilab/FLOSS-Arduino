
import sys
import serial
from serial import Serial
from serial.tools.list_ports import comports
from time import sleep

p1=0               #Initial Position of servo motor 
p2=0               #Final Position of servo motor

a=["0","1","2","3","4","5","6","7","8","9",":",";","<","=",">","A","B","C","D"]
class Initialization:
    def __init__(self):
        pass
        
    def locateport(self):
        if sys.platform.startswith('win'):
            port =''
            ports = list(comports())
            for i in ports:
                for j in i:
                    if 'Serial' in j:
                        port = i[0]
        elif sys.platform.startswith('linux'):
            b=[]
            port =''
            ports = list(comports())
            for i in range(len(ports)):
                for x in range(7):
                    portname="/dev/ttyACM"+str(x)
                    if ports[i][0]==portname:
                        b.append(ports[i][0])
            port=b[0]
        return port
    
    def open_serial(self,ard_no, PortNo,baudrate):
        #global ser
        if PortNo =='':
            sys.exit("aa..error..! arduino not found")
        else:
            self.ser = Serial(PortNo,baudrate)
        sleep(2)
        # self.checkfirmware()
        
    def close_serial(self):
        #global ser     
        self.ser.close()
    
    def checkfirmware(self):
        print ("Check Firm Ware")
        #global ser
        i = 0
        while i < 3:
            self.ser.write(bytes([118])) #chr(118)
            try: 
                x=self.ser.read(2)
                print(x.decode('UTF-8'))
                #x=self.ser.read()
                #print(x)
                # if x==b'o':
                #     try:
                #         # x=self.ser.read()
                #         # print(x.decode('UTF-8'))
                #     except:
                #         sys.exit("aa..! error..! it seems correct firmware not loaded")
                # else:
                #     sys.exit("aa..! error..! it seems correct firmware not loaded")
            except:
                sys.exit("aa..! error..! it seems correct firmware not loaded")
            i = i + 1
    
        
class Arduino(Initialization):
    def __init__(self):
        print ("Init Arduino")
        #self.baudrate=0
        #self.ard_no=1
        #self.PortNo=0
        #self.pin=0
        #self.val=0
        #self.mode=0
        #self.mno=0
        #self.pin1=0
        #self.pin2=0
        #self.servo=0
    
    
    
    def cmd_digital_out(self,ard_no,pin,val):
        cmd=""
        a=["0","1","2","3","4","5","6","7","8","9",":",";","<","=",">","A","B","C","D"]   
        cmd="D"+"a"+a[pin]+"1"    
        self.ser.write(cmd.encode('utf-8'))
        cmd=""
        cmd="D"+"w"+a[pin]+str(val)
        self.ser.write(cmd.encode('utf-8'))
        
    def cmd_digital_in(self,ard_no,pin):
        b=[]
        cmd=""
        a=["0","1","2","3","4","5","6","7","8","9",":",";","<","=",">","A","B","C","D"]   
        cmd="D"+"a"+a[pin]+"0"    
        self.ser.write(cmd.encode('utf-8'))
        cmd=""
        cmd="D"+"r"+a[pin]
        self.ser.write(cmd.encode('utf-8'))
        a=self.ser.read()
        return(a.decode('UTF-8'))
    
    def cmd_analog_in(self,ard_no,pin):
        cmd=""
        a=["0","1","2","3","4","5","6","7","8","9",":",";","<","=",">","A","B","C","D"]    
        cmd="A"+a[pin]    
        self.ser.write(cmd.encode('utf-8'))
        analog_times=[]
        b1=ord(self.ser.read(1))
        b2=ord(self.ser.read(1))
        a=b1+b2*256
        #a=ser.read()
        return(a)
        #return(int((1023-0)*int(ord(a))/(255-0)))
        

    def cmd_lcd_out(self,ard_no,val):
        a=["0","1","2","3","4","5","6","7","8","9",":",";","<","=",">","A","B","C","D"]
        cmd = "L" + "c" + a[val]
        self.ser.write(cmd.encode('utf-8'))
        
    def cmd_analog_out(self,ard_no, pin, val):
        a=["0","1","2","3","4","5","6","7","8","9",":",";","<","=",">","A","B","C","D"]
        cmd = "W" + a[pin] + chr(val)
        self.ser.write(cmd.encode('utf-8'))
        
    
        









