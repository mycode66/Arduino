#include <Stepper.h>

#define SP_A1 8
#define SP_A2 9
#define SP_A3 10
#define SP_A4 11

// Stepper 28BYJ-48 spec.
#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)
 
Stepper stepper(STEPS, SP_A1, SP_A2, SP_A3, SP_A4);

int st = 2003;
int sp = 5; // < --- Do no exceed more than 5

 
void setup() {
  // nothing to do
  stepper.setSpeed(sp);
}


void loop() {
  //return;
  stepper.step(st); // do 2038 steps -- corresponds to one revolution in one minute
  delay(10); // wait for one second
  
  stepper.step(-st); // do 2038 steps in the other direction with faster speed -- corresponds to one revolution in 10 seconds
}
