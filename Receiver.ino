// Load up the libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// define the pins
#define CE_PIN   7
#define CSN_PIN  8

// Create a Radio
RF24 radio(CE_PIN, CSN_PIN); 

// The tx/rx address
const byte rxAddr[6] = "00001";

unsigned char data[32] = {0};

void setup()
{
  // Start the serial
  Serial.begin(115200);
  while(!Serial);
  Serial.println("NRF24L01P Receiver Starting...");
  
  // Start the radio, again set to min & slow as I'm guessing while testing theire really close to each other
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);   // RF24_PA_MIN ,RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate( RF24_250KBPS ); // RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  
  // Set the reading pipe and start listening
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();
  Serial.println("NRF24L01P Listening...");
}

void loop()
{
  if (radio.available())
  {
    // the buffer to store the received message in 
    radio.read(&data, sizeof(data));
 
    for (int i=0; i<32; i++) {
    
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}
