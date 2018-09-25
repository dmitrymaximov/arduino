#include "IRremote.h"
IRrecv irrecv(2);
decode_results results;

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop()
{
  if ( irrecv.decode( &results )) { 
    Serial.println(results.value, HEX); 

    // Красный
    if (results.value==0xA25D58A7)
      setColor(255, 0, 0);

    //Оранжевый
    else if (results.value==0xA25DF807)
      setColor(255, 128, 0);

    //Желтый
    else if (results.value==0xA25D1AE5)
      setColor(255, 255, 0);

    //Зеленый
    else if (results.value==0xA25D6897)
      setColor(0, 255, 0);

    //Голубой
    else if (results.value==0xA25DD827)
      setColor(0, 255, 255);

    //Синий
    else if (results.value==0xA25D2AD5)
      setColor(0, 0, 255);

    //Фиолетовый
    else if (results.value==0xA25D48B7)
      setColor(255, 0, 255);

    else if (results.value==0xA25DC837)
      setColor(0, 0, 0);

    irrecv.resume();
  }
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
