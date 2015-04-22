#include <RFM69.h>
#include <SPI.h> // the RFM69 library uses SPI

RFM69 radio;

#define myFrequency RF69_433MHZ // or RF69_433MHZ (check your radio)
int myNetwork = 123; // radios must share the same network (0-255)
int myID = 0; // radios should be given unique ID's (0-254, 255 = BROADCAST)

// our pre-defined packet structure
// this struct must be shared between all nodes
typedef struct {
  int tempC;
  int tempF;
} Packet;


void setup() {
  Serial.begin(9600);

  // setup the radio
  radio.initialize(myFrequency, myID, myNetwork);
    
  Serial.println("\nRADIO INITIALIZED\n");
  Serial.println("Listening for sensor nodes...");
}

void loop() {
    
  // always check to see if we've received a message
  if (radio.receiveDone()) {
          
    // if the received message is the same size as our pre-defined Packet struct
    // then assume that it is actually one of our Packets
    if(radio.DATALEN == sizeof(Packet)) {
    
      // convert the radio's raw byte array to our pre-defined Packet struct
      Packet newPacket = *(Packet*)radio.DATA;
      
      Serial.print("[");
      Serial.print(radio.SENDERID);
      Serial.print("]\ttempC = ");
      Serial.print(newPacket.tempC);
      Serial.print("\ttempF = ");
      Serial.println(newPacket.tempF);
    }
  }
}