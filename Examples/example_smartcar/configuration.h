#define COMMAND_FORWARD_RUN     'a'
#define COMMAND_FORWARD_STOP    'b'

#define COMMAND_LEFT_RUN        'c'
#define COMMAND_LEFT_STOP       'd'

#define COMMAND_RIGHT_RUN       'e'
#define COMMAND_RIGHT_STOP      'f'

#define COMMAND_BACK_RUN        'g'
#define COMMAND_BACK_STOP       'h'

#define COMMAND_STOP        '5'
#define COMMAND_AVOIDANCE   '3'
#define COMMAND_LINE_FOLLOW '1'
#define COMMAND_BUZZ        '9'

#define TUNE_C        261
#define TUNE_C_SHARP  277
#define TUNE_D        294
#define TUNE_D_SHARP  311
#define TUNE_E        330
#define TUNE_F        349
#define TUNE_F_SHARP  370
#define TUNE_G        392
#define TUNE_G_SHARP  413
#define TUNE_A        440


#define JOB_TIME  10
#define DEFAULT_SPEED 255

/*Declare L298N Dual H-Bridge Motor Controller directly since there is not a library to load.*/
//Define L298N Dual H-Bridge Motor Controller Pins
#define dir1PinL  2    //Motor direction
#define dir2PinL  4    //Motor direction
#define speedPinL 6    // Needs to be a PWM pin to be able to control motor speed

#define dir1PinR  7    //Motor direction
#define dir2PinR  8    //Motor direction
#define speedPinR 5    // Needs to be a PWM pin to be able to control motor speed

/*From left to right, connect to D3,A1-A3 ,D10*/
#define LFSensor_0  3
#define LFSensor_1 A1
#define LFSensor_2 A2
#define LFSensor_3 A3
#define LFSensor_4 10

#define SERVO_PIN     9  //servo connect to D9

#define Echo_PIN   11   // Ultrasonic Echo pin connect to D11
#define Trig_PIN   12   // Ultrasonic Trig pin connect to D12

#define BUZZ_PIN     13  // buzzer connect to D13

int sensor[5];
#define AD_SPEED1   150  //avoidance motor speed
#define LF_SPEED2   200  //line follow motor speed

int leftscanval, centerscanval, rightscanval, ldiagonalscanval, rdiagonalscanval;
int distancelimit = 30;       //distance limit for obstacles in front           
int sidedistancelimit = 30;   //minimum distance in cm to obstacles at both sides (the car will allow a shorter distance sideways)
int turntime = 800;           //time the car spends turning (miliseconds)
int distance;
int numcycles = 0;

int thereis;
bool flag1=false;
bool stopFlag = true;
bool JogFlag = false;
uint16_t JogTimeCnt = 0;
uint32_t JogTime = 0;

#define MAX_PACKETSIZE 32    //Serial receive buffer
#define BUFFERSIZE 127
char buffUART[MAX_PACKETSIZE];
unsigned int buffUARTIndex = 0;
unsigned long preUARTTick = 0;

enum DS
{
  MANUAL_DRIVE,
  AUTO_DRIVE_LF, //line follow
  AUTO_DRIVE_UO  //ultrasonic obstruction
} Drive_Status = MANUAL_DRIVE;

enum DN
{ 
  GO_ADVANCE, 
  GO_LEFT, 
  GO_RIGHT,
  GO_BACK,
  GO_BUZZ,
  STOP_STOP,
  DEF
} Drive_Num = DEF;

