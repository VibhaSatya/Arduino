const int trigpin= 2;
const int echopin=3;
long distance;

void setup() {
  Serial.begin(9600);
  pinMode(echopin,INPUT);
  pinMode(trigpin,OUTPUT);
}
void getDistance()
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


void loop() {
  getDistance();

}
