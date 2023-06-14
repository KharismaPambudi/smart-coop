void RequestSensor(){
  if (minute() != lastMinute && minute()%4==0 && year()>2022) {        // Check if minute has changed
    Serial.println("Requesting Sensors Data ...");
    Serial.flush();
    digitalWrite(RE_DE,LOW);
    delay(1000);
    for (int i = 0; i < sizeof(list_sensor)/sizeof(list_sensor[0]); i++) { // loop list_sensor
      String sensorID = (list_sensor[i]);
      String bytes_send = sensorID+"SZ";
      
      digitalWrite(RE_DE,HIGH);                     // --mode transmit--
      Serial.print(bytes_send);
      Serial.flush();
      digitalWrite(RE_DE,LOW);                      // --mode receive--
  
      last_request = millis();                      // mulai penghitungan timeout
      bool wait_response = true;
      while (wait_response){
        if (Serial.available()) {
          data_masuk = Serial.readStringUntil('Z');
          wait_response = false;
          delay(2000);
        }
        if ((millis()-last_request)>4000){
          wait_response = false;
        }
      }
      parseData();
    }
//--------------------------------------------------------------------------------------
    StoreData();
//--------------------------------------------------------------------------------------
    lastMinute = minute();
  }
}

void parseData() {
  int sensorCount = 0;
  
  char receivedDataBuffer[data_masuk.length() + 1];
  data_masuk.toCharArray(receivedDataBuffer, data_masuk.length() + 1);
  
  char* token = strtok(receivedDataBuffer, ",");
  
  while (token != NULL && sensorCount < MAX_SENSORS) {
    sensorData[sensorCount] = String(token);
    token = strtok(NULL, ",");
    sensorCount++;
  }

  if (sensorData[0] == "AM1"){
    S_A1_min = sensorData[1].toInt();
    S_A1_avg = sensorData[2].toInt();
    S_A1_max = sensorData[3].toInt();
    Serial.print(S_A1_min);Serial.print("---");Serial.print(S_A1_min);Serial.print("---");Serial.println(S_A1_max);
    Serial.flush(); delay(500);
  }
  if (sensorData[0] == "HT1"){
    S_T1_min = sensorData[1].toInt();
    S_T1_avg = sensorData[2].toInt();
    S_T1_max = sensorData[3].toInt();
    S_H1_min = sensorData[4].toInt();
    S_H1_avg = sensorData[5].toInt();
    S_H1_max = sensorData[6].toInt();
    Serial.print(S_T1_min);Serial.print("---");Serial.print(S_T1_min);Serial.print("---");Serial.print(S_T1_max);Serial.print("---");
    Serial.print(S_H1_min);Serial.print("---");Serial.print(S_H1_min);Serial.print("---");Serial.println(S_H1_max);
    Serial.flush(); delay(500);
  }
  if (sensorData[0] == "HT2"){
    S_T2_min = sensorData[1].toInt();
    S_T2_avg = sensorData[2].toInt();
    S_T2_max = sensorData[3].toInt();
    S_H2_min = sensorData[4].toInt();
    S_H2_avg = sensorData[5].toInt();
    S_H2_max = sensorData[6].toInt();
    Serial.print(S_T2_min);Serial.print("---");Serial.print(S_T2_min);Serial.print("---");Serial.print(S_T2_max);Serial.print("---");
    Serial.print(S_H2_min);Serial.print("---");Serial.print(S_H2_min);Serial.print("---");Serial.println(S_H2_max);
    Serial.flush(); delay(500);
  }
}
