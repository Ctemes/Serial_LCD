///
/// @file	I2C_Serial.h
/// @brief	SC16IS750 I2C slave bridge to serial
/// @details	I2C to serial bridge and 8 I/Os 
/// @n	
/// @n	
/// @n @a	Developed with [embedXcode](http://embedXcode.weebly.com)
/// @n
/// @author 	Rei VILO
/// @author 	http://embeddedcomputing.weebly.com
/// @date	Sep 01, 2012
/// @version 	release 308
/// @n
/// @copyright	© Rei VILO, 2010-2012
/// @copyright	CC = BY NC SA
/// @n		http://embeddedcomputing.weebly.com/
///


#define I2C_SERIAL_RELEASE 308

#ifndef I2C_Serial_h
#define I2C_Serial_h

// Core library - MCU-based
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega32U4__) // Arduino specific
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
#pragma monmessage
#else // error
#error Platform not defined
#endif

//#include "Stream.h"
#include "Wire.h"
#include "Print.h"

#define ALL  0xff

class I2C_Serial : public Stream {
public:
  I2C_Serial(uint8_t number=0); 
  String WhoAmI();
  void begin(long baud=9600);
#if defined(ARDUINO) && (ARDUINO >= 100)
  virtual size_t write(uint8_t byte);
#else
  virtual void write(uint8_t byte);
#endif
  virtual int read();
  virtual int available();
  virtual void flush();
  virtual int peek(); // !
  uint8_t free();       
  boolean test();
  void loopback(boolean flag=true);
  void pinMode(uint8_t pin, uint8_t mode); 
  void digitalWrite(uint8_t pin, uint8_t value); 
  int digitalRead(uint8_t pin);
  void reset(uint8_t pin, uint8_t value=LOW, uint8_t ms=10);  
  
private:
  int8_t _address;
};

#endif




