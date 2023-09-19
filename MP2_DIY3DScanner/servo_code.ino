/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo servo_vertical;  // create servo object to control a servo
Servo servo_horizontal;

int vertical_pos = 0;    // variable to store the servo position
int horizontal_pos = 100;
int horizontal_min = 100;  // Minimum angle (in degrees)
int horizontal_max = 150;  // Maximum angle (in degrees)
int horizontal_direction = 1; // Direction 1 for forward, -1 for reverse

void setup() {
  servo_vertical.attach(11);    // attaches the horizontal servo on pin 10 to the servo object
  servo_horizontal.attach(10);  // attaches the horizontal servo on pin 10 to the servo object
}

void loop() {
  for (vertical_pos=0; vertical_pos <=60; vertical_pos +=1){
    servo_vertical.write(vertical_pos);
    delay(40);
  }
  for (vertical_pos=60; vertical_pos >=0; vertical_pos -=1){
    servo_vertical.write(vertical_pos);
    delay(40);
  }

  servo_horizontal.write(horizontal_pos);
  horizontal_pos += (10 * horizontal_direction);

  // Check if the horizontal_pos exceeds the limits
  if (horizontal_pos >= horizontal_max || horizontal_pos <= horizontal_min) {
    horizontal_direction *= -1; // Reverse direction
  }

  delay(15);
} 
