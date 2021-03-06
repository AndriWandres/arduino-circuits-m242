/*
 * This program controls the 7-segment display on the arduino multifunction shield and functions as a stopwatch.
 * 
 * BUTTON_1 => Starts/Stops the timer
 * BUTTON_2 => Resets the timer to 0
 * 
 */

#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

float timer = 0;
byte timerStarted = false;

void setup() {
  Serial.begin(9600);
  Timer1.initialize();
  MFS.initialize(&Timer1);
  MFS.write(0);
}

void loop() {
  byte button = MFS.getButton();
  byte buttonAction = button & B11000000;
  byte buttonNumber = button & B00111111;

  // If BUTTON_1 is pressed
  if (button && buttonAction == BUTTON_SHORT_RELEASE_IND && buttonNumber == 1) {
    // Toggle blinking display
    MFS.blinkDisplay(DIGIT_ALL, timerStarted ? ON : OFF);
    
    // Start/Stop timer
    timerStarted = !timerStarted;
  }

  // If BUTTON_2 is pressed
  if (button && buttonAction == BUTTON_SHORT_RELEASE_IND && buttonNumber == 2) {
    timerStarted = false;
    MFS.write(0);
    MFS.blinkDisplay(DIGIT_ALL, OFF);
  }

  if (timerStarted) {
    // Increase timer by 100ms
    delay(100);
    MFS.write(timer += 0.1);
  } else {
    // Reset timer
    timer = 0;
  }
}
