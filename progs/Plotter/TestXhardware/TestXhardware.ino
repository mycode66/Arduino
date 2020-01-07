// https://github.com/svenhb/GRBL-Plotter

#include <Stepper.h>

// Stepper
#define SP_A1 8
#define SP_A2 9
#define SP_A3 10
#define SP_A4 11

// Stepper 28BYJ-48 spec.
#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)
 
Stepper stepper(STEPS, SP_A1, SP_A2, SP_A3, SP_A4);

int st = 2003;
int sp = 5; // < --- Do no exceed more than 5

//---- Joystick -----------
int xPin = A1;
int yPin = A0;
int buttonPin = 2;

int xPosition = 0;
int yPosition = 0;
int buttonState = 0;

int x,y,b;
int i = 0;
int scale = 50; // this gives us from -10 to 10
int center = ( 1024 /2 ) / scale;
//-------------------------------------------------


void setup() {
    Serial.begin(9600); 
    delay(1000);  

    stepper.setSpeed(sp);
    Serial.println("Ready ... ");
      
}

void loop() {
  i++;
  xPosition = analogRead(xPin) /scale - center;
  yPosition = analogRead(yPin) /scale - center;
  buttonState = digitalRead(buttonPin) /scale;
  
  
  if ( x != xPosition ||  y != yPosition || b != buttonState )
  {
     Serial.print(String(i) + '\t');
     Serial.print("X: ");
     Serial.print(xPosition);
     Serial.print(" | Y: ");
     Serial.print(yPosition);
     Serial.print(" | Button: ");
     Serial.println(buttonState);
  }

  x = xPosition ;
  y = yPosition ;
  b = buttonState ;  

  if ( x != 0 ) {
    Serial.print("Stepping "); Serial.println(x);
    stepper.step(x);
  }
  
  delay(100); // add some delay between reads   
  //stepper.step(st);
    
  
        
}
