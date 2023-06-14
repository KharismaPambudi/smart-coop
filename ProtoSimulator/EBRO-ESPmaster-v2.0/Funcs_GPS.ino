// ===========================================================================================================
// Fungsi Pengambilan data Tanggal dan Waktu dari Modul GPS
// ===========================================================================================================
/*************************************************************************************************************
   1. Membaca data-stream dari GPS Module UBLOX NEO M8
      Format data-stream menggunakan beberapa baris dengan standart NMEA
   2. Ambil baris dengan kode "$GPMRC" yaitu Recommended Minimum specific GPS/Transit data
   3. Cek apakah bagian waktu dan tanggal ada, jika ada GPS_State = TRUE
   4. Konversi Waktu UTC menjadi Waktu Indonesia Barat (GMT+7)
*************************************************************************************************************/
 
void GetGPS(){  
// Ambil Data dari GPS Module
  if (SerialGPS.available()) {
    String gpsData = SerialGPS.readStringUntil('\n');     // Read SerialGPS
    if (gpsData.startsWith("$GPRMC")) {                   // Ambil baris GPRMC dari NMEA data Stream
//      Serial.println(gpsData);
      String fields[13];                                  // Pecah data GPMRC menggunakan tanda (,)
      int fieldCount = 0;
      int startIndex = 0;
      int endIndex = 0;
      while (endIndex < gpsData.length() && fieldCount < 13) {
        endIndex = gpsData.indexOf(',', startIndex);
        if (endIndex == -1) {
          endIndex = gpsData.length();
        }
        fields[fieldCount] = gpsData.substring(startIndex, endIndex);
        startIndex = endIndex + 1;
        fieldCount++;
      }
      if (fieldCount == 13) {           // Cek apakah data GPMRC utuh
        String utcTime = fields[1];     // Ambil data Waktu dalam UTC
        String utcDate = fields[9];     // Ambil data Tanggal dalam UTC
        
        if (utcTime == "" || utcDate == "") {  // Cek apakah data Waktu dan Tanggal utuh
          GPS_State = false; // GPS belum mendapat UTC-datetime dari Satelit
        } else {
          GPS_State = true;  // GPS mendapat UTC-datetime dari Satelit
          
          int utc_h =  utcTime.substring(0, 2).toInt();         // UTC hour
          int utc_m =  utcTime.substring(2, 4).toInt();         // UTC minute
          int utc_s =  utcTime.substring(4, 6).toInt();         // UTC second
          int utc_D =  utcDate.substring(0, 2).toInt();         // UTC day
          int utc_M =  utcDate.substring(2, 4).toInt();         // UTC month
          int utc_Y =  2000 + utcDate.substring(4, 6).toInt();  // UTC year

          setTime(utc_h, utc_m, utc_s, utc_D, utc_M, utc_Y);    // Set waktu dan tanggal 
          adjustTime(7*3600);                                   // Konversi ke UTC+7 (Waktu Indonesia Barat)       
        }
      }
    }
  }
}
