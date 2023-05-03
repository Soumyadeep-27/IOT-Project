#include<Servo.h>
int sensorPin = A0; // select the input pin for LDR
int smoke = A1;//
int sensorValue = 0; // variable to store the value coming from the sensor
int data=0;
int ledPin = 2;                // choose the pin for the LED
int inputPin = 3;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;  // variable for reading the pin status
int trig=8;
int echo=9;
int dt=10;
Servo servo;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   pinMode(13, OUTPUT);
   digitalWrite(13,LOW);
   pinMode(12, OUTPUT);
   digitalWrite(12,LOW);
   pinMode(A0,INPUT);
   pinMode(A1,INPUT);
   pinMode(ledPin, OUTPUT);      // declare LED as output
   pinMode(inputPin, INPUT);     // declare sensor as input
   pinMode(trig,OUTPUT);
   pinMode(echo,INPUT);
  
   servo.attach(11);
}

void loop() {

data = analogRead(smoke);
  Serial.print("p.p.m value of the air :  ");
  Serial.println(data);
 /* if((data<230)&&(flag==0))
  {
    flag=1;
  }*/
  if (data>=90)
  {
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
     //tone(BUZZ, 1000, 500);
    
  }
  delay(100);
   
sensorValue = analogRead(sensorPin); // read the value from the sensor
Serial.println(sensorValue); //prints the values coming from the sensor on the screen

if(sensorValue >= 900)
  digitalWrite(12, HIGH);
else
  digitalWrite(12, LOW);
delay(1000);
digitalWrite(13,LOW);



val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
  
if (calc_dis()<10)
  {
  for (int i=0;i<=100;i++)
  {
    servo.write(i);
    delay(3);
  }
  delay(1500);
  for (int i=100;i>=0;i--)
  {
    servo.write(i);
    delay(3);
  }
  delay(1500);
}
  
  }
  

  int calc_dis()
{
  int duration,distance;
  digitalWrite(trig,HIGH);
  delay(dt);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}
