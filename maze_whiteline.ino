const int startButton = 11;

const int left = A0;
const int ext_left = A5;
const int mid_left = A1;
const int middle = A2;
const int mid_right = A3;
const int ext_right = A6;
const int right = A4;
const int buzzer = 7;

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

void setup()
{
  Serial.begin(9600);
  pinMode(startButton, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(blue_led, OUTPUT);  // blue
  pinMode(green_led, OUTPUT); // green
  pinMode(red_led, OUTPUT);   // red
  //  lfspeed = 50000 / analogRead(7); //arbitrary conversion to convert analogRead to speed. Need to check if this works for all voltage levels
  turnspeed = lfspeed * 0.6; // idk what is this
}

void loop() // this is the loop main loop
{
  while (digitalRead(startButton) == 0) // waiting for the start button
  {                                     // Do nothing while waiting for button press
  }
  delay(1000);

  while (endFound == 0) // line following robot main code ----->
  {
    linefollow(); // follows line
    checknode();  // checks intersection
    botstop();    // stops bot
    delay(100);

    reposition(); // have to read about this
  }

  for (int x = 0; x < 4; x++) // convertor of the whole path to shortest path
  {
    str.replace("LULUS", "U");
    str.replace("LUSUL", "U");
    str.replace("LUL", "S");
    str.replace("SUL", "R");
    str.replace("LUS", "R");
    str.replace("RUL", "U");
  }
  int endpos = str.indexOf('E');

  while (digitalRead(startButton) == 0) // waits for the maze shortest path
  {                                     // Do nothing while waiting for button press
  }
  delay(1000);

  for (int i = 0; i <= endpos; i++) // maze shortest path
  {
    char node = str.charAt(i);
    paths = 0;
    while (paths < 2)
    {
      linefollow();
      checknode();
      if (paths == 1)
      {
        reposition();
      }
    }
    switch (node)
    {
    case 'L':
      botstop();
      delay(50);
      botleft();
      break;

    case 'S':
      break;

    case 'R':
      botstop();
      delay(50);
      botright();
      break;

    case 'E':
      for (int i = 0; i < 50; i++)
      {
        botinchforward();
      }
      red();
      botstop();
      delay(1000);
      break;
    } //_________end of switch
  }   //_________end of for loop
}

void showSensorData() // just prints out
{
  Serial.print("Sensor 0 -");
  Serial.print(analogRead(left));
  Serial.print("Sensor 1 -");
  Serial.print(analogRead(mid_left));
  Serial.print("Sensor 2 -");
  Serial.print(analogRead(middle));
  Serial.print("Sensor 3 -");
  Serial.print(analogRead(mid_right));
  Serial.print("Sensor 4- ");
  Serial.println(analogRead(right));
}

void linefollow() // line following function using pid function returns green
{                 // green () ;
  paths = 0;
  while ((analogRead(left) > threshold) && (analogRead(right) > threshold) && (analogRead(middle) < threshold)) // first is left
  {
    PID(); // takes pid values and returns corrctions based on error and gain
  }
  lightsoff(); // when straight line finished the lights turns off
}

void PID() // pid function takes error and corrects,
{
  int error1 = analogRead(mid_left) - analogRead(mid_right);
  int error2 = analogRead(ext_left) - analogRead(ext_right);
  int error = error1 + error2;

  P = error;                 // proportional
  I = I + error;             // integral
  D = error - previousError; // derivative

  PIDvalue = (Kp * P) + (Ki * I) + (Kd * D); // calculated value pid
  previousError = error;                     // previous error

  lsp = lfspeed - PIDvalue; // lsp left speed
  rsp = lfspeed + PIDvalue; // right speed

  if (lsp > 200)
  {
    lsp = 200; // sets max speed
  }
  if (lsp < 0)
  {
    lsp = 0; // set speed to null or zero
  }
  if (rsp > 200)
  {
    rsp = 200; // same as lsp sets max speed
  }
  if (rsp < 0)
  {
    rsp = 0; // same sets to zero
  }
  // sets speed and direction of motor
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  analogWrite(9, lsp);
  analogWrite(10, rsp);
}

void checknode() // returns yellow when detection
{
  yellow();  // yellow light  on to indicate node or any turn
  l = 0;     // left
  r = 0;     // right
  s = 0;     // straight
  u = 0;     // u turn
  e = 0;     // end
  paths = 0; // path

  // checks whethere bot is on node and the number of exits possible

  if (analogRead(right) < threshold)                                                                         // if right sensor is true
    r = 1;                                                                                                   // if  right most is true
  if (analogRead(left) < threshold)                                                                          // if left sensor is true
    l = 1;                                                                                                   // if left most is true
  if ((analogRead(left) > threshold && (analogRead(right) > threshold) && (analogRead(middle) > threshold))) // if all sensor are true
  {
    u = 1; // if the intersection ends  then u turn
  }
  if ((analogRead(middle) < threshold) && (analogRead(mid_right) < threshold) && (analogRead(right) < threshold)) // if all sensors are false
  {
    e = 1; // if the maze ends
  }

  if (u == 0)
  {
    for (int i = 0; i < FT; i++) // as fas as i know this loop runs 250 times casue ft is defined as ft (i think this is varied by how fast)
    {
      magenta(); // light turns to purple
      // botinchforward ();
      // this loop might be used for detecting a t junction and marks it
      PID();                             // simple pdi
      if (analogRead(right) < threshold) // same if right is true then right
      {
        r = 1;
      }
      if (analogRead(left) < threshold) // left is true then left
      {
        l = 1;
      }
    }
    for (int i = 0; i < FT; i++) // this loop also runs 250 times
    {
      cyan();
      // botinchforward ();
      PID();
      if (analogRead(middle) < threshold)
        s = 1;
      if ((e == 1) && (analogRead(mid_right) < threshold) && (analogRead(right) < threshold) && (analogRead(middle) < threshold))
        e = 2;
    }
  }

  if (u == 1)
  {
    for (int i = 0; i < 50; i++)
    {
      botinchforward(); // inch bot with cycle of fifty
    }
  }

  paths = l + s + r; // final path passed
}

void reposition() // takes the decision based on position returns blue
{
  blue();
  if (e == 2)
  {
    str += 'E';
    endFound = 1;
    red();
    botstop();
    delay(2000);
  }
  else if (l == 1)
  {
    if (paths > 1)
      str += 'L';
    botleft(); // take left
  }

  else if (s == 1)
  {
    if (paths > 1)
      str += 'S';
  }
  else if (r == 1)
  {
    if (paths > 1)
      str += 'R';
    botright(); // take right
  }

  else if (u == 1)
  {
    magenta();
    str += 'U';
    botuturn(); // take left
  }
  lightsoff();
}

void botleft() // left turn
{
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  analogWrite(9, lfspeed);
  analogWrite(10, lfspeed);
  delay(200);
  while (analogRead(middle) > threshold)
  {
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    analogWrite(9, lfspeed);
    analogWrite(10, lfspeed);
  }
  analogWrite(9, 0);
  analogWrite(10, 0);
  delay(50);
}

void botright() // right turn
{
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  analogWrite(9, lfspeed);
  analogWrite(10, lfspeed);
  delay(200);
  while (analogRead(middle) > threshold)
  {
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    analogWrite(9, lfspeed);
    analogWrite(10, lfspeed);
  }
  analogWrite(9, 0);
  analogWrite(10, 0);
  delay(50);
}

void botstraight() // strat line function
{
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  analogWrite(9, lfspeed);
  analogWrite(10, lfspeed);
}

void botinchforward() // moves bot an inch
{
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  analogWrite(9, turnspeed);
  analogWrite(10, turnspeed);
  delay(10);
}
void botstop() // stops the bot at the end
{
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  analogWrite(9, 0);
  analogWrite(10, 0);
}
void botuturn() // u turn of the bot
{
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  analogWrite(9, lfspeed * 0.8);
  analogWrite(10, lfspeed);
  delay(400);
  while (analogRead(middle) > threshold)
  {
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    analogWrite(9, lfspeed * 0.8);
    analogWrite(10, lfspeed);
  }
  analogWrite(9, 0);
  analogWrite(10, 0);
  delay(50);
}

// led functions to indicated specific tasks
void magenta()
{
  analogWrite(blue_led, 200); // BLUE
  analogWrite(green_led, 0);  // Green      // MAGENTA
  analogWrite(red_led, 150);  // red
}

void yellow()
{
  analogWrite(blue_led, 0);    // BLUE
  analogWrite(green_led, 200); // Green      // Yellow
  analogWrite(red_led, 150);   // red
}
void cyan()
{
  analogWrite(blue_led, 200);  // BLUE
  analogWrite(green_led, 200); // Green      // Cyan
  analogWrite(red_led, 0);     // red
}
void green()
{
  digitalWrite(blue_led, LOW);
  digitalWrite(green_led, HIGH); // GREEN
  digitalWrite(red_led, LOW);
}

void red()
{
  digitalWrite(blue_led, LOW);
  digitalWrite(green_led, LOW);
  digitalWrite(red_led, HIGH);
}
void blue()
{
  digitalWrite(blue_led, HIGH);
  digitalWrite(green_led, LOW);
  digitalWrite(red_led, LOW); // BLUE
}
void lightsoff()
{
  digitalWrite(blue_led, LOW);
  digitalWrite(green_led, LOW);
  digitalWrite(red_led, LOW);
}
