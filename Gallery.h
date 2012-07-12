///
/// @file 	Gallery.h 
/// @brief	Gallery of pictures
/// @details	4D Systems uLCD-uLED-uVGA Serial_LCD Library Suite
/// @n @a	for Arduino 0023 and 1.0, chipKIT MPIDE 0023, Wiring 1.0
///
/// @a 		Developed with [embedXcode](http://embedXcode.weebly.com)
/// 
/// @author 	Rei VILO
/// @author 	http://embeddedcomputing.weebly.com
/// @date 	Jun 14, 2012
/// @version 	release 105
/// @n
/// @copyright	© Rei VILO, 2010-2012
/// @copyright	CC = BY NC SA
/// @n		http://embeddedcomputing.weebly.com/serial-lcd.html
/// @n		http://github.com/rei-vilo/Serial_LCD
///
/// @see	4D Systems Goldelox and Picaso SGC Command Set
/// @n		http://www.4dsystems.com.au/
///

#define GALLERY_RELEASE 105

#ifndef Gallery_h
#define Gallery_h

// Core library - MCU-based
#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega2560__) // Arduino specific
#if defined(ARDUINO) && (ARDUINO >= 100)
#include "Arduino.h" // for Arduino 1.0
#else
#include "WProgram.h" // for Arduino 23
#endif
#elif defined(__32MX320F128H__) || defined(__32MX795F512L__) // chipKIT specific 
#include "WProgram.h"
#elif defined(__AVR_ATmega644P__) // Wiring specific
#include "Wiring.h"
#elif defined(__MSP430G2452__) || defined(__MSP430G2553__) || defined(__MSP430G2231__) // LaunchPad specific
#include "Energia.h"
#elif defined(MCU_STM32F103RB) || defined(MCU_STM32F103ZE) || defined(MCU_STM32F103CB) || defined(MCU_STM32F103RE) // Maple specific
#include "WProgram.h"	
#endif

// Other libraries
#include "Serial_LCD.h"
#include "vector_t.h"

#if SERIAL_LCD_RELEASE < 131
#error required SERIAL_LCD_RELEASE 131
#endif

class Gallery {
public:
  Gallery(); 
  ~Gallery();
  uint8_t begin(Serial_LCD * lcd0, String name);
  uint8_t number();
  uint8_t index();
  uint8_t showNext();
  uint8_t showPrevious();
  uint8_t showImage(uint8_t index=0);
  
private:
  struct image_t {
    //    String name;
    uint16_t msb, lsb, x, y;
  };
  Serial_LCD * _pscreen;
  String _name;
  uint8_t _index;
  Vector_t <image_t> _gallery;
};



#endif
