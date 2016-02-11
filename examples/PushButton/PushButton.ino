/**
 * @file PushButton.ino
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2016, Mikael Patel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * @section Description
 * Demonstrate Timemark library; push button handling with long push
 * down detect.
 */

#include <Timemark.h>

Timemark buttonDebounce(40);
Timemark buttonHold(400);

const int buttonPin = 4;
bool buttonState;
int nr = 0;

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("PushButton: started"));

  // Initiate button pin and state
  pinMode(buttonPin, INPUT_PULLUP);
  buttonState = digitalRead(buttonPin);

  // Start the button debounce timemark
  buttonDebounce.start();
}

void loop()
{
  // Check if the button debounce has expired
  if (buttonDebounce.expired()) {
    bool currentState = digitalRead(buttonPin);

    // Check if the button state has changed
    if (currentState != buttonState) {
      buttonState = currentState;

      // Check if button was pushed
      if (buttonState == LOW) {
	Serial.print(nr++);
	Serial.println(F(":push"));
	buttonHold.start();
      }
      else {
	buttonHold.stop();
      }
    }
    else {
      // Check if the button hold limit has expired
      if (buttonHold.expired()) {
	Serial.print(nr++);
	Serial.println(F(":hold"));
	buttonHold.stop();
      }
    }
  }
}
