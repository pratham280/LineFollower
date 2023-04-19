const int startButton = 11;

const int left = 0;
const int right = 4;
const int middle = 2;
const int mid_left = 1;
const int mid_right = 3;

const int green = 5;
const int blue = 3;
const int red = 6;

int lsp = 100;    // speed left
int rsp = 100;    // speed right
int lfspeed = 80; // what is speed
int turnspeed;

void setup(){
    Serial.begin(9600);
    pinMode(startButton, INPUT_PULLUP);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(blue, OUTPUT);  // blue
    pinMode(green, OUTPUT); // green
    pinMode(red, OUTPUT);   // red
    //  lfspeed = 50000 / analogRead(7); //arbitrary conversion to convert analogRead to speed. Need to check if this works for all voltage levels
    turnspeed = lfspeed * 0.6; // idk what is this
}

void loop(){
    // robot gol gol ghumta hai and takes values fast like helll
}
