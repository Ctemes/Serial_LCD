///
/// @file	Energy.h 
/// @brief	Power saving based on idle time
/// @details	Energy switches backlight off when inactivity period is reach to save energy
/// @n
/// @n @a	Member of Serial_LCD Library Suite
/// @n @a	for 4D Systems uLCD-uLED-uVGA screens
/// @n @a	on Arduino 0023 and 1.0, chipKIT MPIDE 0023, Wiring 1.0
///
/// @a		Developed with [embedXcode](http://embedXcode.weebly.com)
/// @n
/// @author	Rei VILO
/// @author	http://embeddedcomputing.weebly.com
/// @date	Jul 30, 2012
/// @version	release 305
/// @n
/// @copyright	© Rei VILO, 2010-2012
/// @copyright	CC = BY NC SA
/// @n		http://embeddedcomputing.weebly.com/serial-lcd.html
/// @n		http://github.com/rei-vilo/Serial_LCD
///
/// @see	4D Systems Goldelox and Picaso SGC Command Set
/// @n		http://www.4dsystems.com.au/
///


#define ENERGY_RELEASE 305

#ifndef Energy_h
#define Energy_h

// Core library - MCU-based
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1280__) // Arduino specific
#if (ARDUINO>=100)
#include "Arduino.h" // for Arduino 1.0
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

// Other libraries
#include "Serial_LCD.h"

#if SERIAL_LCD_RELEASE < 333
#error required SERIAL_LCD_RELEASE 333
#endif

class Energy {
public:
  Energy();
  void begin(Serial_LCD * lcd0, uint32_t seconds=3);
  void check(boolean flag);
  
private:
  Serial_LCD * _pscreen;
  uint32_t _ms;
  uint32_t _chrono;
  boolean _state;
};



#endif
