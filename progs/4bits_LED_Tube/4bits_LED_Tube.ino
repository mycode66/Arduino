

short rclk = 4;
//Pin connected to SH_CP of 74HC595 AKA SCLK
short sclk = 6;
//Pin connected to DS of 74HC595 AKA DIO
short dio = 3;

/*
 *
    This is the driver functions for writing to the Bangood 4 Bit 7 segment display.
    The module has two 74HC595 shift registers on the back.
 *
 * Written by Christopher Hamer Thursday 14th April 2016.
 * Website: monotok.org
 * Released into public domain
 *
 
Below is the segment drawn out to show which letters correspond to which bit in the schematic diagram.    
    
    --a---
    f-   -b
    --g---
    e-   -c
    ---d-- - DP
 
The first byte sent to the register is segment 'A' at the right hand side and segment 'DP' at the
left most side. For example this byte will be sent to display 'C'. The zero's are on and the 1's are
off. This is because the display is a common anode display (CAD).
 
    C = 0b11000110
 
There are two 74HC595 shift registers so we need to send 16 bits (two bytes) to the chip. This second register controls which display unit to show the previous byte. This is not inverted so '1' is now on and '0' is
now off. The four left most bits do not matter, these are not connected to anything. This can be seen in the
schematic diagram. These pins are: QH, QF, QG and QE. The right hand most 4 bits are the DIG0, DIG1, DIG2 and DIG3. These control which display unit displays the previous 8 bits.
 
For example:
 
0b11111001 will turn on the first (right most) and last (left most) display unit. So it will be "C OFF OFF C".
To display just one C on the right then it will be:
0b11110001
    
*/
#ifndef Morse_h
#define Morse_h
 
#include "Arduino.h"
 
class FourBitDisplay
{
    public:
        FourBitDisplay(short rclk, short sclk, short dio);
        byte getBits(char val);
        void printToDisplay(char* value, short arraySize ,char *justify);
    private:
        short _rclkPin;
        short _sclkPin;
        short _dioPin;
};
 
#endif


FourBitDisplay::FourBitDisplay(short rclk, short sclk, short dio)
{
pinMode( rclk, OUTPUT );
_rclkPin = rclk;
pinMode( sclk, OUTPUT );
_sclkPin = sclk;
pinMode( dio, OUTPUT );
_dioPin = dio;
}
byte FourBitDisplay::getBits(char val)
{
/*
This is slightly quicker by a few microseconds than a switch statement.
This is an ASCII lookup table. The reason it includes all off statements before
the 0 is because it allows me to turn off any rubbish that gets printed to the display.
Adding any more items to the lookup table does not hamper performance.
*/
    
    
const static byte bits[] = 
    {
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b10111111, //-
        0b11111111, //off
        0b11111111, //off
        0b11000000, //0
        0b11111001, //1
        0b10100100, //2
        0b10110000, //3
        0b10011001, //4
        0b10010010, //5
        0b10000010, //6
        0b11111000, //7
        0b10000000, //8
        0b10010000, //9
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b11111111, //off
        0b10001000, //A
        0b10000011, //B
        0b11000110, //C
        0b10100001, //D
        0b10000110, //E
        0b10001110 //F
    };
    
  return bits[val];
}
void FourBitDisplay::printToDisplay(char* value, short arraySize ,char *justify)
{
    shiftOut(_dioPin, _sclkPin, MSBFIRST, 0b11111111); //Clear the display
    if(*justify == 'r')
    {
        size_t len = strlen(value);
        char *t = value + len-1;
        char reversed[arraySize];
        short num = 0;
        
        while(t >= value)
        {
          reversed[num] = *t;
          t = t - 1;
          num++;
        }
        
        const char *digitalPins = "1248";
        for(unsigned short s = 0; s <arraySize; s++)
        {
          digitalWrite(_rclkPin, LOW);
          // shift out the bits:
          
          if(reversed[s] == '.')
          {
                byte byteWithDot = (getBits(reversed[s+1]) & 0b01111111);
                shiftOut(_dioPin, _sclkPin, MSBFIRST, byteWithDot);
                
                for(unsigned short f = s+1; f <= arraySize; f++)
                {
                    reversed[f] = reversed[f+1];
                }
          }
          else
          {
                shiftOut(_dioPin, _sclkPin, MSBFIRST, getBits(reversed[s]));
          }
      
          shiftOut(_dioPin, _sclkPin, MSBFIRST, digitalPins[s]);
      
          //take the latch pin high so the LEDs will light up:
    
          digitalWrite(_rclkPin, HIGH);
        }
    }
    else
    {
        const char *digitalPins = "8421";
        for(unsigned short s = 0; s <arraySize; s++)
        {
          digitalWrite(_rclkPin, LOW);
          // shift out the bits:
          
          if(value[s+1] == '.')
          {
                byte byteWithDot = (getBits(value[s]) & 0b01111111);
                shiftOut(_dioPin, _sclkPin, MSBFIRST, byteWithDot);
                
                for(unsigned short f = s+1; f <= arraySize; f++)
                {
                    value[f] = value[f+1];
                }
          }
          else
          {
                shiftOut(_dioPin, _sclkPin, MSBFIRST, getBits(value[s]));
          }
          shiftOut(_dioPin, _sclkPin, MSBFIRST, digitalPins[s]);
      
          //take the latch pin high so the LEDs will light up:
          digitalWrite(_rclkPin, HIGH);
      }
    }
}

#include <string.h>
 
FourBitDisplay fbd(4,6,3);
 
int moistLevel = 0; //Global var
int timer1_counter;
 
void getMoistLevel();
 
 
void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
 
    // initialize timer1
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
 
  // Set timer1_counter to the correct value for our interrupt interval
  //timer1_counter = 64911;   // preload timer 65536-16MHz/256/100Hz
  //timer1_counter = 64286;   // preload timer 65536-16MHz/256/50Hz
  timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz
 
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}


ISR(TIMER1_OVF_vect)        // interrupt service routine
{
  TCNT1 = timer1_counter;   // preload timer
  getMoistLevel();
}
 
 
void getMoistLevel()
{
    moistLevel++;
}
 
void loop()
{
  char buf[4];
  sprintf(buf, "%d", moistLevel);
 
  char *val = buf;
  char *just = "r";
  short arraySize = strlen(val);
  
  fbd.printToDisplay(val,arraySize,just);
}

 
