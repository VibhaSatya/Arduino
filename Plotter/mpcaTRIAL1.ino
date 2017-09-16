#include<Servo.h>

void moveForward(int n); //rods rotate clockwise by n units
void moveBackward(int n); //rods rotate anticlockwise by n units
void moveUp(int n); //paper moves up by n units
void moveDown(int n); //paper moves down by n units
void penOn(); 
void penOff();



Servo servo;

const int mot1 = 12 ,mot2 = 9 ,enable1 = 3 ; //pen motor1
const int mot3 = 13 ,mot4 = 8 ,enable2 = 11 ; //pen motor2

//const int mot3 =4,mot4 =5,enable2 =6;
  
const int mot5 =4,mot6 =5,enable3 =6; //paper motor


int count=0;
int offsetcount=0;

void setup() {

  
  pinMode(mot1,OUTPUT);
  pinMode(mot2,OUTPUT);
  pinMode(enable1,OUTPUT);

  pinMode(mot3,OUTPUT);
  pinMode(mot4,OUTPUT);
  pinMode(enable2,OUTPUT);

  
  pinMode(mot5,OUTPUT);
  pinMode(mot6,OUTPUT);
  pinMode(enable3,OUTPUT);

 servo.attach(2);
 servo.write(20);
 Serial.begin(9600);
}


void moveForward(int n)
{
 count=0;
 while(count<=n)
   {
 
   digitalWrite(mot4,HIGH);
   digitalWrite(mot3,LOW);
   analogWrite(enable2,220);
  
   digitalWrite(mot2,HIGH);
   digitalWrite(mot1,LOW);
   analogWrite(enable1,200);
   
   delay(1000);  //moves forward
   
   digitalWrite(mot3,HIGH);
   digitalWrite(mot1,HIGH);
   delay(2000);
   count++;
   }
    

}



void offset(int n)
{
 count=0;
 while(count<=n)
   {
   analogWrite(enable2,250);
   digitalWrite(mot4,HIGH);
   digitalWrite(mot3,LOW);
   delay(10);
   digitalWrite(mot3,HIGH);
   delay(10);
   count++;
   }
}

void moveBackward(int n)
{
   count=0;
 while(count<=n)
   {
 
   digitalWrite(mot3,HIGH);
   digitalWrite(mot4,LOW);
   analogWrite(enable2,230);
  
   digitalWrite(mot1,HIGH);
   digitalWrite(mot2,LOW);
   analogWrite(enable1,200);
   
   delay(1000);
   
   digitalWrite(mot4,HIGH);
   digitalWrite(mot2,HIGH);
   delay(2000);
   count+=2;
  offset(offsetcount);
   }

}

void moveUp(int n)
{

  count=0;
 while(count<=2*n)
   {
   analogWrite(enable3,200);
   digitalWrite(mot5,HIGH);
   digitalWrite(mot6,LOW);
   delay(20);
   digitalWrite(mot6,HIGH);
   delay(20);
   count+=2;
   Serial.println(count);
   }

 }
  



void moveDown(int n)

{
   count=0;
 while(count<=2*n)
   {
   analogWrite(enable3,200);
   digitalWrite(mot6,HIGH);
   digitalWrite(mot5,LOW);
   delay(20);
   digitalWrite(mot5,HIGH);
   delay(20);
   count+=2;
   }
 
}


  /*
 while(count<=n)
   {
   analogWrite(enable3,200);
   digitalWrite(mot5,HIGH);
   digitalWrite(mot6,LOW);
   delay(80);
   digitalWrite(mot5,HIGH);
   delay(30);
   count++;
   }
   */
   
 

void penOn()
{
  int j;
   for(j=25;j<43;j++)
{
   servo.write(j);
   delay(30);
 }

 
}

void penOff()
{
  int j;
for(j=43;j>25;j--)
{
   servo.write(j);
   delay(30);
 }
}



void plotsin(){
  
  float x,y, val;
  int curr_y;
  float oldx=0;
  float oldy = 0;
  float movebyx, movebyy;
int j;

  
  for(x=0;x<=360;x+=10.0) {
    
    //servo moves pen away from paper
 
    
    //move dc motor x1,x2 by x - oldx;
    movebyx = (x-oldx)/10; 
    moveBackward(((int)movebyx));
    oldx = x;
    //x is now ready
  
    val = PI/180;
    y = sin(x*val);
    if(y < 0){
        y = y*(-1);
    }
    
    //move dc motor y by y-oldy
    movebyy = y-oldy;
    curr_y = ((int)(movebyy *100));
    Serial.println(curr_y);

    if(x <= 90){
      if(curr_y < 0){
        curr_y = curr_y*(-1);
        offsetcount=10;
      }
      moveUp(curr_y);
    }
    
  else if(x <= 270){
      offsetcount=10;
      if(curr_y < 0){
        curr_y = curr_y*(-1);
      }
      moveDown(curr_y);
 }
    
    else if(x <= 360){
      if(curr_y < 0){
        curr_y = curr_y*(-1);
      }
      moveUp(curr_y);
    }
    oldy = y;
    //y is now ready
   
   //servo moves pen to paper
   penOn();
   penOff();
   
  } 
}




void loop() {
//moveUp(1);
//moveForward(100);
//moveBackward(1);
//delay(2000);
plotsin();
//penOn();
//penOff();
 


}  

