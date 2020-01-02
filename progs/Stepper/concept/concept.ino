
 
int enablePin = 8;
int inA1Pin   = 11;
int inA2Pin   = 10;

int inB1Pin   = 9;
int inB2Pin   = 8;

int n=0;
float fAngel = 0;

#define LEFT_DIR  true
#define RIGHT_DIR false



void setup()
{
  pinMode(inA1Pin, OUTPUT);
  pinMode(inA2Pin, OUTPUT);

  pinMode(inB1Pin, OUTPUT);
  pinMode(inB2Pin, OUTPUT);
  
  pinMode(enablePin, OUTPUT);

  Serial.begin(9600);
  Serial.println("starting");
  
  setMotor(LOW, LOW, LOW ,LOW);
  digitalWrite(enablePin, HIGH);
  delay(1000);
}
 
void loop()
{
  //delay(9999999);
  /*
  if ( n  >= 48 ) {
    digitalWrite(enablePin, LOW);   
    delay(1000);
    n=fAngel=0;
    digitalWrite(enablePin, HIGH);   
  }
  */
  for ( int i = 0; i < 240; i++)
    step(LEFT_DIR);

  delay(100);
  
  for ( int i = 0; i < 240; i++)
    step(RIGHT_DIR);
  delay(100);
  //Serial.println(fAngel);
}

void step( bool direction) {
  static int step = 0;

  if ( direction) step--; else step++;
  if ( step > 4 )  step = 1;
  if ( step <= 0 ) step = 4;
    
  //Serial.println(step);
  switch ( step ) {
    case 1 : setMotor( LOW, HIGH, HIGH ,LOW ); break;
    case 2 : setMotor( LOW, HIGH, LOW  ,HIGH); break;
    case 3 : setMotor( HIGH,LOW,  LOW  ,HIGH); break;
    case 4 : setMotor( HIGH,LOW,  HIGH ,LOW ); break;
  }
  
}

void setMotor( boolean a1,boolean a2,boolean b1,boolean b2)
{
  digitalWrite(inA1Pin, b1);
  digitalWrite(inA2Pin, b2);
  digitalWrite(inB1Pin, a1);
  digitalWrite(inB2Pin, a2); 
  delay(10);
}
