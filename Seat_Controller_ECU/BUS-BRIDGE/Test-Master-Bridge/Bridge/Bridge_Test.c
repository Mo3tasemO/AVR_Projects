#include <Arduino.h>

#include <Wire.h>

volatile uint8_t rxBuf[64];
volatile uint8_t rxLen = 0;

void onReceiveCB(int len) {
  rxLen = 0;
  while (Wire.available() && rxLen < sizeof(rxBuf)) {
    rxBuf[rxLen++] = Wire.read();
  }
}

void setup() {
  Serial.begin(115200); // we used this baudrate with stm32
  Wire.begin(0x28);               // 7-bit address, matches STM32
  Wire.setClock(100000);
  Wire.onReceive(onReceiveCB);
  Serial.println("Slave ready");
}

void loop() {
  if (rxLen) {
    noInterrupts();
    uint8_t local[64]; uint8_t n = rxLen;
    memcpy(local, (const void*)rxBuf, n);
    rxLen = 0;
    interrupts();

    // If newline present -> treat as text
    bool isText = false;
    for (uint8_t i=0;i<n;i++) if (local[i]=='\n') { isText=true; break; }
    // the data should be printed in test bench for example the alive message
    if (isText) {
      Serial.print("Message: ");
      for (uint8_t i=0;i<n;i++) Serial.write(local[i]);
    } else if (n == 4) {
      uint16_t ts = (uint16_t)local[0] | ((uint16_t)local[1] << 8);
      uint16_t ctr= (uint16_t)local[2] | ((uint16_t)local[3] << 8);
      Serial.print("Alive Message: Ts="); Serial.print(ts);
      Serial.print(" Ctr="); Serial.println(ctr);
    } else {
      Serial.print("RAW["); Serial.print(n); Serial.print("]: ");
      for (uint8_t i=0;i<n;i++) { Serial.print(local[i], HEX); Serial.print(' '); }
      Serial.println();
    }
  }
}