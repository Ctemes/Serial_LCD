///
/// @file 	GUI.h 
/// @brief	GUI with label, button, dialog box, menu, slider
/// @details	GUI provides high-level elements for user graphic interface
/// @n
/// @n @a 	Member of Serial_LCD Library Suite
/// @n @a 	for 4D Systems uLCD-uLED-uVGA screens
/// @n @a 	on Arduino 0023 and 1.0, chipKIT MPIDE 0023, Wiring 1.0
///
/// @a 		Developed with [embedXcode](http://embedXcode.weebly.com)
/// @n
/// @author 	Rei VILO
/// @author 	http://embeddedcomputing.weebly.com
/// @date	Sep 01, 2012
/// @version 	release 317
/// @n
/// @copyright 	© Rei VILO, 2010-2012
/// @copyright 	CC = BY NC SA
/// @n		http://embeddedcomputing.weebly.com/serial-lcd.html
/// @n		http://github.com/rei-vilo/Serial_LCD
///
/// @see	4D Systems Goldelox and Picaso SGC Command Set
/// @n		http://www.4dsystems.com.au/
///

#define GUI_RELEASE 317

#ifndef GUI_h
#define GUI_h

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
#endif

// Other libraries
#include "Serial_LCD.h"

#if SERIAL_LCD_RELEASE < 334
#error required SERIAL_LCD_RELEASE 334
#endif



struct item {
  uint16_t index; ///<	index 0x1000..0xffff, 0x0000 reserved for menu root
  char label[16]; ///<	text
};
item setItem(uint8_t index0, String text0);

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))


class button {
public:
  button();
  void  define(Serial_LCD * lcd, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, item item0, uint16_t textColour1, uint16_t highColour1);
  void dDefine(Serial_LCD * lcd, uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, item item0, uint16_t textColour1, uint16_t highColour1);
  void  define(Serial_LCD * lcd, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, item item0, uint16_t textColour1, uint16_t highColour1, uint16_t lowColour1, uint8_t size0=9);
  void dDefine(Serial_LCD * lcd, uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, item item0, uint16_t textColour1, uint16_t highColour1, uint16_t lowColour1, uint8_t size0=9);
  void  stringDefine(Serial_LCD * lcd, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, String text0, uint16_t textColour1, uint16_t highColour1);
  void dStringDefine(Serial_LCD * lcd, uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, String text0, uint16_t textColour1, uint16_t highColour1);
  void  stringDefine(Serial_LCD * lcd, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, String text0, uint16_t textColour1, uint16_t highColour1, uint16_t lowColour1, uint8_t size0=9);
  void dStringDefine(Serial_LCD * lcd, uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, String text0, uint16_t textColour1, uint16_t highColour1, uint16_t lowColour1, uint8_t size0=9);
  boolean state();
  void draw(boolean flag=false);
  void enable(boolean flag=true);
  boolean check(boolean instant=false);
  uint16_t getIndex();
  
private:
  uint16_t _x1, _y1, _x2, _y2, _xt, _yt;
  uint16_t _textColour, _highColour, _lowColour;
  boolean _enable;  
  String _text;
  uint16_t _index;
  uint8_t _size;
  Serial_LCD * _pscreen;
};


uint8_t dialog(Serial_LCD * lcd, 
               String text0, uint8_t kind0, uint16_t textColour0, uint16_t highColour0, uint16_t lowColour0, 
               String text1="Press OK", String button1="OK", uint16_t textColour1=whiteColour, uint16_t highColour1=blueColour, uint16_t lowColour1=blackColour, 
               String text2="\0", String button2="\0", uint16_t textColour2=0, uint16_t highColour2=0, uint16_t lowColour2=0, 
               String text3="\0", String button3="\0", uint16_t textColour3=0, uint16_t highColour3=0, uint16_t lowColour3=0);

uint16_t menu(Serial_LCD * lcd, 
              item menuItem0[], uint8_t nItems0, 
              uint16_t textColour0, uint16_t highColourMain0, uint16_t highColourSub0);

void dLabel(Serial_LCD * lcd, 
            uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, 
            String text0, uint16_t textColour0=whiteColour, uint16_t backColour0=blackColour, 
            uint8_t horizontal0=0, uint8_t vertical0=0, uint8_t size0=9);

void  label(Serial_LCD * lcd, 
            uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, 
            String text0, uint16_t textColour0=whiteColour, uint16_t backColour0=blackColour, 
            uint8_t horizontal0=0, uint8_t vertical0=0, uint8_t size0=9);

boolean slider(Serial_LCD * lcd, 
               uint16_t &value, uint16_t min=0, uint16_t max=511, uint16_t step=8, 
               uint16_t minColour0=greenColour, uint16_t maxColour0=redColour, 
               String okText0="OK", uint16_t okTextColour0=whiteColour, uint16_t okColour0=blueColour, 
               String cancelText0="Cancel", uint16_t cancelTextColour0=whiteColour, uint16_t cancelColour0=yellowColour);

#endif










