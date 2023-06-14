#ifndef EBROMASTERHEADER_H
#define EBROMASTERHEADER_H

//--------------------------------------------------------------------------------------
#define RE_DE 32                   // Pin Kontrol Transmisi RS485 
//--------------------------------------------------------------------------------------
#include <HardwareSerial.h>        // TX2/RX2 (u/ komunikasi dengan slave)
//--------------------------------------------------------------------------------------
#include <TimeLib.h>               // Konversi Waktu
//--------------------------------------------------------------------------------------
#include <WiFi.h>                  // Internet Communication
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <vector>
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
const char* ssid = "PERBEJA";                       // ssid
const char* password = "Reinuha2022";               // password
const char* internetTestHost = "www.google.com";    // url untuk tes koneksi internet
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// handling JSON data dari API ke vector & structure
struct TableData {
  String tableName;
  String lastUpload;
};

std::vector<TableData> tableData;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// url untuk pengecekan terakhir upload di MYSQL database table
// jumlah tabel sesuai jumlah sensor yang dihandle oaleh master
String url_check_data = "https://ebro.reinutech.com/apisensorlog/lastupload.php?table=Z18AF7,Z18AF8,Z18B01";
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// url untuk upload ke MYSQL database table
String url_upload_data = "https://ebro.reinutech.com/apisensorlog/upload.php";
String jsonPayload;
//--------------------------------------------------------------------------------------
// Variabel Waktu & Timing
unsigned long last_request = 0;               // waktu terakhir request data ke sensor
unsigned long last_sdcard_check = 0;          // waktu terakhir pengecekan SD-Card
unsigned long interval_sdcard_check = 10000;  // interval pengecekan SD-Card

unsigned long last_control = 0;
unsigned long interval_control = 5000;
//--------------------------------------------------------------------------------------
// GPS HANDLING
const int rx1Pin = 2;                         // Pin RX --> ke TX GPS
const int tx1Pin = 4;                         // Pin TX --> ke RX GPS
HardwareSerial SerialGPS(1);                  // Set HardwareSerial untuk GPS
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Global Variabel terkait GPS
int lastMinute = -1;            
bool GPS_State = false;
//--------------------------------------------------------------------------------------
// Variabel-variabel Sensor
String list_sensor[] = {"AM1","HT1","HT2"};   // List Alamat Sensor
String Tanggal, Waktu, data_masuk;
int S_A1_min, S_A1_avg, S_A1_max;
int S_T1_min, S_T1_avg, S_T1_max, S_H1_min, S_H1_avg, S_H1_max;
int S_T2_min, S_T2_avg, S_T2_max, S_H2_min, S_H2_avg, S_H2_max;

#define MAX_SENSORS 7            // jumlah sensor maksimal untuk 1 tipe sensor
String sensorData[MAX_SENSORS];  // Array to store the separated sensor data
//--------------------------------------------------------------------------------------
#define MAX_rowData 16  // Maximum number of sensors in the data string
String rowData[MAX_rowData];  // Array to store the separated sensor data
//--------------------------------------------------------------------------------------
// SD STORAGE
#include <FS.h>
#include <SD.h>
#include <SPI.h>
const int chipSelect = 5;  // pin CS (spi) SD-Card
String txtFiles[100];      // Global array variable to store .txt file names
int txtFileCount = 0;      // Counter for the number of .txt files
bool SDavailable = false;  // Global boolean variable to check SD card availability
bool upload[3] = {false,false,false};

#endif
