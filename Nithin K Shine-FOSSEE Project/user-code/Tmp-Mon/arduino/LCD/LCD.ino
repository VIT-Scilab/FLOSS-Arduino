#include <LiquidCrystal.h>//For LCD display
int rs=12,en=11,d4=7,d5=6,d6=5,d7=4;   /* pins used for LCD display      */
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //Declare a LiquidCrystal object
int column_index=0, row_index=0;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2); 
  lcd.setCursor(column_index, row_index);
  lcd.print("Hello World!"); 
}

void loop() {
  // put your main code here, to run repeatedly:

}
