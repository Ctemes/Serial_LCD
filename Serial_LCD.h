///
/// @file 	Serial_LCD.h 
/// @brief	Core library
/// @details 	Serial_LCD provides the core functions to display text and graphic, track touch, read and write on SD-card, play sound
/// @n
/// @n @a 	Member of Serial_LCD Library Suite
/// @n @a	for 4D Systems uLCD-uLED-uVGA Serial_LCD Library Suite
/// @n 		on Arduino 0023 and 1.0, chipKIT MPIDE 0023, Wiring 1.0
///
/// @a 		Developed with [embedXcode](http://embedXcode.weebly.com)
/// 
/// @author 	Rei VILO
/// @author 	http://embeddedcomputing.weebly.com
/// @date	Jul 30, 2012
/// @version	release 333
/// @n
/// @copyright 	© Rei VILO, 2010-2012
/// @copyright 	CC = BY NC SA
/// @n		http://embeddedcomputing.weebly.com/serial-lcd.html
/// @n		http://github.com/rei-vilo/Serial_LCD
///
/// @see 	4D Systems Goldelox and Picaso SGC Command Set
/// @n		http://www.4dsystems.com.au/
///
///


#define SERIAL_LCD_RELEASE 333

#ifndef Serial_LCD_h
#define Serial_LCD_h

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
#include "proxySerial.h"

#if PROXYSERIAL_RELEASE < 311
#error required PROXYSERIAL_RELEASE 311
#endif

const uint8_t __uOLED__ = 0; ///<	8-bits uLED=0
const uint8_t __uLCD__  = 1; ///<	16-bits uLCD=1
const uint8_t __uVGA__  = 2; ///<	16-bits uVGA=2

const uint8_t __Goldelox__ = 0; ///<	8-bits Goldelox=0
const uint8_t __Picaso__   = 1; ///<	16-bits Picaso=1

const uint16_t blackColour   = 0b0000000000000000; ///<	black
const uint16_t whiteColour   = 0b1111111111111111; ///<	white
const uint16_t redColour     = 0b1111100000000000; ///<	red
const uint16_t greenColour   = 0b0000011111100000; ///<	green
const uint16_t blueColour    = 0b0000000000011111; ///<	blue
const uint16_t yellowColour  = 0b1111111111100000; ///<	yellow
const uint16_t cyanColour    = 0b0000011111111111; ///<	cyan
const uint16_t orangeColour  = 0b1111101111100000; ///<	orange
const uint16_t magentaColour = 0b1111100000001111; ///<	magenta
const uint16_t violetColour  = 0b1111100000011111; ///<	violet
const uint16_t grayColour    = 0b0111101111101111; ///<	gray

// Objects
//
class Serial_LCD {
public:
  Serial_LCD(ProxySerial * port0); // uint8_t receivePin, uint8_t transmitPin); // constructor
  void begin(int8_t resetPin=-1); // AutoBaud – 55hex
  uint8_t setSpeed(uint32_t speed); // Set new Baud-Rate - 51hex
  String WhoAmI(); // Version-Device Info Request – 56hex
  uint8_t replaceBackGroundColour(uint16_t colour);  // Replace Background Colour – 42hex
  uint8_t clear(); // Clear Screen – 45hex
  uint8_t setBacklight(boolean flag);   // Display Control Functions – 59hex
  uint8_t setDisplay(boolean flag);   // Display Control Functions – 59hex
  uint8_t setContrast(uint8_t contrast);   // Display Control Functions – 59hex
  uint8_t setOrientation(uint8_t orientation);   // Display Control Functions – 59hex
  uint8_t getOrientation();  // Display Control Functions – 59hex
  uint8_t setResolutionVGA(uint8_t resolution);   // Set VGA Resolution Control Functions – 59hex
  uint8_t setVolume(uint8_t percent); // Set Volume - 76hex
  uint8_t protectFAT(boolean flag);  // Display Control Functions – 59hex
  uint8_t checkScreenType();
  uint8_t checkControllerType();
  uint8_t checkHardwareVersion();
  uint8_t checkSoftwareVersion();
  void off(); // Highly recommended at the end
  uint8_t fontX();
  uint8_t fontY(); 
  uint16_t maxX();
  uint16_t maxY();
  uint8_t nacAck(); // 0x06=success, 0x15=error
  uint8_t circle(uint16_t x1, uint16_t y1, uint16_t radius, uint16_t colour);  // Draw Circle – 43hex
  uint8_t triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t colour);  // Draw Triangle – 47hex 
  uint8_t setBackGroundColour(uint16_t colour=blackColour);   // Set Background colour – 4Bhex
  uint8_t dLine(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t colour);  // Draw Line – 4Chex
  uint8_t line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour);  // Draw Line – 4Chex
  uint8_t rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t colour);  // Draw Rectangle – 72hex
  uint8_t dRectangle(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t colour);  // Draw Rectangle – 72hex 
  uint8_t ellipse(uint16_t x, uint16_t y, uint16_t rx, uint16_t ry, uint16_t colour); // Draw Ellipse – 65hex
  uint8_t point(uint16_t x1, uint16_t y1, uint16_t colour);   // Draw Pixel – 50hex
  uint16_t readPixel(uint16_t x1, uint16_t y1); // Read Pixel – 52hex
  uint8_t copyPaste(uint16_t xs, uint16_t ys, uint16_t xt, uint16_t yt, uint16_t dx, uint16_t dy); // Screen Copy-Paste – 63hex
  uint8_t setPenSolid(boolean flag=true);    // Set Pen Size 1=solid; 0=wire frame – 70hex
  uint8_t setFont(uint8_t size=0);  // Set Font – 46hex
  uint8_t setFontSolid(boolean flag=true);  // Set 0=Transparent-1=Opaque Text – 4Fhex
  uint8_t tText(uint8_t x, uint8_t y, String s, uint16_t colour=whiteColour);  // Draw “String” of ASCII Text (text format) – 73he
  uint8_t gText(uint16_t x, uint16_t y, String s, uint16_t colour=whiteColour, uint8_t ix=1, uint8_t iy=1);    
  uint8_t setTouch(boolean flag);   // Display Control Functions – 59hex
  uint8_t getTouchActivity();   // Get Touch Coordinates - 6Fhex 
  uint8_t getTouchXY(uint16_t &x, uint16_t &y);   // Get Touch Coordinates - 6Fhex
  uint8_t dDetectTouchRegion(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy);
  uint8_t detectTouchRegion(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2); // Detect Touch Region - 75hex
  uint8_t saveScreenRAW(uint32_t sector);   // Screen Copy-Save to Card (RAW) - @43hex
  uint8_t dSaveScreenRAW(uint32_t sector, uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy);  // x0, y0 and width and height
  uint8_t saveScreenRAW(uint32_t sector, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);  // x1, y1 x2, y2: same coordinates as rectangle
  uint8_t readScreenRAW(uint32_t sector, uint16_t x1=0, uint16_t y1=0); // x1, y1: left-top coordinates
  uint32_t getSectors(uint16_t dx, uint16_t dy, uint16_t sizeSector=512); // sector = 512
  uint8_t initSD();   // Initialise Memory Card - @69hex
  boolean checkSD();  // is SD card available?
  boolean checkRAW(); // is RAW partition available?
  boolean checkFAT(); // is FAT partition available?
  uint8_t openTextFileDelimiter(String filename, char delimiter);
  boolean nextTextFileDelimiter(String * result); // false = end
  uint8_t readTextFileDelimiter(String filename, char delimiter, void (*cbReadFile)(String text));
  uint8_t readTextFile(String filename, uint8_t bytes, void (*cbReadFile)(String text));
  uint8_t writeStringFile(String filename, String text, uint8_t option=0x00);
  uint8_t appendStringFile(String filename, String text);
  uint8_t eraseFile(String filename);   // Erase file from Card (FAT) - @65hex 
  uint8_t findFile(String filename);    // List Directory from Card (FAT) - @64hex 
  uint8_t saveScreenFAT(String filename);   // Screen Copy-Save to Card (FAT) - @63hex 
  uint8_t dSaveScreenFAT(String filename, uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy);  // x0, y0 and width and height  
  uint8_t saveScreenFAT(String filename, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);  // x1, y1 x2, y2: same coordinates as rectangle
  uint8_t readScreenFAT(String filename, uint16_t x1=0, uint16_t y1=0); // x1, y1: left-top coordinates
  uint8_t readScreenGCI(String filename, uint16_t x1=0, uint16_t y1=0, uint16_t msb2=0, uint16_t lsb2=0); // x1, y1: left-top coordinates; msb2:lsb2 icon sector address
  uint8_t playSoundSD(String filename, uint8_t option0=0);  // Play Audio WAV file from Card (FAT) - @6Chex     
  uint16_t setColour(uint8_t red, uint8_t green, uint8_t blue);
  void splitColour(uint16_t rgb, uint8_t &red, uint8_t &green, uint8_t &blue);
  uint16_t halfColour(uint16_t rgb);
  uint16_t reverseColour(uint16_t rgb);
  
private:
  ProxySerial * _port;
  
  int8_t _resetPin;
  uint8_t _checkedScreenType;
  uint8_t _checkedControllerType;
  uint8_t _checkedHardwareVersion;
  uint8_t _checkedSoftwareVersion;
  boolean _checkedSD;
  boolean _checkedRAW;
  boolean _checkedFAT;
  uint8_t _font, _fontX, _fontY;
  uint8_t _touch_buffer[4];
  uint8_t _orientation;
  uint16_t _maxX, _maxY;
  uint32_t _fileSize;
  uint8_t _delimeter;
  
  // 16 bits for Picaso, 8 bits for Goldelox
  boolean _XY16;
  void _print16(uint16_t ui);
  void _printXY(uint16_t x, uint16_t y);
  
  void _swap(uint16_t &a, uint16_t &b);
};


#endif
