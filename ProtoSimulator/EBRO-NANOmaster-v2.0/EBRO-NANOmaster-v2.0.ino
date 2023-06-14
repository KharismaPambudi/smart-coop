// Output Pin
const int outputPins[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, A0};
const int numPins = sizeof(outputPins) / sizeof(outputPins[0]);

// Komuunikasi dengan MASTER ESP32
#include <SoftwareSerial.h>
SoftwareSerial MASTERserial(3, 2);
String receivedData;
const int maxIntegers = 5;
int SensorDatas[maxIntegers];  // Data sensor dari MASTER [T1, H1, T2, H2, A1]

// Variabel DUMMY 
unsigned long previousMillis = 0;
unsigned long currentMillis = millis();
const unsigned long interval = 5000;

void setup() {
  // Komunikasi dengan HMI menggunakan SERIAL0
  Serial.begin(115200);
  // Komunikasi dengan Master ESP32 menggunakan pin 2 & 3
  MASTERserial.begin(9600);
  // Set all pins as outputs
  for (int i = 0; i < numPins; i++) {
    pinMode(outputPins[i], OUTPUT);
  }
}

void loop() {
  // HANDLING DATA DARI MASTER
  if (MASTERserial.available()) {
    while (MASTERserial.available()) {
      char receivedChar = MASTERserial.read();
      if (receivedChar == 'Z') {
        // End of data received, process the received data
        processReceivedData();
        receivedData = ""; // Reset the received data string
      } else {
        // Append the received character to the data string
        receivedData += receivedChar;
      }
    }
  }

  // Untuk keperluan Simulasi (Random Output))
  RandomOutput();
}
