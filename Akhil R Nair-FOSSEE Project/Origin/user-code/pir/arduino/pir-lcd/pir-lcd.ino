#include<LiquidCrystal.h>
/* LCD Display */
// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int inputPin = 6;               // input pin for pir sensor
int pirState = 0;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 
void setup() {
  pinMode(ledPin, OUTPUT);      
  pinMode(inputPin, INPUT);     
   // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Clears the LCD screen
  lcd.clear();
  Serial.begin(115200);
}
 
void loop(){
  lcd.setCursor(0, 0); //Settinf cursor position to first row first coloumn
  val = digitalRead(inputPin);  // read input value
  
  if (val == HIGH)  // check if the input is HIGH
  {           
      lcd.print(" Motion Detected!  ");
      pirState = 1;
      delay(500);
  } 
  else if(val == LOW && pirstste==1) 
  {
      lcd.print(" Motion ended!  ");
      delay(500);
  }
  else if(val == LOW && pirstste==0) 
  {
      lcd.print(" No Motion!  ");
      delay(500);
  }
}
