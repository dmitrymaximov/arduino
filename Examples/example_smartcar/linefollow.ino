/*read line folloe sensors*/
void read_sensor_values()
{
  sensor[0] = digitalRead(LFSensor_0);
  sensor[1] = digitalRead(LFSensor_1);
  sensor[2] = digitalRead(LFSensor_2);
  sensor[3] = digitalRead(LFSensor_3);
  sensor[4] = digitalRead(LFSensor_4);
}

//Automatic tracking
void auto_tarcking()
{
  read_sensor_values();
  if(sensor[2] == HIGH)
  { 
    //The middle sensor is on the black line
    if(sensor[1] == LOW && sensor[3] == LOW)
    { 
      //Other sensors are in the white area
      go_Advance(LF_SPEED2, LF_SPEED2);
    }
    else if(sensor[1] == HIGH && sensor[3] == LOW)
    { 
      //The second sensor is also on the black line
       go_Left(0, LF_SPEED2);
    }
    else if(sensor[1] == LOW && sensor[3] == HIGH)
    {  
      //The fourth sensor is also on the black line
      go_Right(LF_SPEED2, 0);
    }
  }
  else if(sensor[2] == LOW)
  {  
    if(sensor[1] == HIGH && sensor[3] == LOW)
    { 
      //The middle sensor is in the white area
      go_Left(0, LF_SPEED2);
    }
    else if(sensor[1] == LOW && sensor[3] == HIGH)
    {
       go_Right(LF_SPEED2, 0);
    }
  }
  else {
     go_Back(LF_SPEED2, LF_SPEED2);
  }
  if(sensor[1]==HIGH)
  {  
    //The second sensor is on the black line
    if(sensor[0] == HIGH && sensor[2] == LOW)
    { 
      go_Left(0, LF_SPEED2);
    }
    else
    {
      go_Left(0, LF_SPEED2);
    }
  }
  if(sensor[3] == HIGH)
  {  
    //The fourth sensor is on the black line
    if(sensor[2] == LOW && sensor[4] == HIGH)
    {
      go_Right(LF_SPEED2,0);
    }
    else
    {
      go_Right(LF_SPEED2,0);
    }
  }
}

