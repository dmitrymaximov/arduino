
// TODO
bool isConnected()
{
  
}

String getData()
{
  String str = String("");
  while (Serial.available() > 0)
  {
    char ch = Serial.read();
    Serial.print("in loop: char = ");
    Serial.println(ch);
    str.concat(ch);
    delay(5);
  }

  if (str == "" or str.toInt() == 0) {
    isCommand = false;
  }
  else {
    isCommand = true;
    Serial.print("str = ");
    Serial.println(str);
  }
  return str;
}

// Data format: <mode> + <angel> + <strength>
void getCommandFromString(String data)
{  

  Serial.print ("getCommandFromString data = ");
  Serial.println (data);
  
  String sMode = "";
  String sAngel = "";
  String sStrength = "";

  int cPosition = 0;
  int dataNum = 0;
  
  char currentChat = '0';
  
  while(currentChat >= '0' && currentChat <= '9' || currentChat == '+')
  {
    currentChat = data.charAt(cPosition);
    cPosition++; 

    if(currentChat == '+')
    {
      dataNum++;
    }
    else
    {
      switch (dataNum)
      {
        case 0:
          sMode += currentChat;
          break;
          
        case 1:
          sAngel += currentChat;
          break;

        case 2:
          sStrength += currentChat;
          break;

        default:
          break;
        
      }
    }
  }

  Drive_Status = sMode.toInt(); 
  angel = sAngel.toInt();
  strength = sStrength.toInt();
  
  Serial.print("getCommandFromString = Drive status = ");
  Serial.println(Drive_Status);
}

