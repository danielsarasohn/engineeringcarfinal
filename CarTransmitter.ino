#include <nRF24L01.h>//include rf libraries
#include <RF24.h>
#include <SPI.h>

const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = A0; // analog pin connected to X output
const int Y_pin = A1; // analog pin connected to Y output



const uint64_t pipe = 0xE8E8F0F0E1LL;//set pipe
RF24 radio(9, 10);//set rf pins

int elephant[3];//declare our array
void setup() {
  radio.begin();//set up radio
  radio.openWritingPipe(pipe);//open pipe
  radio.setChannel(110);//set channel
  pinMode(SW_pin, INPUT);//set pin as input

}
  
void loop() {  
  elephant[0] = digitalRead(SW_pin);//read pin and send it as 0
  elephant[1] = analogRead(X_pin);//read pin and send it as 1
  elephant[2] = analogRead(Y_pin);//read pin and send it as 2
  radio.write(elephant, sizeof(elephant));//write all of the pins over rf

  delayMicroseconds(100);//delay 100 microseconds
}
