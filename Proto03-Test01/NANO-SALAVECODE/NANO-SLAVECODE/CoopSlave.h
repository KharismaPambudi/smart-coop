#ifndef COOPSLAVE_H
#define COOPSLAVE_H
//--------------------------------------------------------------------------------------
// DAFTAR CONSTANT
#define Slave_ID 1                // Nomor ID Slave
#define RE_DE 5                   // Pin Kontrol Transmisi RS485 
//--------------------------------------------------------------------------------------
// Daftar MODULE/LIBRARY
#include <Wire.h>                 // komunikasi wire (I2C)
//--------------------------------------------------------------------------------------
#include "Adafruit_SHT31.h"       // SHT31
Adafruit_SHT31 sht31 = Adafruit_SHT31();
//--------------------------------------------------------------------------------------
// Variabel-variabel Awal
float t_jumlah = 0;               // jumlahan semua pembacaan temperature
int   t_total  = 0;               // total pembacaan temperature
float t_min = 0;                  // temperature minimal
float t_max = 0;                  // temperature maksimal

float h_jumlah = 0;               // jumlahan semua pembacaan humidity
int   h_total  = 0;               // total pembacaan humidity
float h_min = 0;                  // humidity minimal
float h_max = 0;                  // humidity maksimal

float a_jumlah = 0;               // jumlahan semua pembacaan ammonia
int   a_total  = 0;               // total pembacaan ammonia
float a_min = 0;                  // temperature ammonia
float a_max = 0;                  // temperature ammonia

unsigned long previousMillis = millis();
const unsigned long interval = 500;
unsigned long currentMillis  = millis();
//--------------------------------------------------------------------------------------
#endif
