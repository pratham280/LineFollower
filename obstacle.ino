const int startButton = 11;

const int left = A0;
const int ext_left = A5;
const int mid_left = A1;
const int middle = A2;
const int mid_right = A3;
const int ext_right = A6;
const int right = A4;
const int PingPin = 7;
const int 
// add ultrasonic logic and also the 
const int green_led = 5;
const int blue_led = 3;
const int red_led = 6;

bool l = 0;    // left
bool r = 0;    // right
bool s = 0;    // straight
bool u = 0;    // back
int e = 0;     // end of the maze
int paths = 0; // over all path

bool endFound = 0; // end found as it is

int blackValue = 900; // analog value of black
int whiteValue = 100; // analog value of white
int threshold = 660;  // threshhold value invert this value to change to differnt contrast
// int threshold = (blackValue + whiteValue) * 0.5;

int FT = 250; // this is cycles based on how fast is the robot (cycles are inversely poroportional to speed)

int P, D, I, previousError, PIDvalue, error; // ititate values pdi and error previous error and pid values calculated
int lsp = 100;                               // speed left
int rsp = 100;                               // speed right
int lfspeed = 80;                            // what is speed
int turnspeed;                               // turn speed will further change
// gain values will alter later
float Kp = 0.04;
float Kd = 0.05;
float Ki = 0.01;

String str; // path as a string

/*
  Ping))) Sensor

  This sketch reads a PING))) ultrasonic rangefinder and returns the distance
  to the closest object in range. To do this, it sends a pulse to the sensor to
  initiate a reading, then listens for a pulse to return. The length of the
  returning pulse is proportional to the distance of the object from the sensor.

  The circuit:
    - +V connection of the PING))) attached to +5V
    - GND connection of the PING))) attached to ground
    - SIG connection of the PING))) attached to digital pin 7

  created 3 Nov 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Ping
*/

long duration, inches, cm;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    // establish variables for duration of the ping, and the distance result
    // in inches and centimeters:

    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);

    // The same pin is used to read the signal from the PING))): a HIGH pulse
    // whose duration is the time (in microseconds) from the sending of the ping
    // to the reception of its echo off of an object.
    pinMode(pingPin, INPUT);
    duration = pulseIn(pingPin, HIGH);

    // convert the time into a distance
    inches = microsecondsToInches(duration);
    cm = microsecondsToCentimeters(duration);

    delay(100);
}

long microsecondsToInches(long microseconds)
{
    return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
    return microseconds / 29 / 2;
}


// the question is wether to take inches or seconds ? 

