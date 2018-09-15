#include <SD.h>
#include <SPI.h>
#include <RH_RF69.h>
#include "config.h"

File logfile;

#if DEBUG
#define VPRINT(data) Serial.print(data); logfile.print(data);
#define VPRINTLN(data) Serial.println(data); logfile.println(data);
#else
#define VPRINT(data)
#define VPRINTLN(data)
#endif

// Module initialisieren
// Radio
uint8_t key[] = { AES_KEY };
RH_RF69 rfm69(RADIO_CS, RADIO_INT);


void setup() {
  Serial.begin(115200);

  // SD init
  VPRINT("Init: SD ");
  if (!SD.begin(SD_PIN)) {
    VPRINTLN("[FAILED]");
    while (1);
  }
  VPRINTLN("[OK]");

  
  // Radio init
  VPRINT("Init: RFM69 ");
  if (!rfm69.init()) {
    VPRINTLN("[FAILED]");
    while (1);
  }
  rfm69.setFrequency(433.0);
  rfm69.setTxPower(20);
  rfm69.setEncryptionKey(key);
  rfm69.setModemConfig(RH_RF69::GFSK_Rb250Fd250);
  VPRINTLN("[OK]");
}

void loop() {
  
  if (rfm69.available()) {
    uint8_t buf[60];
    uint8_t len = sizeof(buf);
    
    if (rfm69.recv(buf, &len)){
      logfile = SD.open("log.txt", FILE_WRITE);
      logfile.println((char*)buf);
      logfile.close();
    } else {
      Serial.println("recv failed");
    }
  }
}
