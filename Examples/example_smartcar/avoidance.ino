/*detection of ultrasonic distance*/
int watch()
{
  long howfar;
  digitalWrite(Trig_PIN, LOW);
  delayMicroseconds(5);  
                                                                              
  digitalWrite(Trig_PIN, HIGH);
  delayMicroseconds(15);
  
  digitalWrite(Trig_PIN, LOW);
  howfar = pulseIn(Echo_PIN, HIGH);
  howfar = howfar * 0.01657; //how far away is the object in cm
  return round(howfar);
}

//Meassures distances to the right, left, front, left diagonal, right diagonal and asign them in cm to the variables rightscanval, 
//leftscanval, centerscanval, ldiagonalscanval and rdiagonalscanval (there are 5 points for distance testing)

void scanDistance (int canvas, int limit, int angel)
{
  canvas = watch();
  if(canvas < limit)
  {
    stop_Stop();
    Serial.println("stop");
    alarm();
  }
  head.write(angel);
  delay(100);
}

void watchsurrounding()
{                     
  scanDistance(centerscanval, distancelimit, 120);
  scanDistance(ldiagonalscanval, distancelimit, 170);
  scanDistance(leftscanval, sidedistancelimit, 120);
  scanDistance(ldiagonalscanval, distancelimit, 90);
  scanDistance(centerscanval, distancelimit, 40);
  scanDistance(rdiagonalscanval, distancelimit, 5);
  scanDistance(rightscanval, sidedistancelimit, 90);
  delay(300);
}

void auto_avoidance()
{
  // if nothing is wrong go forward using go() function above.
  go_Advance(AD_SPEED1, AD_SPEED1);  
  Serial.println("forward");
  
  numcycles++;
  if(numcycles >= 80)
  { 
    //Watch if something is around every 100 loops while moving forward 
    stop_Stop();
    watchsurrounding();
    
    if((leftscanval < sidedistancelimit || ldiagonalscanval < distancelimit) && \
      (rightscanval > sidedistancelimit || rdiagonalscanval > distancelimit))
    {
      go_Right(AD_SPEED1, AD_SPEED1);  
      Serial.println("turn right");
      delay(turntime);
      stop_Stop();
    }
    
    if((rightscanval < sidedistancelimit || rdiagonalscanval < distancelimit) && \
        (leftscanval > sidedistancelimit || ldiagonalscanval > distancelimit))
    {
      go_Left(AD_SPEED1, AD_SPEED1);
      Serial.println("turn left");
      delay(turntime);
      stop_Stop();
    }
    
    if((rightscanval < sidedistancelimit || rdiagonalscanval < distancelimit) && \
        (leftscanval < sidedistancelimit || ldiagonalscanval < distancelimit) && \
        (centerscanval < distancelimit))
    {
      stop_Stop();
    }

    //Restart count of cycles
    numcycles = 0; 
  }

  // use the watch() function to see if anything is ahead (when the robot is just moving forward and not looking around it will test the distance in front)
  distance = watch(); 

  // The robot will just stop if it is completely sure there's an obstacle ahead (must test 25 times) (needed to ignore ultrasonic sensor's false signals)
  if (distance < distancelimit)
    thereis++;

  //Count is restarted
  if (distance > distancelimit)
    thereis = 0;
      
  if (thereis > 25)
  {
    stop_Stop(); // Since something is ahead, stop moving.
    Serial.println("stop");
    thereis = 0;
  }
}
