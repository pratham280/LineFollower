// test for rotating the robot and testing the motor

/*
   Motor Right Dir- 7
   Motor Right PWM- 9
   Motor Left Dir- 8
   Motor Left PWM- 10
   RGB- 6,5,3
*/

const int startButton = 11;
const int right_mot = 7;
const int left_mot = 8;
const int right_pwm = 9;
const int left_pwm = 10;

const int buzzer = 3;

void setup()
{
   pinMode(startButton, INPUT_PULLUP);
   pinMode(Right_mot, OUTPUT);
   pinMode(left_mot, OUTPUT);
   pinMode(right_pwm, OUTPUT);
   pinMode(left_pwm, OUTPUT);
}

void loop()
{
   forward();
   delay(5000);

   stop();

   back();
   delay(5000);

   stop();

   clock_rotate();
   delay(7000);

   stop();
   
   anti_rotate();
   delay(7000);

   stop();

}

void forward()
{
   digitalWrite(7, HIGH);
   digitalWrite(8, HIGH);
   analogWrite(9, 255);
   analogWrite(10, 255);
}

void back()
{
   digitalWrite(7, HIGH);
   digitalWrite(8, HIGH);
   analogWrite(9, 255);
   analogWrite(10, 255);
}
// void left()
// {
// }
// void right()
// {
// }
void clock_rotate()
{
   digitalWrite(7, LOW);
   digitalWrite(8, HIGH);
   analogWrite(9, 255);
   analogWrite(10, 255);
}
void anti_rotate()
{
   digitalWrite(7, HIGH);
   digitalWrite(8, LOW);
   analogWrite(9, 255);
   analogWrite(10, 255);
}
void stop()
{
   digitalWrite(7, HIGH);
   digitalWrite(8, HIGH);
   analogWrite(9, 0);
   analogWrite(10, 0);
   delay(1000);
}
/*
the sequence will be a loop which will run :
   front
   back
   left
   right
   rotate
   and come back to original position
*/
