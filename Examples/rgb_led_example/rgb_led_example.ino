byte yellowPin = 13;
byte redPin = 11;
byte greenPin = 8;

byte modeOff = 0;
byte modeBlink = 1;
byte modeStep = 2;

int getMode;


void setup() {
  // put your setup code here, to run once:
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //if(Serial.available())
    //getMode = Serial.parseInt();

  for (int i = 0; i < 3; i++)
  {
    digitalWrite(yellowPin, HIGH);
    delay(200);
    digitalWrite(redPin, HIGH);
    delay(200);
    digitalWrite(greenPin, HIGH);
    delay(200);

    digitalWrite(yellowPin, LOW);
    delay(200);
    digitalWrite(redPin, LOW);
    delay(200);
    digitalWrite(greenPin, LOW);
    delay(200);
  }
  
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(yellowPin, HIGH);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    delay(200);
  
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    delay(500);
  }
}
