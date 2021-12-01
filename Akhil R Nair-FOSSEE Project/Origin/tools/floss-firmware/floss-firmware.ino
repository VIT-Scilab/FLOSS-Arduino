/* This file is meant to be used with the FLOSS-Arduino  
   toolbox, however, it can be used from the IDE environment
   (or any other serial terminal) by typing commands like:
   
   Conversion ascii -> number
   48->'0' ... 57->'9' 58->':' 59->';' 60->'<' 61->'=' 62->'>' 63->'?' 64->'@' 
   65->'A' ... 90->'Z' 91->'[' 92->'\' 93->']' 94->'^' 95->'_' 96->'`' 
   97->'a' ... 122->'z'
   
   Dan0 or Dan1 : attach digital pin n (ascii from 2 to b) to input (0) or output (1)
   Drn : read digital value (0 or 1) on pin n (ascii from 2 to b)
   Dwn0 or Dwn1 : write 1 or 0 on pin n
   An    : reads analog pin n (ascii from 0 to 19)
   Wnm  : write analog value m (ascii from 0 to 255) on pin n (ascii from 0 to 19)

   LCD Display
   Lc0 or Lc1 or Lc2 : Prints value Motion ended!, Motion detected! & No motion! respectively
   
   */

#include<LiquidCrystal.h>

/* define internal for the MEGA as 1.1V (as as for the 328)  */
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define INTERNAL INTERNAL1V1
#endif


/* LCD Display */
// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


int initiat=1;

void setup() {
  /* initialize serial                                       */
  Serial.begin(115200);

  /* initialize lcd */
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Clears the LCD screen
  lcd.clear();
  
}
void loop() {
  
  
   
  /* variables declaration and initialization                */
  
  static int  s   = -1;    /* state                          */
  static int  pin = 13;    /* generic pin number             */
  static int  dcm =  4;    /* generic dc motor number        */

  int  val =  0;           /* generic value read from serial */
  int  agv =  0;           /* generic analog value           */
  int  dgv =  0;           /* generic digital value          */
  static int  enc   = 1;    /* encoder number 1 (or 2 for Arduino mega)     */

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
  //}

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
  //Case L -> LCD
  else if (val==76){//L -> Detect LCD Function
    while (Serial.available()==0) {}; // Waiting char
    val=Serial.read();
    if (val==99){ //'c'-> declare LCD pins
       lcd.setCursor(0, 0); //Settinf cursor position to first row first coloumn
       while (Serial.available()==0) {}; // Waiting char
       val=Serial.read();
       if (val==48 || val==49 || val==50) { //Checking if character is 0,1,2
          if (val==48){//'0' -> Motion ended
             lcd.print(" Motion ended!  ");
          }
          else if (val==49){//'1' -> Motion detected
             lcd.print("Motion detected! ");
          }
          else if (val==50){//'2' -> No motion
             lcd.print("   No Motion!   ");
          }
         }
       }
    }
  

  //case R -> Analog reference
  if(val==82){
    while (Serial.available()==0) {};                
    val = Serial.read();
    if (val==48) analogReference(DEFAULT);
    if (val==49) analogReference(INTERNAL);
    if (val==50) analogReference(EXTERNAL);
    if (val==51) Serial.print("v3");
    val=-1;
  }
  
} /* end loop statement                                      */
