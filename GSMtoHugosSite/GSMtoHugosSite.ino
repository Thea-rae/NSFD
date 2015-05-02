#include <SoftwareSerial.h>

#define FONA_RX 2 //comms
#define FONA_TX 3 //comms

SoftwareSerial mySerial(FONA_RX, FONA_TX);
char inChar = 0;
void setup() {                
  Serial.begin(9600);
  Serial.println("Serial ready");
  mySerial.begin(9600);
  Serial.println("SoftwareS erial started");
  Serial.println("Setup Done");
  

  

  mySerial.println("AT+QICSGP=1,\"wap.cingular\"");
//  mySerial.print("\n");
  delay(500);
  
  mySerial.println("AT+QHTTPURL=36,30");
//  mySerial.print("\n");
  delay(500);
//
  mySerial.println("http://104.131.172.143:3000/add/asdf");
//  mySerial.print("\n");
  delay(500);
////  
  mySerial.println("AT+QHTTPGET=60");
//  mySerial.print("/n");
  delay(500);


}

void loop() {
    if (mySerial.available()){
      inChar = mySerial.read();
      Serial.write(inChar);
      delay(20);
    }
  if (Serial.available()>0){
    mySerial.write(Serial.read());
  }
}

void otherInfo(){
    mySerial.println("AT+QHTTPREAD=30");
//  mySerial.print("/n");
  delay(500);
}
