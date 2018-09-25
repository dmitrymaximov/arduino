#include <Servo.h>
#include "configuration.h"
Servo head;
bool stop_signal = false;

int mode = 0;
int angel = 0;
int strength = 0;



/*motor control*/
void go_Advance(int speed_L, int speed_R)
{
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL, LOW);
  digitalWrite(dir1PinR, HIGH);
  digitalWrite(dir2PinR, LOW);
  set_Motorspeed(speed_L, speed_R);
}

void go_Left(int speed_L, int speed_R)
{
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL, LOW);
  digitalWrite(dir1PinR, LOW);
  digitalWrite(dir2PinR, HIGH);
  set_Motorspeed(speed_L, speed_R);
}

void go_Right(int speed_L, int speed_R)
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL, HIGH);
  digitalWrite(dir1PinR, HIGH);
  digitalWrite(dir2PinR, LOW);
  set_Motorspeed(speed_L, speed_R);
}

void go_Back(int speed_L, int speed_R)
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL, HIGH);
  digitalWrite(dir1PinR, LOW);
  digitalWrite(dir2PinR, HIGH);
  set_Motorspeed(speed_L, speed_R);
}

void stop_Stop()
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL, LOW);
  digitalWrite(dir1PinR, LOW);
  digitalWrite(dir2PinR, LOW);
  set_Motorspeed(0, 0);
}

/* set motor speed */
void set_Motorspeed(int speed_L, int speed_R)
{
  analogWrite(speedPinL, speed_L); 
  analogWrite(speedPinR, speed_R);   
}

/* open buzzer */
void buzz_ON(int tune)
{
  digitalWrite(BUZZ_PIN, LOW);
  //pinMode(BUZZ_PIN, OUTPUT);
  //tone(BUZZ_PIN, tune, 100);
}

/* close buzzer */
void buzz_OFF()
{
  //digitalWrite(BUZZ_PIN, HIGH);
  pinMode(BUZZ_PIN, INPUT);
  noTone(BUZZ_PIN);
}

/* buzzer control */
void alarm()
{
   buzz_ON(1000);
   delay(100);
   buzz_OFF();
}

//WiFi / Bluetooth through the serial control
void do_Uart_Tick()
{
  //char Uart_Date = 0;
  //char Uart_Date = readCommandDataChar();
  String data = readCommandData();
  Serial.println(data);
  getCommandFromString(data);
  char Uart_Date = char(mode);
  
  //serial control instructions
  switch (Uart_Date)    
  {
    case COMMAND_BUZZ:
      Drive_Status = MANUAL_DRIVE; 
      Drive_Num = GO_BUZZ; 
      Serial.println("buzz");
      break;

    case COMMAND_FORWARD_STOP:
    case COMMAND_LEFT_STOP:
    case COMMAND_RIGHT_STOP:
    case COMMAND_BACK_STOP:
      stop_signal = true;
      Serial.println("stop signal");
      break;
      
    case COMMAND_FORWARD_RUN:
      Drive_Status = MANUAL_DRIVE; 
      stop_signal = false;
      Drive_Num = GO_ADVANCE;
      Serial.println("forward"); 
      break;
      
    case COMMAND_LEFT_RUN:
      Drive_Status = MANUAL_DRIVE; 
      stop_signal = false;
      Drive_Num = GO_LEFT; 
      Serial.println("turn left");
      break;
      
    case COMMAND_RIGHT_RUN:
      Drive_Status = MANUAL_DRIVE; 
      stop_signal = false;
      Drive_Num = GO_RIGHT; 
      Serial.println("turn right");
      break;
      
    case COMMAND_BACK_RUN:
      Drive_Status = MANUAL_DRIVE; 
      stop_signal = false;
      Drive_Num = GO_BACK; 
      Serial.println("go back");
      break;
      
    case COMMAND_STOP:
      Drive_Status = MANUAL_DRIVE; 
      Drive_Num = STOP_STOP;
      buzz_OFF();
      Serial.println("stop");
      break;
      
    case COMMAND_AVOIDANCE:
      Drive_Status = AUTO_DRIVE_UO; 
      Serial.println("avoid obstacles...");
      break;
      
    case COMMAND_LINE_FOLLOW:
      Drive_Status = AUTO_DRIVE_LF; 
      Serial.println("line follow...");
      break;
      
    default:
      break;
  }
}

String readCommandData()
{
  String commandString = "";

  while (Serial.available() > 0)
  {
    int inChar = Serial.read();
    commandString += char(inChar);
  }
  
  return commandString;
}


// Data format: <mode> + <angel> + <strength>
void getCommandFromString(String data)
{
  String sMode;
  String sAngel;
  String sStrength;

  int cPosition = 0;
  int dataNum = 0;
  char currentChat = data.charAt(cPosition);
  

  while(currentChat != '\n')
  {
    currentChat = data.charAt(cPosition);
    cPosition++; 

    if(currentChat == '+')
    {
      dataNum++;
    }
    else
    {
      if(dataNum == 0)
      {
        sMode += currentChat;
      }
      else if (dataNum == 1)
      {
        sAngel += currentChat;
        
      }
      else if (dataNum == 2)
      {
        sStrength += currentChat;
      }
      else
        break;
    }
  }
  mode = sMode.toInt();
  angel = sAngel.toInt();
  strength = sStrength.toInt();
}


char readCommandDataChar()
{
  char command;

  while (Serial.available() > 0)
  {
    command = Serial.read();
  }
  
  return command;
}


void getCommandData()
{
  int commandType = 0;
  
}

//car motor control
void do_Drive_Tick()
{
  if(Drive_Status == MANUAL_DRIVE)
  {
    switch (Drive_Num) 
    {
      case GO_ADVANCE:
          go_Advance(DEFAULT_SPEED, DEFAULT_SPEED);
          JogTime = millis();
          break;
          
      case GO_LEFT: 
          go_Left(DEFAULT_SPEED, DEFAULT_SPEED);
          JogTime = millis();
          break;
          
      case GO_RIGHT:  
          go_Right(DEFAULT_SPEED, DEFAULT_SPEED);
          JogTime = millis();
          break;
          
      case GO_BACK: 
          go_Back(DEFAULT_SPEED, DEFAULT_SPEED);
          JogTime = millis();
          break;
          
      case STOP_STOP: 
          stop_Stop();
          break;
          
      case GO_BUZZ:
          alarm();
          break;
          
      default:
          break;
    }
    Drive_Num = DEF;
    
    //keep the car running for 100ms
    if(millis() - JogTime >= JOB_TIME && stop_signal)
    {
      stop_Stop();
    }
  }
  else if(Drive_Status == AUTO_DRIVE_LF)
  {
    auto_tarcking();
  }
  else if(Drive_Status == AUTO_DRIVE_UO)
  {
    auto_avoidance();
  }
}

void setup()
{
  pinMode(dir1PinL,  OUTPUT); 
  pinMode(dir2PinL,  OUTPUT); 
  pinMode(speedPinL, OUTPUT);  
  pinMode(dir1PinR,  OUTPUT);
  pinMode(dir2PinR,  OUTPUT); 
  pinMode(speedPinR, OUTPUT); 
  stop_Stop();

  pinMode(BUZZ_PIN, OUTPUT);
  digitalWrite(BUZZ_PIN, LOW);
  
  
  pinMode(Trig_PIN, OUTPUT); 
  pinMode(Echo_PIN,INPUT); 

  pinMode(LFSensor_0, INPUT);
  pinMode(LFSensor_1, INPUT);
  pinMode(LFSensor_2, INPUT);
  pinMode(LFSensor_3, INPUT);
  pinMode(LFSensor_4, INPUT); 
  
  //In order to fit the Bluetooth module's default baud rate, only 9600
  Serial.begin(9600);
  digitalWrite(Trig_PIN, LOW);
  head.attach(SERVO_PIN);
  head.write(90);
}


void loop()
{
  do_Uart_Tick();
  do_Drive_Tick();
}

