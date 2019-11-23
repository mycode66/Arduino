#include <InvertedTM1638.h>
#include <TM1638.h>
#include <TM16XXFonts.h>
#include <TM1638QYF.h>
#include <TM1640.h>
#include <TM16XX.h>

    /*     Arduino Color Sensing Tutorial
     *      
     *  by Dejan Nedelkovski, www.HowToMechatronics.com
     *  
     */

  
    const int STROBE    = 10;
    const int CLOCK     = 11;
    const int DATA      = 12;

     
    #define S0 4
    #define S1 5
    #define S2 6
    #define S3 7
    #define POWER 13
    #define sensorOut 8
    int frequency = 0;
    int color=0;
    char strBuffer[256];

    // define a modules
    TM1638 modules(DATA, CLOCK, STROBE);

     void showDisplay( String strMessage, byte nLed, int nThisDelay = 0) {
        
        modules.setLEDs( nLed);   
        modules.clearDisplay();
        modules.setDisplayToString(strMessage);
        delay(nThisDelay);
    }

  
    void setup() {
      pinMode(S0, OUTPUT);
      pinMode(S1, OUTPUT);
      pinMode(S2, OUTPUT);
      pinMode(S3, OUTPUT);

      pinMode(DATA, OUTPUT);
      pinMode(CLOCK, OUTPUT);
      pinMode(STROBE, OUTPUT);
      
      pinMode(POWER, OUTPUT);
      pinMode(sensorOut, INPUT);
      
      // Setting frequency-scaling to 20%
      digitalWrite(S0,HIGH);
      digitalWrite(S1,HIGH);

      digitalWrite(POWER,LOW);
      
      Serial.begin(9600);
    }



 // Custom Function - readColor()
int readColor() {

    color = 0;
    // Setting red filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    int R = frequency;
    // Printing the value on the serial monitor
    //Serial.print("R= ");//printing name
    //Serial.print(frequency);//printing RED color frequency
    //Serial.print("  ");
    delay(50);
    // Setting Green filtered photodiodes to be read
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    int G = frequency;
    // Printing the value on the serial monitor
    //Serial.print("G= ");//printing name
    //Serial.print(frequency);//printing RED color frequency
    //Serial.print("  ");
    delay(50);
    // Setting Blue filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    int B = frequency;

    sprintf(strBuffer, "R=%d G=%d B=%d\n", R,G,B);
    //Printing the value on the serial monitor
    //Serial.print("B= ");//printing name
    //Serial.print(frequency);//printing RED color frequency
    //Serial.println(strBuffer);
    delay(50);


    if ( R < 15 & G < 15 & B < 15 ){
      color = 6; // White 
    }
    else if ( R < 100 & G < 80 & B < 100 ){
      color = 4; // Yellow 
    }
    else if(R<80 & R>32 ){
      color = 1; // Red
    }
    else if(B<80 & B>32 ){
      color = 5; // Blue
    }
    else if (G<90 & G>32){
      color = 3; // Green
    }
    return color;  
}

    int xxx = 0;
    void loop(){

      int c = 0;
      char s[8][10] = {"no Idea","rED","Orang","grEEN","yELLOW","BLUE","WHItE","Pink"};
      
      //c = readColor();
      showDisplay( s[c], xxx++ );

      Serial.println( s[c]);
      delay(100);
    }
