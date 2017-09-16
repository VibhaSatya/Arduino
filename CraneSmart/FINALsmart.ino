#include<Stepper.h>
#include<Servo.h>

const int trigpin= 2;
const int echopin=3;
const int range=30; 

const int mot1=A1,mot2=A2,enable=6,mot3=7,mot4=8,enable2=9;

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
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(enable,OUTPUT);
  pinMode(mot3,OUTPUT);
  pinMode(mot4,OUTPUT);
  pinMode(enable2,OUTPUT);  
 
  stepper.setSpeed(200);
  Serial.begin(9600);
  pinMode(echopin,INPUT);
  pinMode(trigpin,OUTPUT);
  //analogWrite(enable,255);

 
  for(int i=0;i<30;i++)
  getDistance();

}
void check()
{  
  int rotCount=0;
  int d1,d2,d3,d4;
  Serial.print("inside check");
  delay(5000);
   do
   {
   getDistance();
   analogWrite(enable,100);
   analogWrite(mot1,255);
   analogWrite(mot2,0);
   delay(80);
   analogWrite(mot2,255);
   delay(30);
   delay(1000);
   }while(distance!=dist);
  delay(5000);
  Serial.print("EDGE");
  do
   {
   getDistance();
   delay(3000);
   d1=distance;
   analogWrite(enable,100);
   analogWrite(mot1,255);
   analogWrite(mot2,0);
   delay(80);
   analogWrite(mot2,255);
   delay(30);
   delay(3000);

   getDistance();
   delay(3000);
   d2=distance;
   analogWrite(enable,100);
   analogWrite(mot1,255);
   analogWrite(mot2,0);
   delay(80);
   analogWrite(mot2,255);
   delay(30);
   delay(3000);

   getDistance();
   delay(3000);
   d3=distance;
   analogWrite(enable,100);
   analogWrite(mot1,255);
   analogWrite(mot2,0);
   delay(80);
   analogWrite(mot2,255);
   delay(30);
   delay(3000);

   getDistance();
   delay(3000);
   d4=distance;
   analogWrite(enable,100);
   analogWrite(mot1,255);
   analogWrite(mot2,0);
   delay(80);
   analogWrite(mot2,255);
   delay(30);
   delay(3000);
   
   }while(!((d1==d2)&&(d1==d3)&&(d1==d4)));
  Serial.print("outside check");
  delay(5000);
  
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
   analogWrite(mot2,255);
   analogWrite(mot1,0);
   delay(80);
   analogWrite(mot1,255);
   delay(30);
  }
 dist=distance;
 check();
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
   analogWrite(mot1,255);
   analogWrite(mot2,0);
   delay(80);
   analogWrite(mot2,255);
   delay(30);
  }
 } 
 
  analogWrite(mot1,0);
  analogWrite(mot2,0);
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
      delay(dist*210);
      //delay(40); 
     }
     else
     { 
      Serial.print(dist);
      analogWrite(enable2,126);
      digitalWrite(mot3,HIGH);
      digitalWrite(mot4,LOW);
      delay(dist*210);
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
  for(grabCount=0;grabCount<95;grabCount++)
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
  servo1.attach(4);
  servo2.attach(5);
 int i,j;
 Serial.print("Inside Servo\n");
for(i=100,j=0;i>25;i--,j++)
{
   servo1.write(i);
   servo2.write(j);
   delay(30);
 }
servo1.write(i);
servo2.write(j);
}

  
  


void loop() 
{
 if(found==0)
 {  
    rotateArm();
    delay(5000);
    getDistance();
    delay(5000);
    //grabberMove();
    //grabberUpDown();
    //grab();
    found=1;
  }
 else
 {
  if(once==0) 
    {dump=1;
    //grabberUpDown();
    rotateArm();
    //grab();
    //grabberMove();
    once=1;}

}
}
