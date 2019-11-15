    /*     Arduino Color Sensing Tutorial
     *      
     *  by Dejan Nedelkovski, www.HowToMechatronics.com
     *  
     */
     
    #define S0 4
    #define S1 5
    #define S2 6
    #define S3 7
    #define POWER 2
    #define sensorOut 8
    int frequency = 0;
    int color=0;
    char strBuffer[256];
    
    void setup() {
      pinMode(S0, OUTPUT);
      pinMode(S1, OUTPUT);
      pinMode(S2, OUTPUT);
      pinMode(S3, OUTPUT);
      pinMode(POWER, OUTPUT);
      pinMode(sensorOut, INPUT);
      
      // Setting frequency-scaling to 20%
      digitalWrite(S0,HIGH);
      digitalWrite(S1,HIGH);

      digitalWrite(POWER,HIGH);
      
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

    void loop(){
      
      int c = 0;
      char s[8][10] = {"Unknown","Red","Orang","Green","Yellow","Blue","White","Pink"};
      
      c = readColor();

      Serial.println( s[c]);
      delay(1000);
    }

/*
    void loop() {

      digitalWrite(POWER,HIGH);
      
      // Setting red filtered photodiodes to be read
      digitalWrite(S2,LOW);
      digitalWrite(S3,LOW);
      // Reading the output frequency
      frequency = pulseIn(sensorOut, LOW);
      // Printing the value on the serial monitor
      Serial.print("R= ");//printing name
      Serial.print(frequency);//printing RED color frequency
      Serial.print("  ");
      delay(500);
      // Setting Green filtered photodiodes to be read
      digitalWrite(S2,HIGH);
      digitalWrite(S3,HIGH);
      // Reading the output frequency
      frequency = pulseIn(sensorOut, LOW);
      // Printing the value on the serial monitor
      Serial.print("G= ");//printing name
      Serial.print(frequency);//printing RED color frequency
      Serial.print("  ");
      delay(500);
      // Setting Blue filtered photodiodes to be read
      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
      // Reading the output frequency
      frequency = pulseIn(sensorOut, LOW);
      // Printing the value on the serial monitor
      Serial.print("B= ");//printing name
      Serial.print(frequency);//printing RED color frequency
      Serial.println("  ");
      
      digitalWrite(POWER,LOW);
      delay(10000);
    }
 */
