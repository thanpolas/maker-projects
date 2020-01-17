// Set debug on or off
#define DEBUG 1

// Define Pins for RGB
#define BLUE 3
#define GREEN 5
#define RED 6

// define variables
int redValue;
int greenValue;
int blueValue;

int readRed=0;
int readGreen=0;
int readBlue=0;

// States:
// 1: Red
// 2: Green
// 3: Blue
int state = 1;

// 0 going down, 1 going up
int direction = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  redValue = 255;
  greenValue = 255;
  blueValue = 255;
}


// main loop
void loop()
{
  main_rgb_loop();
}

void main_rgb_loop() {
  #define delayTime 10 // fading time between colors in ms

  log("BEGIN");
  log("redValue in loop original: " + String(redValue));
  log("blueValue in loop original: " + String(blueValue));
  log("greenValue in loop original: " + String(greenValue));

  setNextValues();

  analogWrite(RED, redValue);
  analogWrite(BLUE, blueValue);
  analogWrite(GREEN, greenValue);

  delay(delayTime);

  readRed = analogRead(RED);    // read the input pin
  readGreen = analogRead(GREEN);    // read the input pin
  readBlue = analogRead(BLUE);    // read the input pin

  log("READ RED: " + String(readRed));
  log("READ GREEN: " + String(readGreen));
  log("READ BLUE: " + String(readBlue));
}

void log (String message) {
  if (DEBUG) {
    Serial.println(message);
  }
}

void setNextValues() {
  switch (state) {
    case 1:
      redValue = calculateNextValue(redValue);
      break;
    case 2:
      greenValue = calculateNextValue(greenValue);
      break;
    case 3:
      blueValue = calculateNextValue(blueValue);
      break;
  }
}

int calculateNextValue(int value) {
  if (direction == 0 && value == 0) {
    state += 1;
    if (state == 4) {
      direction = 1;
      state = 1;
    }

    return 0;
  }

  if (direction == 1 && value == 255) {
    state += 1;
    if (state == 4) {
      direction = 0;
      state = 1;
    }

    return 255;
  }

  int nextValue;
  if (direction == 0) {
    nextValue = value - 10;
  } else {
    nextValue = value + 10;
  }

  if (nextValue > 255) {
    nextValue = 255;
  }

  if (nextValue < 0) {
    nextValue = 0;
  }

  return nextValue;
}
