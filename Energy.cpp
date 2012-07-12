// 
// 4D Systems uLCD-uLED-uVGA Serial_LCD Library Suite
// Arduino 0023 and 1.0, chipKIT MPIDE 0023, Wiring 1.0
// ----------------------------------
//
//  Energy.cpp 
//  Library C++ code
//  ----------------------------------
//  Developed with embedXcode
//
// Jun 14, 2012 release 104
// See README.txt
//
// © Rei VILO, 2010-2012
//   CC = BY NC SA
//   http://embeddedcomputing.weebly.com/serial-lcd.html
//   http://github.com/rei-vilo/Serial_LCD
//
// For 
//   4D Systems Goldelox and Picaso SGC Command Set
//   http://www.4dsystems.com.au/
//
//

// Core library - MCU-based
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__) // Arduino specific
#if (ARDUINO>=100)
#include "arduino.h" // for Arduino 1.0
#else
#include "WProgram.h" // for Arduino 23
#endif
#elif defined(__32MX320F128H__) || defined(__32MX795F512L__) // chipKIT specific 
#include "WProgram.h"
#elif defined(__AVR_ATmega644P__) // Wiring specific
#include "Wiring.h"
#else
#error Board not supported.
#endif

// Library header
#include "Energy.h"

// Code
Energy::Energy() {
}

void Energy::begin(Serial_LCD * lcd0, uint32_t seconds) {
  _pscreen = lcd0;
  _ms = (uint32_t)seconds*1000;
  _chrono = millis();
  _state = true; // backlight on
}

void Energy::check(boolean flag) {
  if ( flag ) {
    _chrono = millis();
    if ( _state==false ) {
      _state = true;
      _pscreen->setBacklight(true); 
    }
  } else if ( (_state==true) & (millis()>_chrono+_ms) ) {
    _state = false;
    _pscreen->setBacklight(false);   
  }
}