/* get angel sector */
int getSectorNumber(int _angel)
{
  return ((_angel - 1) / SECTOR_SIZE) + 1;
}

int getSpeed (int _speed, int _strength)
{
  int temp = _speed * _strength / 100;
  temp = MAX_SPEED * temp / 100;
  return temp;
}

/* setup speed for all sectors */
void auto_drive(int _angel, int _strength)
{
  int sector = getSectorNumber(_angel);
  int speed_left = 0;
  int speed_right = 0;

//  Serial.println("auto_drive ...");

  switch (sector)
  {
    case 1:
      speed_left = 100;
      speed_left = getSpeed (speed_left, _strength);

      speed_right = (_angel - 45) / 45.0 * 100;
      speed_right = getSpeed (speed_right, _strength);

      if (_angel < 45) 
      {
        go_Right(speed_left, speed_right);
      }
      else 
      {
        go_Advance (speed_left, speed_right);
      }
      Serial.print("Speed left = ");
      Serial.println(speed_left);

//      Serial.print("Speed right = ");
//      Serial.println(speed_right);
        
      break;

    case 2:
      speed_left = (135 - _angel) / 45.0 * 100;
      speed_left = getSpeed (speed_left, _strength);

      speed_right = 100;
      speed_right = getSpeed (speed_right, _strength);

      if (_angel < 135)
      {
        go_Advance(speed_left, speed_right);
      }
      else 
      {
        go_Left(speed_left, speed_right);
      }
      
      break;
      
    case 3:
      speed_left = -100;
      speed_left = getSpeed (speed_left, _strength);

      speed_right = (225 - _angel) / 45.0 * 100;
      speed_right = getSpeed (speed_right, _strength);

      if (_angel < 225)
      {
        go_Left(speed_left, speed_right);
      }
      else 
      {
        go_Back (speed_left, speed_right);
      }
        
      break;

    case 4:
      speed_left = (_angel - 315) / 45.0 * 100;
      speed_left = getSpeed (speed_left, _strength);

      speed_right = -100;
      speed_right = getSpeed (speed_right, _strength);

      if (_angel > 315)
      {
        go_Right(speed_left, speed_right);
      }
      else 
      {
        go_Back(speed_left, speed_right);
      }
        
      break;

    default:
      break;
  }  
  return;
}


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

void auto_stop()
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

/* set motor */
void initEngine()
{
  pinMode(dir1PinL,  OUTPUT); 
  pinMode(dir2PinL,  OUTPUT); 
  pinMode(speedPinL, OUTPUT); 
   
  pinMode(dir1PinR,  OUTPUT);
  pinMode(dir2PinR,  OUTPUT); 
  pinMode(speedPinR, OUTPUT);
  auto_stop();
}
