#include <Keypad.h> // Подключаем библиотеку 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,2,2);  // Устанавливаем дисплей
const byte ROWS = 4; // 4 строки
const byte COLS = 4; // 4 столбца
char keys[ROWS][COLS] = {
  {'H','W','L','O'},
  {'E','R','R','L'},
  {'L','D','9','C'},
  {'O',' ','#','D'}
}; 
byte rowPins[ROWS] = {11,10, 9, 8}; 
byte colPins[COLS] = {7, 6, 5, 4}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  lcd.init();    
  lcd.backlight();
  lcd.blink();
  lcd.setCursor(0, 0);
}
void loop(){
  char key = keypad.getKey();
  if (key){
    lcd.print(key);
    Serial.println(key); // Передаем название нажатой клавиши в сериал порт
  }
}
