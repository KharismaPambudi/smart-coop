void ReadSensor() {
  if (Slave_ID<9){
//    Pembacaan Sensor SHT31
    float t_sekarang = sht31.readTemperature();
    float h_sekarang = sht31.readHumidity();

//    Proses Data Temperature
    t_jumlah = t_jumlah += t_sekarang;
    t_total++;
    if (t_max == 0){
      t_min = t_sekarang;
      t_max = t_sekarang;
    } else {
      if (t_min > t_sekarang){
        t_min = t_sekarang;
      }
      if (t_max < t_sekarang){
        t_max = t_sekarang;
      }
    }
//    Proses Data Humidity
    h_jumlah = h_jumlah += h_sekarang;
    h_total++;
    if (h_max == 0){
      h_min = h_sekarang;
      h_max = h_sekarang;
    } else {
      if (h_min > h_sekarang){
        h_min = h_sekarang;
      }
      if (h_max < h_sekarang){
        h_max = h_sekarang;
      }
    }
  }
//--------------------------------------------------------------------------------------
  if (Slave_ID>8){
//    float a_sekarang = 100 + 30 * sin(2 * PI * (millis()%3600000) / 3600000);
    currentMillis  = millis();
    if (currentMillis - previousMillis >= interval) {
      float a_sekarang = float(analogRead(A1));
      a_jumlah = a_jumlah += a_sekarang;
      a_total++;
      if (a_max == 0){
        a_min = a_sekarang;
        a_max = a_sekarang;
      }  else {
        if (a_min > a_sekarang){
          a_min = a_sekarang;
        }
        if (a_max < a_sekarang){
          a_max = a_sekarang;
        }
      }
      previousMillis = currentMillis;  // Update the previous time
    }
  }
}
