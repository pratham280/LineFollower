// Constants
#define KP 1.5         // Proportional gain
#define KD 5.0         // Derivative gain
#define KI 0.001       // Integral gain
#define MIN_SPEED 100  // Minimum motor speed
#define MAX_SPEED 255  // Maximum motor speed
#define BASE_SPEED 200 // Base motor speed
#define MAX_ERROR 700  // Maximum error
#define NUM_SENSORS 5  // Number of IR sensors

// Pin assignments
#define LEFT_MOTOR_DIR 3  // Left motor direction
#define LEFT_MOTOR_PWM 7  // Left motor PWM
#define RIGHT_MOTOR_DIR 5 // Right motor direction
#define RIGHT_MOTOR_PWM 2 // Right motor PWM
#define SENSOR_1 A0       // IR sensor 1
#define SENSOR_2 A1       // IR sensor 2
#define SENSOR_3 A2       // IR sensor 3
#define SENSOR_4 A3       // IR sensor 4
#define SENSOR_5 A4       // IR sensor 5
// #define SENSOR_6 X
// #define SENSOR_7 X
// #define SENSOR_8 z

// Global variables
int last_error = 0;             // Last error for derivative term
int total_error = 0;            // Total error for integral term
int sensor_values[NUM_SENSORS]; // IR sensor readings

void setup()
{
  // Set up motor pins as outputs
  pinMode(LEFT_MOTOR_DIR, OUTPUT);
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);

  pinMode(RIGHT_MOTOR_DIR, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);

  // Set up sensor pins as inputs
  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  pinMode(SENSOR_3, INPUT);
  pinMode(SENSOR_4, INPUT);
  pinMode(SENSOR_5, INPUT);

  // Set initial motor speeds
  analogWrite(LEFT_MOTOR_PWM, BASE_SPEED);
  analogWrite(RIGHT_MOTOR_PWM, BASE_SPEED);
  Serial.begin(9600);
}

void loop()
{
  // Read IR sensor values
  sensor_values[0] = analogRead(SENSOR_1);
  sensor_values[1] = analogRead(SENSOR_2);
  sensor_values[2] = analogRead(SENSOR_3);
  sensor_values[3] = analogRead(SENSOR_4);
  sensor_values[4] = analogRead(SENSOR_5);
  for (int i = 0; i < 5; i++)
  {
    Serial.println("this is sensor",i,sensor_values[i]);
  }
  // Calculate error as weighted sum of sensor values
  int error = 0;
  for (int i = 0; i < 5; i++)
  {
    error += sensor_values[i] * (i - 2);
  }

  // Calculate PID output
  int pid_output = KP * error + KD * (error - last_error) + KI * total_error;

  // Update last and total error
  last_error = error;
  total_error += error;

  Serial.println("this is overall error: ",error);

  // Limit total error to prevent integral windup
  if (total_error > MAX_ERROR)
  {
    total_error = MAX_ERROR;
  }
  else if (total_error < -MAX_ERROR)
  {
    total_error = -MAX_ERROR;
  }

  // Calculate motor speeds
  int left_speed = BASE_SPEED + pid_output;
  int right_speed = BASE_SPEED - pid_output;

  // Limit motor speeds
  if (left_speed > MAX_SPEED)
  {
    left_speed = MAX_SPEED;
  }
  else if (left_speed < MIN_SPEED)
  {
    left_speed = MIN_SPEED;
  }

  if (right_speed > MAX_SPEED)
  {
    right_speed = MAX_SPEED;
  }
  else if (right_speed < MIN_SPEED)
  {
    right_speed = MIN_SPEED;
  }

  // Set motor directions and speeds
  if (error > 0)
  {
    digitalWrite(LEFT_MOTOR_DIR, HIGH);
    digitalWrite(RIGHT_MOTOR_DIR, LOW);
    digitalWrite(4, LOW);
    digitalWrite(6, LOW);
    analogWrite(LEFT_MOTOR_PWM, left_speed);
    analogWrite(RIGHT_MOTOR_PWM, right_speed);
    Serial.println("that happend");
  }
  else if (error < 0)
  {
    digitalWrite(LEFT_MOTOR_DIR, LOW);
    digitalWrite(RIGHT_MOTOR_DIR, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(6, LOW);
    analogWrite(LEFT_MOTOR_PWM, left_speed);
    analogWrite(RIGHT_MOTOR_PWM, right_speed);
    Serial.println("this happend");
  }
  else
  {
    analogWrite(LEFT_MOTOR_PWM, BASE_SPEED);
    analogWrite(RIGHT_MOTOR_PWM, BASE_SPEED);
    Serial.println("what happend");
  }
}
