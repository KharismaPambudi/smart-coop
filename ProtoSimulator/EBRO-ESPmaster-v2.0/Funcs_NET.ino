/*  FUNGSI PENGECEKAN KONEKSI INTERNET
 *  ping ke www.google.com
 *  output: true/false */
bool checkInternetConnectivity() {
  WiFiClient client;
  if (client.connect(internetTestHost, 80)) {
    client.stop();
    return true;
  } else {
    return false;
  }
}
//--------------------------------------------------------------------------------------
/*  FUNGSI PENGECEKAN UPLOAD TERAKHIR DI DATABASE
 *  dari API server database format JSON
 *  parsing JSON ke data structure dan vector */
void checkLastUpload(){
  tableData.clear();
  HTTPClient http;
  http.begin(url_check_data);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.println(payload);
    // Parse JSON
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.println("NET: Failed to parse JSON");
    } else {
      tableData.clear();
      // Extract data into vector
      for (const JsonPair& pair : doc.as<JsonObject>()) {
        TableData data;
        data.tableName = pair.key().c_str();
        data.lastUpload = pair.value().as<String>();
        tableData.push_back(data);
      }
    }
  } else {
    Serial.printf("NET: HTTP request failed with error code: %d\n", httpCode);
  }
  http.end();
}
//--------------------------------------------------------------------------------------
/*  FUNGSI UPLOAD DATA KE DATABASE
 *  FORMAT upload: JSON */
 
void uploadData(const String& jsonPayload) {
  // Create an HTTPClient object
  HTTPClient http;

  // Make the POST request
  http.begin(url_upload_data);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(jsonPayload);

  // Check the response code
  if (httpResponseCode == HTTP_CODE_OK) {
    Serial.println("Data uploaded successfully");
  } else {
    Serial.print("Data upload failed. Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
}
//--------------------------------------------------------------------------------------
/*  FUNGSI koneksi ke WiFi
 *  dari API server database format JSON
 *  parsing JSON ke data structure dan vector */
void connectToWiFi() {
  WiFi.begin(ssid, password);
  int attemptCount = 0;
  
  while (WiFi.status() != WL_CONNECTED && attemptCount < 10) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    attemptCount++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Failed to connect to WiFi");
  }
}
