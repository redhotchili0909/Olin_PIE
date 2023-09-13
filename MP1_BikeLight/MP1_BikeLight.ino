// Establishes an initial blink interval of 100 milliseconds, and a change interval of 10 milliseconds that prevents bouncing
uint16_t blink_interval = 100;
const uint8_t CHANGE_INTERVAL = 10;

// Stores the time of the last button press
unsigned long lastDebounce = 0;

// Programs the LEDs and the button to be connected to various sources on the Arduino
const uint8_t LED1 = 13;
const uint8_t LED2 = 12;
const uint8_t LED3 = 11;
const uint8_t button = 10;

// Establishes blink_time variables for each blink
uint32_t blink_time = 0;

// Sets the initial mode for the button to be LOW, and sets the lights to the first mode
int buttonMode = LOW;
int blink_style = 0;

// Turns all the LEDs to the LOW state
int ledState = LOW;

// Establishes the initial state of the button to be LOW
int buttonPrevState = LOW;

// Establishes values to be used to track amount of flashes of each light later in the program (for incremental blinking mode)
int green_count = 0;
int yellow_count = 0;
int red_count = 0;

// Sets up a clock for the program
uint32_t time = millis();

// The setup function runs once when you press reset or power the board
void setup()
{
  // Initializes digital LED pins as an output and the button as an input.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(button, INPUT);
}

// The loop function runs indefinitely as the program is active
void loop()
{
  // Sets the time to the current time for this loop
  time = millis();
  // Handles button presses/debounce
  CheckButtonState();
  // Sets the blink interval to the value of the potentiometer mapped from 0 to 1023 miliseconds
  blink_interval = analogRead(A0);
  if (blink_style == 0)
  {
    // Turns all the lights on
    all_on();
  }
  if (blink_style == 1)
  {
    // Blinks the lights on and off
    blink_on();
  }
  if (blink_style == 2)
  {
    // Turns some of the lights on alternatingly
    alternating_flashing();
  }
  if (blink_style == 3)
  {
    // Turns all the lights off
    all_off();
  }
  if (blink_style == 4)
  {
    // Turns the lights on in a incrementing pattern
    EIEIO();
  }
}

void all_on()
{
  // Sets all 3 LEDs on
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
}
void all_off()
{
  // Sets all 3 LEDs off
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}

void blink_on()
{
  // Check if we should start blinking the LEDs
  if (time - blink_time >= blink_interval)
  {

    blink_time = time;

    // Toggle the active LED state
    ledState = !ledState;

    // Set the LEDs to the toggled state
    digitalWrite(LED1, !ledState);
    digitalWrite(LED2, !ledState);
    digitalWrite(LED3, !ledState);
  }
}

void alternating_flashing()
{
  // Check if we should start blinking the LEDs
  if (time - blink_time >= blink_interval)
  {
    blink_time = time;

    // Toggle the active LED state
    ledState = !ledState;

    // Set some of the LEDs to the toggled state
    digitalWrite(LED1, !ledState);
    digitalWrite(LED2, ledState);
    digitalWrite(LED3, ledState);
  }
}

void EIEIO()
{
  // Check if we should start blinking the LEDs
  if (time - blink_time >= blink_interval)
  {
    blink_time = time;

    // Toggle the active LED state
    ledState = !ledState;

    // Switch on the green LED and increment the green count
    digitalWrite(LED1, !ledState);
    green_count += 1;

    // If the green count is greater than 10, switch on the yellow LED and reset the green count
    if (green_count > 10)
    {
      yellow_count++;
      digitalWrite(LED2, !ledState);
      green_count = 0;
    }

    // Same for the red LED
    if (yellow_count > 10)
    {
      red_count++;
      digitalWrite(LED3, !ledState);
      yellow_count = 0;
    }

    // Once the red count is greater than 10, reset it as there are no LEDs left to blink
    if (red_count > 10)
    {
      red_count = 0;
    }
  }
}

void CheckButtonState()
{
  // Check if its appropriate to test the button state
  if ((time - lastDebounce) >= CHANGE_INTERVAL)
  {
    // Do debounce
    if (debounce())
    {
      // if the button is pressed, increment the blink style
      blink_style++;
      // Modulo the blink style back into {0,1,2,3,4}
      blink_style = blink_style % 5;
    }
    // Update the last debounce check time
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
  btnStates = (btnStates << 1) | (!digitalRead(button));
  return (btnStates == 0x00FF);
}
