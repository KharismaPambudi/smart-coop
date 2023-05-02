#ifndef COOPMASTER_H
#define COOPMASTER_H

// DAFTAR CONSTANT
#define RE_DE 4                    // Pin Kontrol Transmisi RS485 

// Daftar MODULE/LIBRARY
#include <HardwareSerial.h>        // TX2/RX2 (u/ komunikasi dengan slave)
#include <TimeLib.h>

// Variabel-variabel Waktu
unsigned long last_ping_time = 0;
unsigned long last_request = 0;

// Variabel-variabel GPS
const int rx1Pin = 2;
const int tx1Pin = 15;
HardwareSerial SerialGPS(1);
int lastMinute = -1;

// Variabel-variabel Sensor
int list_sensor[] = {1, 9};
String Tanggal, Waktu;
String Sensor1 = "0,0,0,0,0,0,";
String Sensor9 = "0,0,0";

bool GPS_State = false;
#endif
