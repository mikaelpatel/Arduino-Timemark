/**
 * @file MouseClick.ino
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
 * Demonstration of the Timemark library; capture button push (pin 4)
 * and simulate mouse events.
 */

#include <Timemark.h>

Timemark debounce(40);
Timemark doubleClick(500);

const int buttonPin = 4;
bool buttonState;

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("MouseClick: started"));

  // Initiate button pin and state
  pinMode(buttonPin, INPUT_PULLUP);
  buttonState = digitalRead(buttonPin);

  // Start the button debounce timemark
  debounce.start();
}

void loop()
{
  // Check if the button debounce has expired
  if (debounce.expired()) {
    bool currentState = digitalRead(buttonPin);

    // Check if the button state has changed
    if (currentState != buttonState) {
      buttonState = currentState;

      // Check if button was pushed
      if (buttonState == LOW) {
	Serial.print(millis());
	Serial.println(F(":mouse down"));
      }
      // Button was released
      else {
	Serial.print(millis());
	Serial.println(F(":mouse up"));
	Serial.print(millis());
	Serial.print(':');
	Serial.print(doubleClick.elapsed());

	// Check type of click
	if (!doubleClick.running() || doubleClick.expired()) {
	  Serial.println(F(":click"));
	} else {
	  Serial.println(F(":double click"));
	}

	// Start the timemark for double click detect
	doubleClick.start();
      }
    }
  }
}
