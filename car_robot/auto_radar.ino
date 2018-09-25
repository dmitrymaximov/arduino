
void radar()
{
  int distance;
  
  for(int i = 0; i < 180; i++)
  {
    head.write(i);
    distance = measure();
    delay(200);
    radarLog(i, distance);
  }
  
  for(int i = 180; i > 0; i--)
  {
    head.write(i);
    distance = measure();
    delay(200);
    radarLog(i, distance);
  }
}


int measure()
{
  digitalWrite(Trig_PIN, HIGH);
  digitalWrite(Trig_PIN, LOW);
  int distance = pulseIn(Echo_PIN, HIGH, 15000) / 50;
  return constrain(distance, 1, 300);
}

void radarLog(int angle, int distance)
{
  Serial.print(angle);
  Serial.print(":");
  Serial.print(distance);
  Serial.print(";");
}
  
