///
/// @file 	proxySerial.h
/// @brief	Serial port hardware abstraction layer
/// @details 	proxySerial handles hardware, software and I2C serial ports 
/// @n
/// @n @a 	Member of Serial_LCD Library Suite
/// @n @a 	for 4D Systems uLCD-uLED-uVGA screens
/// @n @a 	on Arduino 0023 and 1.0, chipKIT MPIDE 0023, Wiring 1.0
/// 
/// @a		Developed with [embedXcode](http://embedXcode.weebly.com)
/// @n
/// @author	Rei VILO
/// @author	http://embeddedcomputing.weebly.com
/// @date	Jul 08, 2012
/// @version	release 110
/// @n
/// @copyright	© Rei VILO, 2010-2012
/// @copyright	CC = BY NC SA
/// @n		http://embeddedcomputing.weebly.com/serial-lcd.html
/// @n		http://github.com/rei-vilo/Serial_LCD
///
/// @see	4D Systems Goldelox and Picaso SGC Command Set
/// @n		http://www.4dsystems.com.au/
///

///
/// @brief	Library release number
///
#define PROXYSERIAL_RELEASE 110

#ifndef proxy_Serial_h
#define proxy_Serial_h

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
#include "Stream.h"
const uint32_t securityDelay = 0;
String ftoa(float number, uint8_t precision=0, uint8_t size=0);
String utoa(uint64_t number, uint8_t precision=0, uint8_t size=0);
String htoa(uint32_t number, uint8_t size=0);
String ttoa(uint64_t number, uint8_t precision=0, uint8_t size=0);

class ProxySerial
{
public:
  ProxySerial(Stream * port0);
  void begin(uint16_t dummy);  // to be managed at serial port level
  void setXY16(boolean flag);
  void print(int8_t i);
  void print(uint8_t ui);
  void print(int16_t i);
  void print(uint16_t ui);
  void print(char c);
  void print(String s);
  uint8_t read();
  uint16_t read16();
  int8_t available();
  void flush();
  
private:
  uint16_t _millis;
  void _checkSpeed();
  Stream * _proxyPort;
};

#endif





