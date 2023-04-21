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

void setup(){
   pinMode(startButton, INPUT_PULLUP);
   pinMode(Right_mot, OUTPUT);
   pinMode(left_mot, OUTPUT);
   pinMode(right_pwm, OUTPUT);
   pinMode(left_pwm, OUTPUT);
}
