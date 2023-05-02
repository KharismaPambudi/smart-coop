#include "CoopMaster.h"
#include <HardwareSerial.h>
//======================================================================================
void setup() {
//  KOMUNIKASI UART
  Serial.begin(115200);                               // TX0: Serial Monitor
  Serial2.begin(9600);                                // Komunikasi dengan SLAVE
  SerialGPS.begin(9600, SERIAL_8N1, rx1Pin, tx1Pin);  // Baca data GPS
//--------------------------------------------------------------------------------------
// Inisiasi Flow-Control RS485
  pinMode(RE_DE, OUTPUT);
  digitalWrite(RE_DE,LOW);                    // --mode receive--
//--------------------------------------------------------------------------------------

}
//======================================================================================
void loop() {
  GetGPS();
  RequestSensor();
}
