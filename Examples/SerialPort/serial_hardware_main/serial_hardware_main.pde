///
/// @file 	serial_hardware.pde
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
#include "Serial_LCD.h"
#include "proxySerial.h"
#include "GUI.h"


// test release
#if GUI_RELEASE < 114
#error required GUI_RELEASE 114
#endif


// --- HardwareSerial Case - Arduino + chipKIT
  #define mySerial Serial1
ProxySerial myPort(&mySerial);
Serial_LCD myLCD(&myPort); 
button b7;

uint16_t x, y;
uint32_t l;

void setup() {
  Serial.begin(19200);
  Serial.print("\n\n\n***\n");

  // --- HardwareSerial Case - Arduino + chipKIT
  mySerial.begin(9600);
  Serial.print("HardwareSerial 9600 \n");

  myLCD.begin(4); // Arduino pin 4 connected to screen RESET

  delay(10);
  // === Serial port speed up
  myLCD.setSpeed(38400);
  mySerial.begin(38400);
  Serial.print("Serial 38400 \n");


  myLCD.setOrientation(0x03);
  myLCD.setPenSolid(true);
  myLCD.setFontSolid(true);
  myLCD.setFont(0);
  myLCD.gText( 0, 210, myLCD.WhoAmI());
  myLCD.setTouch(true);
  l=millis();

  b7.define(&myLCD,  0, 0, 79, 59, setItem(1, "Stop"), myLCD.setColour(0xff, 0xff, 0xff), myLCD.setColour(0xff, 0x00, 0x00), myLCD.setColour(0x88, 0x00, 0x00), 9);
  b7.enable(true);
  b7.draw();

  uint16_t chrono0, chrono1;
  chrono0=millis();

  myLCD.setPenSolid(false);
  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      myLCD.circle(120+j*10, 30+i*10, 30, random(0, 0xffff));
    }
  }

  chrono1=millis();
  myLCD.gText( 0, 180, ftoa((chrono1-chrono0), 0, 10 ));

  chrono0=millis();

  myLCD.setPenSolid(true);
  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      myLCD.circle(120+j*10, 30+i*10, 30, random(0, 0xffff));
    }
  }

  chrono1=millis();
  myLCD.gText( 160, 180, ftoa((chrono1-chrono0), 0, 10 ));

}

uint8_t c;

void loop() {

  c=myLCD.getTouchActivity();
  Serial.print(". ");

  if (c>0) {
    Serial.print("getTouchActivity ");
    myLCD.getTouchXY(x, y);
    Serial.print("getTouchXY ");
    myLCD.setFont(0);
    Serial.print("setFont ");
    myLCD.gText(200, 0, ftoa(x, 0, 5)); 
    Serial.print("gText x ");
    myLCD.gText(200, 15, ftoa(y, 0, 5)); 
    Serial.print("gText y ");

    // quit
    if (b7.check()) {
      Serial.print("QUIT ");
      myLCD.off();
      while(true);
    }
    Serial.print("\n");
  }
  myLCD.setFont(0);
  myLCD.setFontSolid(true);
  myLCD.gText( 250, 225, ftoa(millis()-l, 0, 6));
  l=millis();
}





















