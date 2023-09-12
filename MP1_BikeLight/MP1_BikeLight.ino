uint16_t BLINK_INTERVAL = 100;
const uint8_t CHANGE_INTERVAL = 10;
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
  // initialize digital LED pins as an output.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(button, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  time = millis();
  CheckButtonState();
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

void CheckButtonState(){

  if((time-lastDebounce) >= CHANGE_INTERVAL)
  {
    if (debounce()) {
    blink_style ++;
    blink_style = blink_style % 5;
    }
    lastDebounce = millis();
  }
}

uint16_t btnStates = 0;

bool debounce(void)
{
  /* based off of http://www.ganssle.com/debouncing-pt2.htm and https://deepbluembedded.com/arduino-button-debouncing/
  - stores the button press history as a sequence of bits 
  - if the sequence matches a rising edge 0000 0000 1111 1111, a valid button press is detected
  */
  btnStates = (btnStates<<1) | (!digitalRead(button)); 
  return (btnStates == 0x00FF);
}