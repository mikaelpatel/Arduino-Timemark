/**
 * @file Timemark.h
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
 */

#ifndef TIMEMARK_H
#define TIMEMARK_H

/**
 * The Timemark class is an abstraction of the classical
 * "Blink-without-delay" pattern. Used in the format:
 * @code
 * Timemark mark(100);
 * ...
 * mark.start();
 * ...
 * if (mark.expired()) {
 *   ...
 *   mark.stop();
 * }
 * @endcode
 * The maximum timemark limit is approx 49 days.
 *
 * @section Reference
 * 1. https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 */
class Timemark {
public:
  /**
   * Construct timemark with the given time limit in milli-seconds.
   * @param[in] ms time limit in milli-seconds (Default 0).
   */
  Timemark(uint32_t ms = 0UL) :
    m_limitMillis(ms),
    m_previousMillis(0UL),
    m_running(false)
  {
  }

  /**
   * Get current timemark limit.
   * @return time limit.
   */
  uint32_t limitMillis()
  {
    return (m_limitMillis);
  }

  /**
   * Set timemark limit.
   * @param[in] ms time limit in milli-seconds.
   */
  void limitMillis(uint32_t ms)
  {
    m_limitMillis = ms;
  }

  /**
   * Get current timemark status. Return true if running otherwise
   * false.
   * @return bool.
   */
  bool running()
  {
    return (m_running);
  }

  /**
   * Returns true if the timemark has expired otherwise false. A new
   * time interval is started if the timemark was running and expired
   * was detected.
   * @return bool.
   */
  bool expired()
  {
    if (!m_running) return (false);
    uint32_t currentMillis = millis();
    if ((currentMillis - m_previousMillis) < m_limitMillis) return (false);
    m_previousMillis += m_limitMillis;
    return (true);
  }

  /**
   * Returns the number of milli-seconds that have elapsed since the
   * timemark was started. Zero is returned if the timemark is not running.
   * @return ms.
   */
  uint32_t elapsed()
  {
    if (!m_running) return (0UL);
    return (millis() - m_previousMillis);
  }

  /**
   * Start the timemark.
   */
  void start()
  {
    m_previousMillis = millis();
    m_running = true;
  }

  /**
   * Stop the timemark.
   */
  void stop()
  {
    m_running = false;
  }

protected:
  uint32_t m_limitMillis;
  uint32_t m_previousMillis;
  bool m_running;
};

#endif
