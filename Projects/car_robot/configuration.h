bool isCommand = false;

/* ***** General configurations ***** */
/* Vars */
enum DS
{
  DS_MANUAL_DRIVE = 1,
  DS_AUTO_LF = 2,
  DS_AUTO_UO = 3,
  DS_BUZZ = 4,
  DS_FORWARD = 5,
  DS_BACK = 6, 
  DS_LEFT = 7,
  DS_RIGHT = 8,
  DS_SONG = 9,
  DS_STOP = 13,
  DS_DEF = 14
} Drive_Status = DS_DEF;
/* ***** */


/* ***** Auto drive configurations ***** */
/* Pins: Declare L298N Dual H-Bridge Motor Controller directly since there is not a library to load. */
#define dir1PinL  2    // Motor direction
#define dir2PinL  4    // Motor direction
#define speedPinL 6    // Needs to be a PWM pin to be able to control motor speed

#define dir1PinR  7    // Motor direction
#define dir2PinR  8    // Motor direction
#define speedPinR 5    // Needs to be a PWM pin to be able to control motor speed
/* Others */
#define SECTOR_SIZE   90
#define MAX_SPEED     255
#define JOB_TIME      10
/* Vars */
int angel = 0;
int strength = 0;
/* ***** */


/* ***** Auto linefollow configurations ***** */
/* Pins: From left to right, connect to D3, A1, A2, A3, D10 */
#define LFSensor_0  3
#define LFSensor_1  A1
#define LFSensor_2  A2
#define LFSensor_3  A3
#define LFSensor_4  10
/* Others */
#define LF_SPEED2   200  // line follow motor speed
/* Vars */
int sensor[5];
/* ***** */


/* ***** Auto avoidance configurations ***** */
/* Pins */
#define SERVO_PIN   9   // Servo connect to D9
#define Echo_PIN   11   // Ultrasonic Echo pin connect to D11
#define Trig_PIN   12   // Ultrasonic Trig pin connect to D12
/* Others */
#define AD_SPEED1   150  // avoidance motor speed
/* Vars */
int leftscanval, centerscanval, rightscanval, ldiagonalscanval, rdiagonalscanval;
int distancelimit = 30;       // distance limit for obstacles in front           
int sidedistancelimit = 30;   // minimum distance in cm to obstacles at both sides (the car will allow a shorter distance sideways)
int turntime = 800;           // time the car spends turning (miliseconds)
int distance;
int numcycles = 0;
int thereis;
/* ***** */


/* ***** Auto avoidance configurations ***** */
/* Pins */
#define BUZZ_PIN   13
/* Others */
#define DEFAULT_TONE 1275
#define DEFAULT_TONE_TIME 100
#define SONG_LENGTH 46
/* Vars */
int song_length = 46;
int song_tones_count = 30;
int song_tempo = 50;
  
String noteNames[] = { "D#4/Eb4", "E4", "F4", "F#4/Gb4", "G4", "G#4/Ab4", "A4", "A#4/Bb4", "B4", "C5", "C#5/Db5", "D5", "D#5/Eb5", "E5", "F5", "F#5/Gb5", "G5", "G#5/Ab5", "A5", "A#5/Bb5", "B5", "C6", "C#6/Db6", "D6", "D#6/Eb6", "E6", "F6", "F#6/Gb6", "G6", "rest" };
int tones[] = { 1607, 1516, 1431, 1351, 1275, 1203, 1136, 1072, 1012, 955, 901, 851, 803, 758, 715, 675, 637, 601, 568, 536, 506, 477, 450, 425, 401, 379, 357, 337, 318, 0 };
  
String notes[SONG_LENGTH] = {"G4","G4", "G4", "D#4/Eb4", "A#4/Bb4", "G4", "D#4/Eb4","A#4/Bb4", "G4", "D5", "D5", "D5", "D#5/Eb5", "A#4/Bb4", "F#4/Gb4", "D#4/Eb4","A#4/Bb4", "G4", "G5", "G4", "G4", "G5", "F#5/Gb5", "F5", "E5", "D#5/Eb5", "E5", "rest", "G4", "rest", "C#5/Db5", "C5", "B4", "A#4/Bb4", "A4", "A#4/Bb4", "rest", "D#4/Eb4", "rest", "F#4/Gb4", "D#4/Eb4", "A#4/Bb4", "G4", "D#4/Eb4", "A#4/Bb4", "G4"};
int beats[SONG_LENGTH] = {8, 8, 8, 6, 2, 8, 6, 2, 16, 8, 8, 8, 6, 2, 8, 6, 2, 16, 8, 6, 2, 8, 6, 2, 2, 2, 2, 6, 2, 2, 8, 6, 2, 2, 2, 2, 6, 2, 2, 9, 6, 2, 8, 6, 2, 16};
/* ***** */

