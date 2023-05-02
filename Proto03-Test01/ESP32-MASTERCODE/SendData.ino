void SendData() {
  
  String bulan,hari,jam,menit;
  
  if (month() <10){
    bulan = "0"+ String(month());
  } else {bulan = String(month());}

  if (day() <10){
    hari = "0"+ String(day());
  } else {hari = String(day());}

  if (hour() <10){
    jam = "0"+ String(hour());
  } else {jam = String(hour());}

  if (minute() <10){
    menit = "0"+ String(minute());
  } else {menit = String(minute());}
  
  String DataLog = String(year()) +"/"+ bulan +"/"+ hari +","+ jam +":"+ menit +":00,"+ Sensor1 + Sensor9 +"Z";
//  Serial.print(Sensor1);
//  Serial.print('/n');
//
//  Serial.print(Sensor9);
//  Serial.print('/n');
  
  Serial.print(DataLog);
  Serial.print('\n');
}
