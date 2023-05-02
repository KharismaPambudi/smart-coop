void RequestSensor(){
  if (minute() != lastMinute) {                   // check if minute has changed
    

    
    for (int i = 0; i < sizeof(list_sensor)/sizeof(list_sensor[0]); i++) { // loop list_sensor
      String sensorID = String(list_sensor[i]);
      String bytes_send = "R"+sensorID+"SZ";
//      Serial.println(); Serial.println(bytes_send);

      digitalWrite(RE_DE,HIGH);                     // --mode transmit--
      Serial2.print(bytes_send);
      Serial2.flush();
      digitalWrite(RE_DE,LOW);                      // --mode receive--
  
      last_request = millis();                      // mulai penghitungan timeout
      bool wait_response = true;
      while (wait_response){
        if (Serial2.available()) {
          String data_masuk = Serial2.readStringUntil('Z');

          if (sensorID == "1"){
            Sensor1 = data_masuk.substring(2);
          }
          
          if (sensorID == "9"){
            Sensor9 = data_masuk.substring(2);
          }
          
          wait_response = false;
          delay(2000);  
        }
        if ((millis()-last_request)>2000){
          wait_response = false;
        }
      }  
    }
    SendData();
    String Sensor1 = "0,0,0,0,0,0";
    String Sensor9 = "0,0,0";
    lastMinute = minute();
  }
}
