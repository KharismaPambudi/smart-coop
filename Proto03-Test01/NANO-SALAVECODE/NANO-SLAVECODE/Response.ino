void Response(){
  if (Serial.available()) {
    String data_masuk = Serial.readStringUntil("Z");  // Read incoming data
    String key = "R" + String(Slave_ID)+ "SZ";
    if (data_masuk == key){
      if (Slave_ID<9){
        int Data1 = round(t_min*10);
        int Data2 = round(t_jumlah*10/t_total);
        int Data3 = round(t_max*10);
        int Data4 = round(h_min);
        int Data5 = round(h_jumlah/h_total);
        int Data6 = round(h_max);
    
        String data_kirim = String(Slave_ID)+","+String(Data1)+","+String(Data2)+","+String(Data3)+","+String(Data4)+","+String(Data5)+","+String(Data6)+",Z";
        ResetData();        
        
        digitalWrite(RE_DE, HIGH);
        Serial.print(data_kirim);
        Serial.flush();
        digitalWrite(RE_DE, LOW);
      }
      if (Slave_ID>8){
        int Data7 = round(a_min);
        int Data8 = round(a_jumlah/a_total);
        int Data9 = round(a_max);
    
        String data_kirim = String(Slave_ID)+","+String(Data7)+","+String(Data8)+","+String(Data9)+"Z";
        ResetData();
        
        digitalWrite(RE_DE, HIGH);
        Serial.print(data_kirim);
        Serial.flush();
        digitalWrite(RE_DE, LOW);
      }
    }
  }
}
