///
/// @file 	menu_main.pde
/// @brief	Example
/// @details 	
/// @n @a 	Example for Serial_LCD Library Suite
/// @n @a	for 4D Systems uLCD-uLED-uVGA Serial_LCD Library Suite
/// @n 		on Arduino 0023 and 1.0, chipKIT MPIDE 0023, Wiring 1.0
///
/// @a 		Developed with [embedXcode](http://embedXcode.weebly.com)
/// 
/// @author 	Rei VILO
/// @author 	http://embeddedcomputing.weebly.com
/// @date	Jul 12, 2012
/// @version	release 132
/// @n
/// @copyright 	© Rei VILO, 2010-2012
/// @copyright 	CC = BY NC SA
/// @n		http://embeddedcomputing.weebly.com/serial-lcd.html
/// @n		http://github.com/rei-vilo/Serial_LCD
///
/// @see 	4D Systems Goldelox and Picaso SGC Command Set
/// @n		http://www.4dsystems.com.au/
///

// Core library
#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega2560__) // Arduino specific
#include "WProgram.h" // — for Arduino 0023
// #include  "Arduino.h" // — for Arduino 1.0
#elif defined(__32MX320F128H__) || defined(__32MX795F512L__) // chipKIT specific 
#include "WProgram.h"
#elif defined(__AVR_ATmega644P__) // Wiring specific
#include "Wiring.h"
#elif defined(__MSP430G2452__) || defined(__MSP430G2553__) || defined(__MSP430G2231__) // LaunchPad specific
#include "Energia.h"
#endif

// Include application, user and local libraries
#include "Wire.h"
#include "proxySerial.h"
#include "Serial_LCD.h"
#include "GUI.h"

// test release
#if GUI_RELEASE < 114
#error required GUI_RELEASE 114
#endif

// uncomment for I2C serial interface
//#define __I2C_Serial__

// === Serial port choice ===
#if defined(__I2C_Serial__) // I2C serial
  #include "Wire.h"
  #include "I2C_Serial.h"
  I2C_Serial mySerial(0);

#elif defined (__AVR_ATmega328P__) // software serial
  #if defined(ARDUINO) && (ARDUINO>=100) // for Arduino 1.0
    #include "SoftwareSerial.h"
    SoftwareSerial mySerial(2, 3);
  #else
    #include "NewSoftSerial.h" // for Arduino 23
    NewSoftSerial mySerial(2, 3);
  #endif

#elif defined(__32MX320F128H__) || defined(__32MX795F512L__) || defined (__AVR_ATmega2560__) || defined(__AVR_ATmega644P__) // hardware serial Serial1
  #define mySerial Serial1

#else // error
  #error Platform not defined
#endif
// === End of Serial port choice ===

// Define variables and constants
ProxySerial myPort(&mySerial); // hardware abstraction layer
Serial_LCD myLCD(&myPort); // LCD
uint16_t x, y;
uint32_t l;
button b1, b3;
uint16_t result=0;
uint16_t ui=255;
uint16_t option=0;


// menu declaration and size
item myMenuItems[] = { 
  {     
    0x0000, "Menu 0"          }  
  ,    
  {     
    0x1000, "Item 1"          }  
  ,
  {     
    0x1100, "Item 11"         }  
  ,
  {     
    0x1200, "Item 12"         }  
  ,
  {     
    0x2000, "Item 2"          }  
  ,
  {     
    0x2100, "Item 21"         }  
  ,
  {     
    0x2110, "Item 211"        }  
  ,
  {     
    0x2120, "Item 212"        }  
  ,
  {     
    0x2121, "Item 2121"       }  
  ,
  {     
    0x2122, "Item 2122"       }  
  ,
  {     
    0x2200, "Item 22"         }  
  ,
  {     
    0x2300, "Item 23"         }  
  ,
  {     
    0x3000, "Item 3"          } 
};

uint8_t nItems = sizeof(myMenuItems) / sizeof(myMenuItems[0]);
uint32_t sizeRAW;

// Add setup code 
void setup() {
  Serial.begin(9600);
  Serial.print("\n\n\n***\n");

  // === Serial port initialisation ===
#if defined(__I2C_Serial__)
  Serial.print("i2c Serial\n");
  Wire.begin();

#elif defined(__AVR_ATmega328P__) 
  Serial.print("Software Serial\n");

#elif defined(__32MX320F128H__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega644P__)
  Serial.print("Hardware Serial\n");

#endif 
  // === End of Serial port initialisation ===
  mySerial.begin(9600);

  myLCD.begin(4);  // 9600 at start-up

  // === Serial port speed change ===
  if (false) {
    myLCD.setSpeed(38400);
    mySerial.begin(38400);
  }
  // === End of Serial port speed change ===


  myLCD.setOrientation(0x03);

  myLCD.initSD();

  myLCD.setPenSolid(true);
  myLCD.setFontSolid(true);    
  myLCD.setFont(0);
  myLCD.gText( 0, 210, myLCD.WhoAmI());

  myLCD.setTouch(true);

  myLCD.setFont(1);
  myLCD.gText(0,  0, "         1         2         3         4");
  myLCD.gText(0, 20, "1234567890123456789012345678901234567890"); 
  myLCD.gText(0, 60, ftoa(myLCD.fontX(), 0, 8)); 

  myLCD.setFont(0);
  myLCD.gText(0,  80, "         1         2         3         4         5");
  myLCD.gText(0, 100, "12345678901234567890123456789012345678901234567890123"); 
  myLCD.gText(0, 120, ftoa(myLCD.fontX(), 0, 8)); 

  b1.dStringDefine(&myLCD, 120, 160, 60, 40, "Menu",   whiteColour, blueColour);
  b3.dStringDefine(&myLCD, 240, 160, 60, 40, "Stop",   whiteColour, redColour);
  b1.enable(true);
  b3.enable(true);
  b1.draw();
  b3.draw();

  dLabel(&myLCD, 120, 120, 60, 40, htoa(result), blueColour,  blackColour, 0, 2, 2);
}

uint8_t c;
boolean b=true;


// Add loop code 
void loop() {

  if ( myLCD.getTouchActivity() ) {
    myLCD.getTouchXY(x, y);
    myLCD.setFont(0);
    myLCD.gText(200, 0,  ftoa(x, 0, 5), greenColour); 
    myLCD.gText(200, 15, ftoa(y, 0, 5), redColour); 

    // menu
    if (b1.check()) {
      result = menu(&myLCD, myMenuItems, nItems, whiteColour, blueColour, myLCD.halfColour(blueColour));
      dLabel(&myLCD, 120, 120, 60, 40, htoa(result), blueColour, blackColour, 0, 2, 2);
      Serial.print("\n menu > \t");
      Serial.print(result, HEX);
    }
    // quit
    else if (b3.check()) {
      myLCD.off();
      Serial.print("\n END");
      while(true);
    }
  }

  myLCD.setFont(0);
  myLCD.setFontSolid(true);
  myLCD.gText( 250, 225, ftoa(millis()-l, 0, 6));
  l=millis();

}




