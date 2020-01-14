#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 radio(7, 8); // CE, CSN
const byte address = "0xF0F0F0F0E1LL";

int up_button     = 2;
int msg[3];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

 pinMode(up_button,INPUT);
 digitalWrite(up_button,HIGH);

}
void loop() {

    if(digitalRead(up_button)==LOW){
      int jox= analogRead(A0);
      int joy= analogRead(A1);
       msg[0]= 1; // UP
       msg[1]=jox;
       msg[2]=joy;
      radio.write(&msg,sizeof(msg));
      delay(300);

    }

}
