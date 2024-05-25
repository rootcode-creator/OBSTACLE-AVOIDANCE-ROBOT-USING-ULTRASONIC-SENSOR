#include <servo.h>
#include <NewPing.h> 
int echoPinRight = 6;         // PIN 6 TO RECEIVE ECHO FROM RIGHT SENSOR
int trigerPinRight = 7;       // PIN 7 TO TRIGER THE RIGHT SENSOR
int echoPinMiddle = 8;        // PIN 8 TO RECEIVE ECHO FROM MIDDLE SENSOR
int trigerPinMiddle = 9;      // PIN 9 TO TRIGER THE MIDDLE SENSOR
int echoPinLeft = 13;         // PIN 13 TO RECEIVE ECHO FROM LEFT SENSOR
int trigerPinLeft = 10;       // PIN 10 TO TRIGER THE LEFT SENSOR
int motorA1 = 2;              // PIN 2 FOR CONTROLLING MOTOR A1
int motorA2 = 3;              // PIN 3 FOR CONTROLLING MOTOR A2
int motorB1 = 4;              // PIN 4 FOR CONTROLLING MOTOR B1
int motorB2 = 5;              // PIN 4 FOR CONTROLLING MOTOR B1
const int motorSpeed = 12;          // ARDUINO PWM PIN 11 TO CONTROL MOTORS SPEED
double echoValueright, echoValuemiddle, echoValueleft;  
// INITIALIZING VARIABLE TO RECEIVE ECHO FROM THE SENSORS
float cmRight, cmMiddle, cmLeft; 
Servo myservo;                          
 // INITIALIZING VARIABLES TO STORE DISTANCE MEASURED OF SENSORS IN CENTIMETERS
void setup()
{
  Serial.begin(9600);                                     // STARTING SERIAL COMMUNICATION TO PRINT VALUES RECEIVED BY SENSOR ON SERIAL MONITER
  myservo.attach(12); 
  pinMode(echoPinLeft, INPUT);                           // SETTING ARDUINO PIN AS INPUT
  pinMode(trigerPinLeft, OUTPUT);                       // SETTING ARDUINO PIN AS OUTPUT
  pinMode(echoPinMiddle, INPUT);                        // SETTING ARDUINO PIN AS INPUT
  pinMode(trigerPinMiddle, OUTPUT);                    // SETTING ARDUINO PIN AS OUTPU
  pinMode(echoPinRight, INPUT);                        // SETTING ARDUINO PIN AS INPUT
  pinMode(trigerPinRight, OUTPUT);                     // SETTING ARDUINO PIN AS OUTPU
  pinMode(motorSpeed, OUTPUT);          // SETTING ARDUINO PIN AS OUTPUT TO CONTROL MOTOR SPEED
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
    
  }
void loop()
{
  float cmR, cmM, cmL;                                      // INITIALIZING VARIABLES TO STORE DISTANCE OBTAINED FROM SENSORS IN CM
  int maxRange = 40;                                        // SETTING MAX RANGE 
  //analogWrite(motorSpeed, 50);                              // SETTING MOTORS SPEED YOU CAN SET SPEED BETWEEN 0-255
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);

   
  cmR = sensorRight();
  cmM = sensorMiddle();
  cmL = sensorLeft();
   Serial.println();
   Serial.println("Distance from the object to each sensor");
  Serial.println();
  Serial.print(cmL);
  Serial.print("        ");
  Serial.print(cmM);
  Serial.print("        ");
  Serial.print(cmR);
   if ((cmM > maxRange) )
  {
    digitalWrite(motorA1,HIGH);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, HIGH);
    Serial.println();
    Serial.println("MOVE FORWARD");
  }
  if ((cmR < maxRange) && (cmL > maxRange) && (cmM < maxRange) )
  {
    digitalWrite(motorA1,LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    Serial.println();
    Serial.println("MOVE LEFT");
  }
  else if ((cmR > maxRange) && (cmL < maxRange) && (cmM < maxRange) )
  {
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
     Serial.println();
Serial.println("MOVE RIGHT");
  }
    else if ((cmR < maxRange) && (cmL < maxRange) && (cmM < maxRange) )
  { 
  if (cmR>cmL && cmR>cmM)
  {
      digitalWrite(motorA1, HIGH);
      digitalWrite(motorA2, LOW);
      digitalWrite(motorB1, LOW);
      digitalWrite(motorB2, HIGH);
       Serial.println();
Serial.println("MOVE RIGHT");
    }
   else if (cmR<cmL && cmL>cmM)
  {
      digitalWrite(motorA1, LOW);
      digitalWrite(motorA2, HIGH);
      digitalWrite(motorB1, HIGH);
      digitalWrite(motorB2, LOW);
       Serial.println();
    Serial.println("MOVE LEFT");
    }
    else if(cmM>cmR && cmM>cmL)
    {
      digitalWrite(motorA1, HIGH);
      digitalWrite(motorA2, HIGH);
      digitalWrite(motorB1, HIGH);
      digitalWrite(motorB2, HIGH);
       Serial.println();
    Serial.println("MOVE FORWARD");
    }
    else if (cmM == cmR == cmL )
     {
      digitalWrite(motorA1, LOW);
      digitalWrite(motorA2, LOW);
      digitalWrite(motorB1, LOW);
      digitalWrite(motorB2, LOW);
       Serial.println();
    Serial.println("STOP");
    }
    }
     else if ((cmR > maxRange) && (cmL > maxRange) && (cmM < maxRange) )
  { 
     if (cmL > cmR)
    {
      digitalWrite(motorA1, LOW);
      digitalWrite(motorA2, HIGH);
      digitalWrite(motorB1, HIGH);
      digitalWrite(motorB2, LOW);
      Serial.println();
Serial.println("MOVE LEFT");
    }
    else if (cmR > cmL)
    {
      digitalWrite(motorA1, HIGH);
      digitalWrite(motorA2, LOW);
      digitalWrite(motorB1, LOW);
      digitalWrite(motorB2, HIGH);
            Serial.println();
Serial.println("MOVE RIGHT");
    }
    }
  delay(2000);
}
float sensorRight()               // FUUNCTION TO OPERATE RIGHT SENSOR
{
  digitalWrite(trigerPinRight, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerPinRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerPinRight, LOW);
  echoValueright = pulseIn(echoPinRight, HIGH);
  cmRight = echoValueright / 650;
  //inchesRight=cmRight/2.54;
  //Serial.print(cmRight);
  return (cmRight);
}
float sensorMiddle()              // FUNCTION TO OPERATE MIDDLE SENSOR
{
  digitalWrite(trigerPinMiddle, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerPinMiddle, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerPinMiddle, LOW);
  echoValuemiddle = pulseIn(echoPinMiddle, HIGH);
  cmMiddle = echoValuemiddle / 650;

  //inchesMiddle=cmMiddle/2.54;
  //Serial.print(cmMiddle);
  return (cmMiddle);
}
float sensorLeft()              // FUNCTION TO OPERATE LETT SENSOR
{
  digitalWrite(trigerPinLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerPinLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerPinLeft, LOW);
  echoValueleft = pulseIn(echoPinLeft, HIGH);
  cmLeft = echoValueleft / 650;
  //inchesLeft=cmLeft/2.54;
  //Serial.print(cmLeft);
  return (cmLeft);
}
