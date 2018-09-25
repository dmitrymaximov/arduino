#define NONE  0
#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

byte col = 0;
byte leds[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

byte rows[8] = {2, 7, 19, 5, 13, 18, 12, 16};
byte cols[8] = {6, 11, 10, 3, 17, 4, 8, 9};
byte cord[2] = {A0, A1};

float stepSize = 180.0 / 1024.0;

const byte MAX_SNAKE_LENGTH = 30;
byte snakeX[MAX_SNAKE_LENGTH];
byte snakeY[MAX_SNAKE_LENGTH];
byte snakeLength = 1;

byte fruitX, fruitY;
unsigned long fruitPrevTime = 0;
unsigned long fruitBlinkTime = 3;
bool fruitLed = HIGH;

unsigned long prevTime = 0;
unsigned long delayTime = 500;

byte prevDirection = NONE;
byte nextDirection = NONE;

bool playerLost = false;
bool isMatrixClear = false;
byte showLoseTimes = 5;
byte showenLoseTimes = 0;


void setup()
{
  randomSeed(analogRead(0));

  for (int i = 0; i < 8; i++) {
    pinMode(cols[i], OUTPUT);
    pinMode(rows[i], OUTPUT);
    
    digitalWrite(cols[i], LOW);
    digitalWrite(rows[i], LOW);
  }

  initNewGame();
}


void loop()
{
  unsigned long currentTime = millis();

  if (!playerLost)
  {
    byte direction = getDirection();
    if (direction != NONE)
    {
      if (prevDirection == LEFT && direction == RIGHT) nextDirection = prevDirection;
      else if (prevDirection == RIGHT && direction == LEFT) nextDirection = prevDirection;
      else if (prevDirection == UP && direction == DOWN) nextDirection = prevDirection;
      else if (prevDirection == DOWN && direction == UP) nextDirection = prevDirection;
      else nextDirection = direction;
    }
      
    
    if (currentTime - prevTime >= delayTime) 
    {
      nextstep();
      prevTime = currentTime;
    } 

    if (!playerLost) draw();
  }
  else
  {
    if (currentTime - prevTime >= delayTime) 
    {
      prevTime = currentTime;
      showenLoseTimes++;
      if (isMatrixClear)
      {
        clearMatrix();
        fillMatrix();
        isMatrixClear = false;
      }
      else
      {
        clearMatrix();
        isMatrixClear = true;
      }
      
      if (showenLoseTimes >= showLoseTimes)
        initNewGame();
    }
    displayMatrix();
  }
}

void initNewGame()
{
  showenLoseTimes = 0;
  playerLost = false;
  prevDirection = NONE;
  nextDirection = NONE;
  snakeLength = 1;
  snakeX[0] = 4;
  snakeY[0] = 7;
  makeFruit();
  for (int i = 1; i < MAX_SNAKE_LENGTH; i++)
    snakeX[i] = snakeY[i] = -1;
}

//------------
void drawSnake()
{
  for (int i = 0; i < snakeLength; i++)
  {
    byte x = snakeX[i];
    byte y = snakeY[i];
    leds[x][y] = 1;
  }
}

void drawFruit(){
  if(inPlayField(fruitX, fruitY)){
    unsigned long currenttime = millis();
    if(currenttime - fruitPrevTime >= fruitBlinkTime){
      fruitLed = !fruitLed;
      fruitPrevTime = currenttime;
    }
    leds[fruitX][fruitY] = fruitLed;
  }
}


void nextstep()
{
  for (int i = snakeLength - 1; i > 0; i--)
  {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  switch (nextDirection)
  {
    case LEFT:
      snakeY[0] = snakeY[0] - 1;
      prevDirection = LEFT;
      break;
    case DOWN:
      snakeX[0] = snakeX[0] + 1;
      prevDirection = DOWN;
      break;
    case RIGHT:
      snakeY[0] = snakeY[0] + 1;
      prevDirection = RIGHT;
      break;
    case UP:
      snakeX[0] = snakeX[0] - 1;
      prevDirection = UP;
      break;
  }

  if (!inPlayField(snakeX[0], snakeY[0]))
  {
    playerLost = true;
    return;
  }

  if (isCrossing())
  {
    playerLost = true;
    return;
  }

  if((snakeX[0] == fruitX) && (snakeY[0] == fruitY))
  {
    if(snakeLength < MAX_SNAKE_LENGTH)   
      snakeLength++;
    makeFruit();
  }
}

void clearMatrix()
{
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      leds[i][j] = 0;
}

void fillMatrix()
{
  for (int i = 0; i < 8; i++)
  {
    leds[i][i] = 1;
    leds[i][7-i] = 1;
    for (int j = 0; j < 8; j++)
    {
      if (i == 0 || j == 0)
        leds[i][j] = 1;
      else if (i == 7 || j ==7)
        leds[i][j] = 1; 
    }
  }
}

void draw()
{
  clearMatrix();
  drawSnake();
  drawFruit();
  displayMatrix();
}


boolean inPlayField(byte x, byte y)
{
  return (x>=0) && (x<8) && (y>=0) && (y<8);
}

void makeFruit()
{
  byte x = random(0, 8);
  byte y = random(0, 8);
  while(isPartOfSnake(x, y))
  {
    x = random(0, 8);
    y = random(0, 8);
  }
  fruitX = x;
  fruitY = y;
}

  
bool isCrossing()
{
  for (int i = 0; i < snakeLength; i++)
    for (int j = 0; j < snakeLength; j++)
      if (i != j)
        if (snakeX[i] == snakeX[j] && snakeY[i] == snakeY[j])
          return true;
  return false;
}


boolean isPartOfSnake(byte x, byte y)
{
  for(int i = 0; i < snakeLength - 1; i++)
    if((x == snakeX[i]) && (y == snakeY[i]))
      return true;
  return false;
}



void displayMatrix()
{
  digitalWrite(cols[col], HIGH);  // Turn whole previous column off
  col++;
  
  if (col == 8) col = 0;

  for (int row = 0; row < 8; row++)
    if (leds[col][7 - row] == 1)  digitalWrite(rows[row], HIGH);  // Turn on this led
    else  digitalWrite(rows[row], LOW); // Turn off this led

  digitalWrite(cols[col], LOW); // Turn whole column on at once (for equal lighting times)
}


byte getDirection()
{
  int xVal = analogRead(cord[0]);
  int yVal = analogRead(cord[1]);

  float xAngle = xVal * stepSize;
  float yAngle = yVal * stepSize;

  if ((xAngle >= 45) && (xAngle <= 135) && (yAngle <= 45))        return UP;
  else if ((xAngle >= 45) && (xAngle <= 135) && (yAngle >= 135))  return DOWN;
  else if ((yAngle >= 45) && (yAngle <= 135) && (xAngle <= 30))   return LEFT;
  else if ((yAngle >= 45) && (yAngle <= 135) && (xAngle >= 135))  return RIGHT;
  else return NONE;
}
