#ifndef rfm_h
#define rfm_h
#include "Arduino.h"
#include <RH_RF69.h>

class Radio{
  public:
    Radio(uint8_t key, int CS, int INT, int RST);
    int init();
    void sendData(char *payload);
    boolean available();
    boolean recv(uint8_t* buf, uint8_t *len);
    
  private:
    RH_RF69 _radio;
    int _RST;
    uint8_t _key;
};

#endif
