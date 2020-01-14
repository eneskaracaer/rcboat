#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address = "0xF0F0F0F0E1LL";
int msg[3];

Servo motor;
int servoDegree;

const int BIA = 6; // speed control
const int BIB = 5;
byte speed = 180;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

 motor.attach(3);
 pinMode(BIB, OUTPUT);
 pinMode(BIA, OUTPUT);
}

void loop() {
  while (radio.available()) {

    radio.read(&msg, sizeof(msg));
    delay(50);

    if(msg[0] == 1){
      forward();
      servo();
    }

  } // while
} // loop

void forward()
{
  digitalWrite(BIA,LOW);
  digitalWrite(BIB,HIGH);
  delay(200);
  digitalWrite(BIA,LOW);
  digitalWrite(BIB,LOW);
}

void servo(){

  servoDegree = map(msg[1],0,672,0,45);
  motor.write(servoDegree);
  delay(50);

}
