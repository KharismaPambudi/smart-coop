#include "EbroMasterHeader.h"
void setup() {
  
  //  KOMUNIKASI UART
  Serial.begin(9600);                               // Monitor & Komunikasi dengan SLAVE 
  SerialGPS.begin(9600,SERIAL_8N1,rx1Pin,tx1Pin);   // Baca data GPS
  Serial2.begin(9600);                              // Komunikasi dengan ArduNano

//--------------------------------------------------------------------------------------
// Pin Flow-Control RS485
  pinMode(RE_DE, OUTPUT);
  digitalWrite(RE_DE,LOW);                          // --mode receive--
//--------------------------------------------------------------------------------------
// Inisiasi Koneksi WiFi
  connectToWiFi();
}

void loop() {
  // Check if Wi-Fi is still connected
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Reconnecting...");
    connectToWiFi();
  }
  
  if (SDavailable == false){
      if (!SD.begin(chipSelect)) {
      Serial.println("SD card initialization failed");
      delay(1000);
    } else {
      SDavailable = true;
      Serial.println("SD card initialized");
      delay(1000);
    }
  }
  GetGPS();
  RequestSensor();
  
  if (millis()-interval_sdcard_check >= last_sdcard_check){
    SendData();
    last_sdcard_check=millis();
  }

    if (millis()-interval_control >= last_control){
    ControlDataToSerial2();
    last_control=millis();
  }
  
}

void ControlDataToSerial2() {
  String data2 = String(S_T1_avg)+"/"+String(S_H1_avg)+"/"+String(S_T2_avg)+"/"+String(S_H2_avg)+"/"+String(S_A1_avg);
  data2 += "Z";

  // Send data to the slave
  Serial2.print(data2);

  // Print sent data on the serial monitor
  Serial.print("Sent Data: ");
  Serial.println(data2);
}
