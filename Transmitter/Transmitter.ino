// Load in the libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Set the CE & CSN pins
#define CE_PIN  7
#define CSN_PIN 8

// This is the address used to send/receive
const byte rxAddr[6] = "00001";

// Create a Radio
RF24 radio(CE_PIN, CSN_PIN); 

void setup() {
  
  // Start up the Serial connection
  while (!Serial);
  Serial.begin(115200);
  
  // Start the Radio!
  radio.begin();
  
  // Power setting. Due to likelihood of close proximity of the devices, set as RF24_PA_MIN (RF24_PA_MAX is default)
  radio.setPALevel(RF24_PA_MIN); // RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  
  // Slower data rate for better range
  radio.setDataRate( RF24_250KBPS ); // RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  
  // Number of retries and set tx/rx address
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);

  // Stop listening, so we can send!
  radio.stopListening();
}

const int MAX_LEN = 100;

void loop() {
  if (Serial.available() > 0) {
    // Set up a message and a timestamp to it using millis()
    unsigned char buffer[MAX_LEN];
    int length = Serial.readBytes(buffer, 32);
    if (length != 32) {
      Serial.print("Error: message was not expected 32 bytes: ");
      Serial.print(length);
      Serial.println();
    }
    else {
      radio.write(&buffer, 32);
    }

    // // http://stackoverflow.com/questions/7383606/converting-an-int-or-string-to-a-char-array-on-arduino
    // // Length (with one extra character for the null terminator)
    // int str_len = message.length() + 1; 
    // char char_array[str_len] = {0};
    // message.toCharArray(char_array, str_len);
    //int newlen = 15;
    //for (int i=0; i<newlen;i++)
    //{
      //Serial.print(buffer[i], HEX);
    //}
    //Serial.println();
    // buffer[22]=0xAA;
    // buffer[25]=0xAA;
    // buffer[43]=0xBB;
    //radio.write(&buffer, length);
    char log[500] = {0};
    int j = 0, chars = 0;
    for (int i=0; i<length; i++) {
      // Serial.print(buffer[i], HEX);
      // Serial.print(" ");
      chars = sprintf(log + j, i % 4 == 3 ? "%02x " : "%02x", buffer[i]);
      j += chars;
    }
    Serial.println(log);

    // radio.write(&buffer[23], 22);
  }
}
