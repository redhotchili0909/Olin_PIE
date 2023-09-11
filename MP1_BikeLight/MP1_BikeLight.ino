uint16_t BLINK_INTERVAL = 100;
const uint16_t CHANGE_INTERVAL = 10;
unsigned long lastDebounce = 0;
const uint8_t LED1 =13;
const uint8_t LED2 = 12;
const uint8_t LED3 = 11;
const uint8_t button = 10;

uint32_t blink_time1 = 0;
uint32_t blink_time2 = 0;
uint32_t blink_time3 = 0;

int  buttonMode = LOW;
int blink_style = 0;

int ledState = LOW;

int buttonPrevState = LOW;

int green_count = 0;
int yellow_count = 0;
int red_count = 0;

uint32_t time = millis();
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(button, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  time = millis();
  checkButtonState();
  BLINK_INTERVAL = analogRead(A0);
  if (blink_style == 0){
    all_on();
  }
  if (blink_style == 1){
    blink_on();
  }
  if (blink_style == 2){
    bounce_on();
  }
  if (blink_style == 3){
    all_off();
  }
  if (blink_style == 4){
    wave();
  }
}
void all_on(){
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
}
void all_off(){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}
void wave(){
  if (time - blink_time1 >= BLINK_INTERVAL) {

      blink_time1 = time;

      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      green_count += 1;
      digitalWrite(LED1, !ledState);
      if (green_count > 10) {
        yellow_count++;
        digitalWrite(LED2, !ledState);
        green_count = 0;
      }
      if (yellow_count > 10) {
        red_count++;
        digitalWrite(LED3, !ledState);
        yellow_count = 0;
      }
      if (red_count > 10){
        red_count = 0;
      }
    }
}
void blink_on(){
  if (time - blink_time1 >= BLINK_INTERVAL) {

      blink_time1 = time;

      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }

      digitalWrite(LED1, !ledState);
      digitalWrite(LED2, !ledState);
      digitalWrite(LED3, !ledState);
    }
}
void bounce_on(){
  if (time - blink_time2 >= BLINK_INTERVAL) {

      blink_time2 = time;

      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }

      digitalWrite(LED1, !ledState);
      digitalWrite(LED2, ledState);
      digitalWrite(LED3, ledState);
    }
}
uint32_t timeCheck = time;
void checkButtonState(){
  buttonMode = digitalRead(button);
  if (timeCheck <= time + CHANGE_INTERVAL)
    buttonMode = digitalRead(button);
    if (buttonMode == HIGH && buttonPrevState == LOW) {
      blink_style ++;
      blink_style = blink_style % 5;
      buttonPrevState = HIGH;
    }
    if (buttonMode == LOW && buttonPrevState == HIGH) {
      buttonPrevState = LOW;
    }
    timeCheck = time;
}


int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

int ledState2 = HIGH;
void checkButtonState2(){
  int reading = digitalRead(button);
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState2 = !ledState2;
      }
    }
  }

  // set the LED:
  if (ledState2 == HIGH){
    blink_style ++;
    blink_style = blink_style % 5;
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;

}

