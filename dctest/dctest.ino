/*#include<Servo.h>
Servo servo1;

int j=0;

void setup() {
  
  servo1.attach(4);
}


void loop() {
  for(j=0;j<100;j++)
{
   servo1.write(j);
   delay(30);
 }

}*/


//const int mot3 = 12 ,mot4 = 9 ,enable2 = 3 ; //pen motor1
const int mot3 = 13 ,mot4 = 8 ,enable2 = 11 ; //pen motor2

//const int mot3 =4,mot4 =5,enable2 =6;
int count=0;

void setup() {
  pinMode(mot3,OUTPUT);
  pinMode(mot4,OUTPUT);
  pinMode(enable2,OUTPUT);
}


void moveForward(int n)
{
 count=0;
 while(count<=n)
   {
   analogWrite(enable2,200);
   digitalWrite(mot4,HIGH);
   digitalWrite(mot3,LOW);
   delay(10);
   digitalWrite(mot3,HIGH);
   delay(10);
   count++;
   }
   digitalWrite(mot3,LOW);
   digitalWrite(mot4,LOW);
   /*count=0;
   while(count<=100)
   {
   analogWrite(enable2,100);
   digitalWrite(mot3,HIGH);
   digitalWrite(mot4,LOW);
   delay(80);
   digitalWrite(mot3,HIGH);
   delay(30);
   count++;
   }
   digitalWrite(mot3,LOW);
   digitalWrite(mot4,LOW);
   delay(2000);
   count=0;
   */
  
}
void moveBackward(int n)
{
count=0;
   while(count<=n)
   {
   analogWrite(enable2,250);
   digitalWrite(mot3,HIGH);
   digitalWrite(mot4,LOW);
   delay(10);
   digitalWrite(mot3,HIGH);
   delay(10);
   count++;
   }  
   digitalWrite(mot3,LOW);
   digitalWrite(mot4,LOW);

}
void loop() {


 moveForward(500);

}
