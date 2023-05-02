#include "CoopSlave.h"

//======================================================================================
void setup() {
//  KOMUNIKASI UART
  Serial.begin(9600);                         // Komunikasi dengan MASTER
  while (!Serial)
    delay(10);                                // pause sampai serial console terbuka
// Inisiasi Flow-Control RS485
  pinMode(RE_DE, OUTPUT);
  digitalWrite(RE_DE,LOW);                    // --mode receive--
  
  randomSeed(analogRead(0));                  // just for dummy
//--------------------------------------------------------------------------------------
  if (Slave_ID<9){
    if (! sht31.begin(0x44)) {                  // jika tidak connect ganti alamat ke 0x45 
      delay(10);
      while (1) delay(1);
    }
  }
}

void loop() {
  ReadSensor();
  Response();
}
