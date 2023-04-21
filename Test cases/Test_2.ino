// to test the ir sensor
const int startButton = 11;

const int left = A0;
const int right = A4;
const int middle = A2;
const int mid_left = A1;
const int mid_right = A3;

const int buzzer = 7;

// on every IR  sensor there should be a differnt sound made by buzzer

void setup(){
    pinMode(startButton, INPUT_PULLUP);
}

void loop(){
    // WRITE SOMETING SO THAT ON EVERY IR ACTIVATION THERE SHOULD BE A DIFFERENT PITCH USING PWM
}
