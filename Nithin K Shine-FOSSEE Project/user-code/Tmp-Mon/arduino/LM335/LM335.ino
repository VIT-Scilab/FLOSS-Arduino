void setup()
{
Serial.begin(9600);
}
//main loop
void loop()
{
val = analogRead(A5);//value of LM335
val = val*(500/1023)-273;
Serial.println(val);//for display
delay(500);
}
