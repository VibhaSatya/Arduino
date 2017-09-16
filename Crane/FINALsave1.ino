#include<Stepper.h>
#include<Servo.h>
const int trigpin= 2;
const int echopin=3;
const int range=60; 

const int mot1=4,mot2=5,enable=6,mot3=7,mot4=8,enable2=9;

const int stepsPerRevolution = 140;
int dist;

int dump=0,dumpCount=0;
long distance=1000;  //Set it greater than range
int found=0,once=0;
int servoAngle;
int grabCount=0;

Stepper stepper(stepsPerRevolution,10,12,11,13);
Servo servo1;
Servo servo2;

void setup() {
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);  
 
  stepper.setSpeed(200);
  Serial.begin(9600);
  pinMode(echopin,INPUT);
  pinMode(trigpin,OUTPUT);
  //analogWrite(enable,255);

 // servo1.attach(7);
  //servo2.attach(8);
  
  for(int i=0;i<30;i++)
  getDistance();

}

void getDistance()
{ 
 distance=0;
 while(distance==0)
 {
 float duration;
 digitalWrite(trigpin,LOW);
 delayMicroseconds(2);
 digitalWrite(trigpin,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigpin,LOW);
 duration=pulseIn(echopin,HIGH);
 distance=duration/29/2;
 Serial.print(distance);
 Serial.println();
 }
}
void rotateArm()
{
 
  if(dump==0)
  {
    Serial.print("RotArm\n");
  while(distance>=range)
  {
   dumpCount++;
   getDistance();
  
   analogWrite(enable,100);
   digitalWrite(mot2,HIGH);
   digitalWrite(mot1,LOW);
   delay(80);
   digitalWrite(mot1,HIGH);
   delay(30);
  }
 dist=distance;
 }
  
  //rotate to dump
 else
 {
  while(dumpCount>0)
  {
   Serial.print(dumpCount);
   Serial.println();
   dumpCount--;
   getDistance();
   analogWrite(enable,100);
   digitalWrite(mot1,HIGH);
   digitalWrite(mot2,LOW);
   delay(80);
   digitalWrite(mot2,HIGH);
   delay(30);
  }
 } 
  digitalWrite(mot1,LOW);
  digitalWrite(mot2,LOW);
  return;
}

void grabberMove()
{    
  if(dump==0)
     {
      Serial.print("GrabMove\n");
      analogWrite(enable2,126);
      digitalWrite(mot4,HIGH);
      digitalWrite(mot3,LOW);
      delay(dist*200);
      //delay(40); 
     }
     else
     { 
      Serial.print(dist);
      analogWrite(enable2,126);
      digitalWrite(mot3,HIGH);
      digitalWrite(mot4,LOW);
      delay(dist*200);
      //delay(40); 
     }
digitalWrite(mot3,LOW);
digitalWrite(mot4,LOW);
     
}
void grabberUpDown()
{
  
 //down
if(dump==0)
{ 
  Serial.print("Up down\n");
  for(grabCount=0;grabCount<100;grabCount++)
  stepper.step(stepsPerRevolution);
}
//up
else
{
  while(--grabCount>0)
  stepper.step(-stepsPerRevolution);
}
      

}

void grab()
{
 int i,j;
 Serial.print("Inside Servo\n");
for(i=100,j=0;i>20;i--,j++)
{
   servo1.write(i);
   servo2.write(j);
   delay(15);
 }

}

  
  


void loop() 
{
 if(found==0)
 {  
    rotateArm();
    grabberMove();
    grabberUpDown();
    //grab();
    found=1;
  }
 else
 {
  if(once==0) 
    {dump=1;grabberUpDown();rotateArm();grabberMove();once=1;}

}
}
