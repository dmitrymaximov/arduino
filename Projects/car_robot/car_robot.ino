#include <Servo.h>
#include "configuration.h"
Servo head;

uint32_t JogTime = 0;
#define JOB_TIME 100

void car_tick()
{
  if (millis() - JogTime >= JOB_TIME)
  {
    JogTime = millis();
    String data = getData();
      
    if (isCommand)
      getCommandFromString(data);
    
    switch (Drive_Status)
    {
      case DS_MANUAL_DRIVE:
//        Serial.println("DS_MANUAL_DRIVE...");
        auto_drive(angel, strength);
        break;

      case DS_AUTO_LF:
//        Serial.println("DS_AUTO_LF...");
        auto_tracking();
        break;

      case DS_AUTO_UO:
//        Serial.println("DS_AUTO_UO...");
        auto_avoidance();
        break;

      case DS_BUZZ:
//        Serial.println("DS_BUZZ...");
        playTone(DEFAULT_TONE, DEFAULT_TONE_TIME);
        Drive_Status = DS_DEF;
        break;

      case DS_SONG:
//        Serial.println("DS_SONG...");
        playSong();
        Drive_Status = DS_DEF;
        break;
        
      case DS_STOP:
//        Serial.println("DS_STOP...");
        auto_stop();
        Drive_Status = DS_DEF;
        break;

      case DS_FORWARD:
//        Serial.println("DS_FORWARD...");
        go_Advance(MAX_SPEED, MAX_SPEED);
        break;

      case DS_BACK:
//        Serial.println("DS_BACK...");
        go_Back(MAX_SPEED, MAX_SPEED);
        break;

      case DS_LEFT:
//        Serial.println("DS_LEFT...");
        go_Left(MAX_SPEED, MAX_SPEED);
        break;

      case DS_RIGHT:
//        Serial.println("DS_RIGHT...");
        go_Right(MAX_SPEED, MAX_SPEED);
        break;

      default:
//        Serial.println("DEFAULT ...");
        auto_stop();
        break;
    }
  }
}

void setup()
{
  Serial.begin(9600);
  
  initBuzz();
  initEngine();
  initAOSensors();
  //initLFSensors();  
}

void loop()
{  
  car_tick();
//  radar();
}
