/* This file is meant to be used with the FLOSS-Arduino  
   toolbox, however, it can be used from the IDE environment
   (or any other serial terminal) by typing commands like:
   
   Conversion ascii -> number
   48->'0' ... 57->'9' 58->':' 59->';' 60->'<' 61->'=' 62->'>' 63->'?' 64->'@' 
   65->'A' ... 90->'Z' 91->'[' 92->'\' 93->']' 94->'^' 95->'_' 96->'`' 
   97->'a' ... 122->'z'
   
   */


/* define internal for the MEGA as 1.1V (as as for the 328)  */
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define INTERNAL INTERNAL1V1
#endif



void setup() {
  /* initialize serial                                       */
  Serial.begin(115200);
  
}

void loop() {
  
  
   
  /* variables declaration and initialization                */
  
  static int  s   = -1;    /* state                          */
  static int  pin = 13;    /* generic pin number             */

  int  val =  0;           /* generic value read from serial */
  int  agv =  0;           /* generic analog value           */
  int  dgv =  0;           /* generic digital value          */
  
  while (Serial.available()==0) {}; // Waiting char
  val = Serial.read(); 
  
  //Checking for availability of firmware
  if(val==118)
  {
    delay(10);
    Serial.write("ok"); 
  }
  
//  if (val==0){// version
//    Serial.print('v3');
//    val=-1;
//  }
  //case A -> Analog
  else if (val==65){//A -> Analog read
    while (Serial.available()==0) {}; // Waiting char
//    val=Serial.read();
//    if (val==114){ //'r'-> read pin
//       while (Serial.available()==0) {}; // Waiting char
       val=Serial.read();
       if (val>47 && val<67) { //from pin 0, to pin 19
          pin=val-48; //number of the pin
          agv=analogRead(pin);
          //Serial.println(agv);
          Serial.write((uint8_t*)&agv,2); /* send binary value via serial  */   
       }
       val=-1;
  }
  else if (val==87){//W -> Analog write
      while (Serial.available()==0) {}; // Waiting char
      val=Serial.read();
         if (val>47 && val<67) { //from pin 0 to pin 19
            pin=val-48; //number of the pin
            while (Serial.available()==0) {}; // Waiting char
            val=Serial.read();
            analogWrite(pin,val);
         }
          val=-1;
      }
  else if (val==80){//P -> HCSR04
    int trig,echo;
    while (Serial.available()==0) {}; // Waiting char
    trig=Serial.read()-48;
    while (Serial.available()==0) {}; // Waiting char
    echo=Serial.read()-48;
    pinMode(trig,OUTPUT);
    pinMode(echo,INPUT);
    delay(1000);
    unsigned long duration;
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    
    duration=pulseIn(echo,HIGH);
    int distance=duration*0.034/2;
    Serial.print("Distance : ");
    Serial.print(distance);
    Serial.println(" cm ");
    delay(1000);
          val=-1;
      }

  //case D -> Digital
  else if (val==68){//D -> Digital pins
    while (Serial.available()==0) {}; // Waiting char
    val=Serial.read();
    if (val==97){ //'a'-> declare pin
       while (Serial.available()==0) {}; // Waiting char
       val=Serial.read();
       if (val>49 && val<102) {
         pin=val-48;
         while (Serial.available()==0) {}; // Waiting char
         val=Serial.read();
         if (val==48 || val==49) { 
            if (val==48){//'0' -> input
               pinMode(pin,INPUT);
            }
            else if (val==49){//'1' -> output
               pinMode(pin,OUTPUT);
            }
         }
       }
    }
    if (val==114){ //'r'-> read pin
       while (Serial.available()==0) {}; // Waiting char
       val=Serial.read();
       if (val>49 && val<102) { 
          pin=val-48; //number of the digital pin
          dgv=digitalRead(pin);      
//          Serial.println(dgv);        
          Serial.print(dgv);         
       }
    }
    if (val==119){ //'w'-> write pin
       while (Serial.available()==0) {}; // Waiting char
       val=Serial.read();
       if (val>49 && val<102) { 
          pin=val-48; //number of the digital pin
          while (Serial.available()==0) {}; // Waiting char
          val=Serial.read();
          if (val==48 || val==49) { // 0 or 1
            dgv=val-48;
            digitalWrite(pin,dgv);
//            Serial.println(dgv);    
          }
       }
    }
   val=-1;

  }
  }
 
