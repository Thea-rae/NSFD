#include <RFM69.h>
#include <SPI.h> // the RFM69 library uses SPI

RFM69 radio;

#define myFrequency RF69_433MHZ // or RF69_433MHZ (check your radio)
int myNetwork = 123; // radios must share the same network (0-255)
int myID = 1; // radios should be given unique ID's (0-254, 255 = BROADCAST)

int hubID = 0; // the receiver for all sensor nodes in this example
int tempPin = A0;

// instead of sending a string, we can send a struct
// this struct must be shared between all nodes
typedef struct {
  int sensor0;
  int sensor1;
} 
Packet;

void setup() {

  // setup the radio
  radio.initialize(myFrequency, myID, myNetwork);

  // this example only uses Serial inside setup()
  // because Narcoleptic will stop Serial once used
  Serial.begin(9600);
  Serial.println("\nRADIO INITIALIZED");
  Serial.println("Sending sensor values");
}

void loop() {
  int reading = analogRead(tempPin);

  float voltage = reading * 3.3;
  voltage /=1024.0;

  Serial.print(voltage); 
  Serial.println(" volts");

  float tempC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
  //to degrees ((voltage - 500mV) times 100)
  Serial.print(tempC); 
  Serial.println(" degrees C");

  float tempF = (tempC * 9.0 / 5.0) + 32.0;
  Serial.print(tempF); 
  Serial.println(" degrees F");

  delay(1000);

  // create new instance of our Packet struct
  Packet packet;
  packet.sensor0 = tempC; // read values from the analog pins
  packet.sensor1 = tempF;

  int numberOfRetries = 25;

  // send reliable packet to the hub
  // notice the & next to packet when sending a struct
  boolean gotACK = radio.sendWithRetry(hubID,  &packet, sizeof(packet),numberOfRetries);

  if(gotACK) {
      Serial.println("got acknowledgment");
  }
  else {
     Serial.println("failed acknowledgment");
  }
}



