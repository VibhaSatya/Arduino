#include<Servo.h>
Servo servo1;
Servo servo2;
int i=0,j=0;
int done=0;
void setup() {
  servo1.attach(13);
  Serial.begin(9600);
  servo1.write(0);
}


void loop() {
  for(j=0;j<120;j++)
{
   servo1.write(j);
   delay(20);
 }
delay(2000);
}
