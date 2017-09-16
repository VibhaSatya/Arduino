#include<Servo.h>
Servo servo1;
Servo servo2;
int i=0,j=0;
int done=0;
void setup() {
  
  servo1.attach(2);
}


void loop() {
  
   servo1.write(20);
/*  for(j=25;j<43;j++)
{
   servo1.write(j);
   delay(30);
 }

   (j=43;j>25;j--)
{
   servo1.write(j);
   delay(30);
 }
 */

}
