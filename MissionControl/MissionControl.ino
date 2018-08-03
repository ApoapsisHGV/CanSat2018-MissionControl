#include <RH_RF69.h>
#include <SPI.h>
#include "rfm.h"
#include "config.h"

uint8_t key[] = { AES_KEY };
Radio rfm69(key, RADIO_CS, RADIO_INT, RADIO_RST);

void setup(){
  Serial.begin(115200);
  if(!rfm69.init()){
    Serial.println("Error during rfm69 init");
    while(1);
  }
}

void loop(){
   if (rfm69.available())
  {
    // Should be a message for us now   
    uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rfm69.recv(buf, &len))
    {
      Serial.print("got request: ");
      Serial.println((char*)buf);
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}

