// 
// μLCD-32PT(SGC) 3.2” Serial LCD Display Module
// Arduino & chipKIT Library
//
// Example - see README.txt
// © Rei VILO, 2010-2012
// CC = BY NC SA
// http://sites.google.com/site/vilorei/
// http://github.com/rei-vilo/Serial_LCD
//
//
// Based on
// 4D LABS PICASO-SGC Command Set
// Software Interface Specification
// Document Date: 1st March 2011 
// Document Revision: 6.0
// http://www.4d-Labs.com
//
//


#include "Serial_LCD.h"
#include "proxySerial.h"
#include "GUI.h"
#include "Graphics.h"
#include "Wire.h"

// test release
#if GUI_RELEASE < 108
#error required GUI_RELEASE 108
#endif

#if GRAPHICS_RELEASE < 107
#error required GRAPHICS_RELEASE 107
#endif

// === Serial port choice ===
// --- Arduino Uno - software serial
#if defined (__AVR_ATmega328P__) 
#include "SoftwareSerial.h"
SoftwareSerial Serial3(2, 3); // RX, TX

// --- Arduino mega2560 - hardware serial
#elif defined (__AVR_ATmega2560__)
#endif
// === End of Serial port choice ===

ProxySerial myPort(&Serial3);
Serial_LCD myLCD(&myPort); 


uint16_t x, y;
uint32_t l;

button b7;
uint8_t a;
gGauge myGauge;


void setup() {
  Serial.begin(19200);
  Serial.print("\n\n\n***\n");

  // === Serial port initialisation ===
  // --- Arduino Uno - software serial
#if defined (__AVR_ATmega328P__) 
  Serial.print("software\n");
  // --- Arduino mega2560 - hardware serial
#elif defined (__AVR_ATmega2560__)
  Serial.print("hardware\n");
#endif
  // === End of Serial port initialisation ===

  Serial3.begin(9600);
  myLCD.begin(4);

  Serial.print("begin\n");

  // === Serial port speed change ===
  myLCD.setSpeed(38400);
#if defined (__AVR_ATmega328P__) 
  Serial3.begin(38400);
#elif defined (__AVR_ATmega2560__)
  Serial3.begin(38400);
#endif
  // === End of Serial port speed change ===

  myLCD.setOrientation(0x03);
  myLCD.setPenSolid(true);
  myLCD.setFontSolid(true);

  myLCD.setFont(0);
  myLCD.gText( 0, 225, myLCD.WhoAmI());
  myLCD.setTouch(true);

  l=millis();

  b7.dDefine(&myLCD, 0, 0, 70, 40, setItem(0, "Stop"), myLCD.setColour(0xff, 0xff, 0xff), myLCD.setColour(0xff, 0x00, 0x00), myLCD.setColour(0x88, 0x00, 0x00), 9);
  b7.enable(true);
  b7.draw();

  myGauge.define(&myLCD, 169, 120, 60, -2.0, 2.0, 8, 8);
}

uint32_t ll = 0;
uint16_t i = 0;
float v;

void loop() {
  Serial.print(".");
  
  //  // Solution 1
  //  while (millis()-l<100) {
  //    v = cos(i*PI/64.0) + 0.3*cos(i*PI/16.0+PI/8.0);
  //    i++;
  //    i %= 256;
  //  }

  // Solution 2
  v = cos(i*PI/64.0) + 0.3*cos(i*PI/16.0+PI/8.0);
  i++;
  i %= 256;
//  while (millis()-ll<100);

  ll=millis();
  myGauge.draw( v, ftoa(v, 2, 7) );

//  myLCD.setFont(3);
//  myLCD.setFontSolid(true);
//  myLCD.gText( 160, 180, ftoa(v, 2, 10 ));

  if (myLCD.getTouchActivity()>0) {
    myLCD.getTouchXY(x, y);
    myLCD.setFont(0);
    myLCD.gText(200, 0, ftoa(x, 0, 5)); 
    myLCD.gText(200, 15, ftoa(y, 0, 5)); 

    // quit
    if (b7.check()) {
      myLCD.off();
      while(true);
    } // quit
  } // getTouchActivity

  myLCD.setFont(0);
  myLCD.setFontSolid(true);
  myLCD.gText( 250, 225, ttoa(millis()-l, 0, 6));
  l=millis();

  //  delay(100);
}
























