/*
Library examples for TM1638.

Copyright (C) 2011 Ricardo Batista <rjbatista at gmail dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//#define F_CPU 8000000  // This is used by delay.h library

#include "Arduino.h"

#include <TM1638.h>
//const int strobe = 7;
//const int clock = 9;
//const int data = 8;

int nDryness = 70; // 1 - 100

int nDelay = 300;
int nSense = 0;
int nNumOfChecks = 1;
int nNumOfPumsRun = 0;

const int strobe    = 0;
const int clock     = 1;
const int data      = 2;
const int sensorPin = 3; 
const int pumpPin   = 4; 

unsigned long startTime = 0;


// define a modules
TM1638 modules(data, clock, strobe);

void setup() {
  startTime = millis();
  pinMode( sensorPin, INPUT_PULLUP);
  pinMode( pumpPin, OUTPUT);
  
}

void activatePump( bool onOff) {
  if ( onOff ) nNumOfPumsRun++;
  
  digitalWrite( pumpPin,onOff);
}

void resetLEDs( bool OnOff = false) {
  for ( int i = 0; i < 8; i++) {
    modules.setLEDs( OnOff ? 8 : 0);
  }
}
int getSensor(){
  return map( analogRead(sensorPin) , 0, 1023, 0, 100 );
}



void showDisplay( String strMessage, byte nLed, int nThisDelay = 0) {
    
    modules.setLEDs( nLed);   
    modules.clearDisplay();
    modules.setDisplayToString(strMessage);
    delay(nThisDelay);
}


byte doSleepOnInterupt( int nThisDelay ) {

    byte buttons = 0;
    int nDelayPart = nThisDelay / 100;
        
    modules.setLEDs( B10000000);
    for ( int i = 0; i < 3; i++) {
      modules.clearDisplay(); 
      resetLEDs();
   
      delay(20);   
      modules.setDisplayToString("SLEEP....");
      modules.setLEDs( 0xFF);
      delay(20);
    }
    delay(nDelay);
    modules.setLEDs( B10000000);
   
    modules.clearDisplay();


    for ( int i = 0; i < nDelay; i++) {
     
      buttons = modules.getButtons();

      if ( buttons != 0) {
        break;
      }

      if ( getSensor() >= nDryness) {
        break;
      }
      
      delay( 100);
    }    
    
    return buttons;
} 

void loop() {

    byte keyPressed = 0;
    
    resetLEDs();

    showDisplay("SYS 1001",  B00000001, nDelay); 
    
    showDisplay("SYS PASS",  B00000001, nDelay); 


    showDisplay("CHE " + String(nNumOfChecks++), B00000010, nDelay);

    showDisplay("PUMP " + String(nNumOfPumsRun), B00000010, nDelay);
    
    nSense = getSensor();
    showDisplay("SENS " + String(nSense),  B00000100, nDelay);
    

    // Check for pump activity
    if ( nSense >= nDryness) {
      activatePump( true);
      
      showDisplay("PUMP ON", B0001000, nDelay);
      activatePump(false);
    }
    else {
      showDisplay("PUMP OFF", B0001000, nDelay);
    }

    // We can decide what action to take based on the key
    keyPressed = doSleepOnInterupt( nDelay * 10);

}

