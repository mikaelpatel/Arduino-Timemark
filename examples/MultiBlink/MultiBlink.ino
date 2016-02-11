/**
 * @file MultiBlink.ino
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
 * Demonstration of the Timemark library; handle several blinking LEDs
 * with different time periods.
 */

#include <Timemark.h>

Timemark trace(500);

const int led1 = 13;
Timemark blink1(500);

const int led2 = 12;
Timemark blink2(1000);

const int led3 = 11;
Timemark blink3(1500);

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("MultiBlink: started"));

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  trace.start();
  blink1.start();
  blink2.start();
  blink3.start();
}

void loop()
{
  // Trace LED status
  if (trace.expired()) {
    Serial.print(millis());
    Serial.print(' ');
    Serial.print(digitalRead(led1));
    Serial.print(' ');
    Serial.print(digitalRead(led2));
    Serial.print(' ');
    Serial.println(digitalRead(led3));
  }

  // Blink LED 1
  if (blink1.expired())
    digitalWrite(led1, !digitalRead(led1));

  // Blink LED 2
  if (blink2.expired())
    digitalWrite(led2, !digitalRead(led2));

  // Blink LED 3
  if (blink3.expired())
    digitalWrite(led3, !digitalRead(led3));
}
