// to test the ir sensor
// const int startButton = 11;

const int left = A0;
const int ext_left = A5;
const int mid_left = A1;
const int middle = A2;
const int mid_right = A3;
const int ext_right = A6;
const int right = A4;
const int buzzer = 7;

int blackValue = 900; // analog value of black
int whiteValue = 100; // analog value of white
int threshold = 150;
// on every IR  sensor there should be a differnt sound made by buzzer

void setup(){
    Serial.begin(9600);
    pinMode(startButton, INPUT_PULLUP);
    pinMode(buzzer, OUTPUT);
}

void loop(){
    soudn();
    // WRITE SOMETING SO THAT ON EVERY IR ACTIVATION THERE SHOULD BE A DIFFERENT PITCH USING PWM
}

void sound(){
    tone(buzzer, 2000, 1000);
    
}
