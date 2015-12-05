// Define the GPIO pins each light is connected to.
int leftTop = 2;
int leftMiddle = 3;
int leftBottom = 4;
int middleMiddle = 5;
int rightTop = 6;
int rightMiddle = 7;
int rightBottom = 8;

// Save them in an array so we can easily iterate all of them.
int ledPins[] = {
  leftTop,
  leftMiddle,
  leftBottom,
  middleMiddle,
  rightTop,
  rightMiddle,
  rightBottom
};

int numLedPins = 7;

// Create arrays that hold which pins are part of which dice rolls.
int one[] = { middleMiddle };
int two[] = { leftTop, rightBottom };
int three[] = { leftTop, middleMiddle, rightBottom };
int four[] = { leftTop, leftBottom, rightTop, rightBottom };
int five[] = { leftTop, leftBottom, middleMiddle, rightTop, rightBottom };
int six[] = { leftTop, leftMiddle, leftBottom, rightTop, rightMiddle, rightBottom };

// All possible roles.
int* roles[] = { one, two, three, four, five, six };

// The pin the button is connected to.
int buttonPin = 12;

void setup() {

  // Setup the button as an input.
  pinMode(buttonPin, INPUT);

  // Set all LED pins as outputs.
  for(int i = 0; i < numLedPins; i++) {
    pinMode(ledPins[i], OUTPUT);
  }  
}

// These are all used for debouncing the button.
// From here: https://www.arduino.cc/en/Tutorial/Debounce
int currentButtonState = 0;
int buttonState = 0;
int lastButtonState = 0;
long debounceDelay = 50;
long lastDebounceTime = 0;

// the loop function runs over and over again forever
void loop() {

  currentButtonState = digitalRead(buttonPin);

  if(currentButtonState != lastButtonState) {
    lastDebounceTime = millis();
  }

  if((millis() - lastDebounceTime) > debounceDelay) {
    
    if(currentButtonState != buttonState) {
      buttonState = currentButtonState;
      
      if(buttonState == HIGH) {
        shuffle();
        role();
      }
    }
  }

  lastButtonState = currentButtonState;
}

/*
 * Rolls a dice by randomly choosing a number and
 * lighting up the appropriate LEDs.
 */
void role() {

  // Randomly pick a dice roll.
  int number = random(0, 6);

  // Grab the pins that make up this roll.
  int* rolePins = roles[number];

  // Turn off all LEDs.
  for(int i = 0; i < numLedPins; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  // Turn on the LEDs that repesent the dice roll.
  for(int i = 0; i < number + 1; i++) {
    digitalWrite(rolePins[i], HIGH);
  }
}

/*
 * Animates the dice by rolling them several times.
 */
void shuffle() {
  for(int i = 0; i < 25; i++) {
    role();
    delay(40);   
  }
}
