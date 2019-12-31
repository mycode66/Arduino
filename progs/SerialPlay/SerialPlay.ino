#include <Stepper.h>

#define SP_A1 8
#define SP_A2 10
#define SP_A3 9
#define SP_A4 11

// Stepper 28BYJ-48 spec.
#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)
 
Stepper stepper(STEPS, SP_A1, SP_A2, SP_A3, SP_A4);

int st = 2003;
int sp = 5; // < --- Do no exceed more than 5

String input;


void setup() {
    Serial.begin(9600); 
    delay(2000);  

    stepper.setSpeed(sp);
    Serial.println("Ready ... ");
}

void loop() {
    if(Serial.available()){
        input = Serial.readStringUntil('\n');
 
        //Serial.println("Doing "+ input );  

        st = atoi(input.c_str());

        
        Serial.println("Doing "+ String(st) );  
        stepper.step(st);
    }
    delay(200);
        
}
