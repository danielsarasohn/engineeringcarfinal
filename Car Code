int enA = 5;//declaring variables
int in1 = 4;
int in2 = A0;
int enB = 6;
int in3 = 7;
int in4 = 8;
int Run = 1;
int Micros;
int trigPin = A2;
int echoPin = A3 ;
long duration, inches;

// Import installed libraries
#include <SPI.h>//libraries for rf
#include <nRF24L01.h>
#include <RF24.h>
// The 'pipe' or 'frequency'
// Same for sender and receiver
const uint64_t pipe = 0xE8E8F0F0E1LL;
// Declare object & Create Radio
RF24 radio(9, 10);
//Declare Variable 'rocket'
//as a 3 element array
int rocket[3];



int motorSpeedA = 0;//variables for motor speed
int motorSpeedB = 0;

void setup() {
  pinMode(enA, OUTPUT);//delcaring inputs and outputs
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(A1, OUTPUT);
  radio.begin();//beggining radio communications
  radio.openReadingPipe(1, pipe);
  radio.startListening();//tell radio its reciever
  radio.setChannel(110);//set radio channel
  Serial.begin(9600);//start serial monitor
  attachInterrupt(0, switching, RISING);//set interrupt which changes auton to tele-op
  Serial.print("Run = ");//lets us know auton/tele-op variable
  Serial.println(Run);
}
void off()//turns motor pins off to prevent short circuits
{
  digitalWrite (in1, LOW);
  digitalWrite (in2, LOW);
  digitalWrite (in3, LOW);
  digitalWrite (in4, LOW);
}
void loop() {

  if (Run == 1) {//if tele-op variable is 1 (RF Mode)
    Serial.print("Run = ");//print variable
    Serial.println(Run);
    int SW_pin = rocket[0]; // digital pin connected to switch output
    int xAxis = rocket[1]; // analog pin connected to X output
    int yAxis = rocket[2]; // analog pin connected to Y output
    radio.read(rocket, sizeof(rocket)); //recieve rf communications
    while (rocket[0] == 0)// if horn pin is high
    {
      Serial.println("horn");//serial print horn
      digitalWrite(A1, HIGH);//turn horn on
      return;//leave loop
    }
    Serial.print("Switch:  ");//print switch value
    Serial.println(rocket[0]);
    Serial.print("X-axis: ");//prints x axis value
    Serial.println(rocket[1]);
    Serial.print("Y-axis: ");//prints x axis value
    Serial.println(rocket[2]);
    Serial.print("\n\n");
    if (yAxis < 470) {//if yaxis is less than 470
      off();//calls off so there are no short circuits
      digitalWrite(in1, HIGH);//set drive to reverse
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);

      motorSpeedA = map(yAxis, 470, 0, 0, 255);//map motor speeds to axis
      motorSpeedB = map(yAxis, 470, 0, 0, 255);
    }
    else if (yAxis > 550) {//if y axis is greater than 550
      off();//calls off so there are no short circuits
      digitalWrite (in1, LOW);//set drivetrain to backwards
      digitalWrite (in2, HIGH);
      digitalWrite (in3, LOW);
      digitalWrite (in4, HIGH);
      motorSpeedA = map(yAxis, 550, 1023, 0, 255);//map motor speeds
      motorSpeedB = map(yAxis, 550, 1023, 0, 255);
    }
    else {//if joystick is in middle shut motors off
      motorSpeedA = 0;
      motorSpeedB = 0;
    }

    if (xAxis < 470 && yAxis < 550 || yAxis > 470) { // if xaxis is less than 470 and yaxis is less than 550 or yaxis is greater than 470 (if xaxis is right and yaxis is up or down)
      int xMapped = map(xAxis, 470, 0, 0, 255);//map motor speed
      motorSpeedA = motorSpeedA - xMapped; //set turning speed
      motorSpeedB = motorSpeedB + xMapped;
    }
    if (xAxis < 470 && yAxis < 550 && yAxis > 470) {// if xaxis is less than 470 and yaxis is less than 550 and yaxis is greater than 470 (if xaxis is right and yaxis is not up or down)
      off();//calls off so there are no short circuits
      int xMapped = map(xAxis, 470, 0, 0, 255);//map motor speed
      motorSpeedA = xMapped;//set motor speed
      motorSpeedB = xMapped;
      digitalWrite(in1, HIGH);//set turning wheels
      digitalWrite(in4, HIGH);
    }
    if (xAxis > 550 && yAxis < 550 && yAxis > 470) {//if xaxis is greater than 550 and yaxis is less than 550 and yaxis is greater than 470(if xaxis is left and yaxis is not up or down)
      off();//calls off so there are no short circuits
      int xMapped = map(xAxis, 470, 0, 0, 255);//map motor speed
      motorSpeedA = xMapped;//set motor speed
      motorSpeedB = xMapped;
      digitalWrite(in2, HIGH);//set turning wheels
      digitalWrite(in3, HIGH);
    }
    if (xAxis > 550 && yAxis < 550 || yAxis > 470) {//if xaxis is greater than 550 and yaxis is less than 550 or yaxis is greater than 470(if xaxis is left and yaxis is  up or down)
      int xMapped = map(xAxis, 470, 0, 0, 255);//map motor speed
      motorSpeedA = motorSpeedA + xMapped;//set turning speed
      motorSpeedB = motorSpeedB - xMapped;



    }
    if (motorSpeedA < 0) {//if motor speed is less than zero(can happen with the subtraction)
      motorSpeedA = 0;//motor speed set to 0
    }
    if (motorSpeedA > 255) {//if motor speed is greater than 255(can happen with the addition)
      motorSpeedA = 255;//motor speed set to 255
    }
    if (motorSpeedB < 0) {//if motor speed is less than zero(can happen with the subtraction)
      motorSpeedB = 0;//motor speed set to 0
    }
    if (motorSpeedB > 255) {//if motor speed is greater than 255(can happen with the addition)
      motorSpeedB = 255;//motor speed set to 255
    }
    if (!radio.available()) {//if radio is not availible
      motorSpeedA = 0;//turn off motors
      motorSpeedB = 0;
      SW_pin = 1; //turn off buzzer
      return;//leave loop
    }
    analogWrite(enA, motorSpeedA);//write motor speeds to motor enable pins
    analogWrite(enB, motorSpeedB);
  }
  if (Run == 0)//if tele-op/auton variable is zero
  {
    Serial.print("Run = ");//print the tele-op/auton variable
    Serial.println(Run);
    digitalWrite(enA, HIGH);//turn motors on we dont use speed control here
    digitalWrite(enB, HIGH);
    digitalWrite(trigPin, LOW);//turn of trig pon for optimal results
    delayMicroseconds(2);//wait two microseconds
    digitalWrite(trigPin, HIGH);//turn trig pin on
    delayMicroseconds(5);//wait 5 microseconds
    digitalWrite(trigPin, LOW);//turn trig pin off
    duration = pulseIn(echoPin, HIGH);//read the pulses form the trig pin
    inches = duration / 74 / 2;//map duration to inches
    Serial.println(inches);//print distance in inches
    delay(200);//wait 200 milliseconds as to not read to fast
    if (inches < 10)//if we are closer than 10 inches
    {
      Serial.print("Run = ");//print the tele-op/auton variable
      Serial.println(Run);
      off();//calls off so there are no short circuits
      digitalWrite(7, HIGH);//turn on the turning pins
    }
    else//if inches is greater than 10
    {
      Serial.print("Run = ");//print the tele-op/auton variable
      Serial.println(Run);
      off();//calls off so there are no short circuits
      digitalWrite (in2, HIGH);//go forwards
      digitalWrite (in4, HIGH);
      digitalWrite (in1, LOW);
      digitalWrite (in3, LOW);
    }
  }
  digitalWrite(A1, LOW);//turn off horn
}
void switching() {//interupt loop
  if (micros() - Micros > 1000000)//debounce
  {
    Micros = micros();//reset debounce
    Run = 1 - Run; //changes run from 1 to zero and back
  }
}
