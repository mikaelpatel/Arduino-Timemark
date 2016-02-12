/**
 * @file MultiBlinkArray.ino
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
 * with different time periods. Modified version of MultiBlink using
 * an array of timemarks.
 */

#include <Timemark.h>

#define membersof(v) (sizeof(v) / sizeof(v[0]))

Timemark trace(500);

const int led[3] = { 13, 12, 11 };
const unsigned int limit[3] = { 500, 1000, 1500 };
Timemark blink[3];

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("MultiBlinkArray: started"));

  trace.start();
  for (unsigned int i = 0; i < membersof(led); i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
    blink[i].limitMillis(limit[i]);
    blink[i].start();
  }
}

void loop()
{
  if (trace.expired()) {
    Serial.print(millis());
    for (unsigned int i = 0; i < membersof(led); i++) {
      Serial.print(' ');
      Serial.print(digitalRead(led[i]));
    }
    Serial.println();
  }

  for (unsigned int i = 0; i < membersof(led); i++)
    if (blink[i].expired())
      digitalWrite(led[i], !digitalRead(led[i]));
}
