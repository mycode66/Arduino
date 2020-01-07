int xPin = A1;
int yPin = A0;
int buttonPin = 2;

int xPosition = 0;
int yPosition = 0;
int buttonState = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);

  //activate pull-up resistor on the push-button pin
  pinMode(buttonPin, INPUT_PULLUP); 
  
  // For versions prior to Arduino 1.0.1
  // pinMode(buttonPin, INPUT);
  // digitalWrite(buttonPin, HIGH);
  
}

int x,y,b;
int i = 0;
int scale = 50; // this gives us from -10 to 10
int center = ( 1024 /2 ) / scale;

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
  delay(10); // add some delay between reads
}
