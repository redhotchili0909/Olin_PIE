const uint16_t BLINK_INTERVAL = 100;
const uint16_t CHANGE_INTERVAL = 10;

const uint8_t LED1 =13;
const uint8_t LED2 = 12;
const uint8_t LED3 = 11;
const uint8_t button = 10;

uint32_t blink_time1 = 0;
uint32_t blink_time2 = 0;
uint32_t blink_time3 = 0;

int  buttonMode = 0;
int blink_style = 0;

int ledState = LOW;

int buttonPrevState = LOW;

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
  if (blink_style == 0){
    all_on();
  }
  if (blink_style == 1){
    blink_on();
  }
  else if (blink_style == 2){
    bounce_on();
  }
}
void all_on(){
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
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
  if (timeCheck <= time + CHANGE_INTERVAL)
    buttonMode = digitalRead(button);
    if (buttonMode == HIGH && buttonPrevState == LOW) {
      blink_style ++;
      blink_style = blink_style % 3;
      buttonPrevState = HIGH;
    }
    if (buttonMode == LOW && buttonPrevState == HIGH) {
      buttonPrevState = LOW;
    }
    timeCheck = time;
}
