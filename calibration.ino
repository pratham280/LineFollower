const int startButton = 11;

const int left = 0;
const int right = 4;
const int middle = 2;
const int mid_left = 1;
const int mid_right = 3;
const int num_sens = 5;
int thresh[num_sens];

const int green = 5;
const int blue = 3;
const int red = 6;

void setup()
{
    Serial.begin(9600);
    pinMode(startButton, INPUT_PULLUP);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(blue, OUTPUT);  // blue
    pinMode(green, OUTPUT); // green
    pinMode(red, OUTPUT);   // red
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
}

void calibration()
{
    
    delay(1000);
    for (int i = 0; i < 3000; i++)
    {
        rotate();
        for (int i; i < num_sens; i++)
        {
            if analogRead(i) < minValue[i]
                Pass
            if analogRead(i) > maxValue[i]
                Pass
        }
    }
}

void threshold(){

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
