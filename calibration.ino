const int startButton = 11;

const int left = 0;
const int right = 4;
const int middle = 2;
const int mid_left = 1;
const int mid_right = 3;
const int num_sens = 5;
int thresh[num_sens], minValue[num_sens], maxValue[num_sens];

const int green_led = 5;
const int blue_led = 3;
const int red_led = 6;

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
    // turnspeed = lfspeed * 0.6; // idk what is this
}

void loop()
{
    // robot gol gol ghumta hai and takes values fast like helll
    while (digitalRead(startButton) == 0) // waiting for the start button
    {                                     // Do nothing while waiting for button press
    }
    calibration();
    threshold();
    while (digitalRead(startButton) == 0) // waiting for the start button
    {                                     // Do nothing while waiting for button press
    }
}

void calibration()
{
    delay(1000);
    for (int i = 0; i < num_sens; i++)
    {
        minValues[i] = analogRead(i);
        maxValues[i] = analogRead(i);
    }
    for (int i = 0; i < 3000; i++)
    {
        showSensorData();
        rotate();
        for (int i = 0; i < num_sens; i++)
        {
            if (analogRead(i) < minValue[i])
            {
                minValue[i] = analogRead(i);
            }
            if (analogRead(i) > maxValue[i])
            {
                maxValue[i] = analogRead(i);
            }
        }
    }
}

void threshold()
{
    for (int i = 0; i < num_sens; i++)
    {
        thresh[i] = (minValue[i] + maxValue[i]) / 2;
        Serial.print(thresh[i]);
        // Serial.print("   ");
    }
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
// roatate the robot on place
void rotate()
{
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    analogWrite(9, 100);
    analogWrite(10, 100);
}

void botstop() // stops the bot at the end
{
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    analogWrite(9, 0);
    analogWrite(10, 0);
}
