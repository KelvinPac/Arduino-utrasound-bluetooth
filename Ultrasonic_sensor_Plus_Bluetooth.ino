/*
  HC-SR04 Ping distance sensor]
  VCC to arduino 5v GND to arduino GND
  Echo to Arduino pin 13 Trig to Arduino pin 12
  Red POS to Arduino pin 11
  Green POS to Arduino pin 10
  560 ohm resistor to both LED NEG and GRD power rail
  More info at: http://goo.gl/kJ8Gl
  Original code improvements to the Ping sketch sourced from Trollmaker.com
  Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/
#include <AFMotor.h>

#define trigPin 13
#define echoPin 12
#define frontlight 3
#define backlight 5

AF_DCMotor motor1(3);
AF_DCMotor motor2(4);
char command;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(frontlight, OUTPUT);
  pinMode(backlight, OUTPUT);

}

void loop() {
  if(Serial.available() > 0){ 
    command = Serial.read(); 
    Stop(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.   
    //Serial.println(command);
    switch(command){
    case 'F':  
      forward();
      break;
    case 'B':  
       back();
      break;
    case 'L':  
      left();
      break;
    case 'R':
      right();
      break;
    }
  } 
}

void back()
{
  motor1.setSpeed(255); 
  motor1.run(BACKWARD); //rotate the motor counterclockwise
  motor2.setSpeed(255); 
  motor2.run(BACKWARD); //rotate the motor counterclockwise
  digitalWrite(5, LOW);   // turn the LED off (LOW is the voltage level)
  digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void left()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(0);
  motor2.run(RELEASE); //turn motor2 off
}

void right()
{
  motor1.setSpeed(0);
  motor1.run(RELEASE); //turn motor1 off
  motor2.setSpeed(255); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
}

void Stop()
{
  motor1.setSpeed(0);
  motor2.run(RELEASE); //turn motor1 off
  motor2.setSpeed(0);
  motor2.run(RELEASE); //turn motor2 off
}
void forward()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

if (distance < 30) {  // This is where the LED On/Off happens
    motor1.run(RELEASE); //rotate the motor clockwise
    motor2.run(RELEASE); //rotate the motor clockwise
    digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(3, LOW);   // turn the LED off (LOW is the voltage level)
  }
  else {
    motor1.setSpeed(255); //Define maximum velocity
    motor1.run(FORWARD); //rotate the motor clockwise
    motor2.setSpeed(255); //Define maximum velocity
    motor2.run(FORWARD); //rotate the motor clockwise
    digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(3, HIGH);   // turn the LED off (LOW is the voltage level)
  }
  }
 
