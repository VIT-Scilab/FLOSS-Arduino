int inputPin = 6;               // input pin for pir sensor
int pirState = 0;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 
void setup() {
  pinMode(ledPin, OUTPUT);      
  pinMode(inputPin, INPUT);     
 
  Serial.begin(115200);
}
 
void loop(){
  val = digitalRead(inputPin);  // read input value
  
  if (val == HIGH)  // check if the input is HIGH
  {           
      Serial.println("Motion detected!"); // print on output change
      pirState = 1;
      delay(500);
  } 
  else if(val == LOW && pirstste==1) 
  {
      Serial.println("Motion ended!");  // print on output change
      delay(500);
  }
  else if(val == LOW && pirstste==0) 
  {
      Serial.println("No Motion!");  // print on output change
      delay(500);
  }
}
