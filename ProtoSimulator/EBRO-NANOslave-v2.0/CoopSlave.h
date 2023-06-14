#ifndef COOPSLAVE_H
#define COOPSLAVE_H
//--------------------------------------------------------------------------------------
// RS485 Communication
#define RE_DE 3                   // Pin Kontrol Transmisi RS485
//--------------------------------------------------------------------------------------
// SWITCH & TM1637 DISPLAY
#include <TM1637Display.h>        // Muat Library Display

bool Slave_SW[] = {LOW,LOW,LOW,LOW};
String Slave_TYPE = "HT";
uint8_t Slave_ID  = 0;            // Nomor ID Slave

uint8_t segment4[] = {
  0xff, 0xff, 0xff, 0xff };       // variable display

#define CLK 9
#define DIO 8
TM1637Display display(CLK, DIO);

int saklar0 = 7; int saklar1 = 6; int saklar2 = 5; int saklar3 = 4;

#include <avr/wdt.h>              // software reset

//--------------------------------------------------------------------------------------
// Daftar MODULE/LIBRARY
#include <Wire.h>                 // komunikasi wire (I2C)
//--------------------------------------------------------------------------------------
#include "Adafruit_SHT31.h"       // SHT31
Adafruit_SHT31 sht31 = Adafruit_SHT31();
//--------------------------------------------------------------------------------------
// Variabel-variabel Awal

float t_sekarang;
float h_sekarang;
float a_sekarang;

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
const unsigned long interval = 2000;
unsigned long currentMillis  = millis();

// 12V B A GND
//  1  2 3  4
//--------------------------------------------------------------------------------------
#endif
