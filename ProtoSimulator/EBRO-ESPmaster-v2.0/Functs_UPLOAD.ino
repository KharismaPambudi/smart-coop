void SendData(){
//  SDCARD CHECK
  File root = SD.open("/");                                     // Listing .txt FILEs
  if (root) {
    Serial.println();Serial.println();
    Serial.println("List of .txt files:");
    txtFileCount = 0; // Reset the file count
    listFiles(root);
    root.close();
    // Sort the file names in ascending order
    sortFileNames();
    // Print the sorted file names
    for (int i = 0; i < txtFileCount; i++) {
      Serial.println("/"+txtFiles[i]+".txt");
    }
    Serial.println();
  } else {
    Serial.println("Error opening root directory");
  }

  Serial.println("Checking /" + txtFiles[0] +".txt ...");       // Checking oldest .txt FILE
  String filename = "/" + txtFiles[0] +".txt";

  bool filerow;
  File file = SD.open(filename);                                // Checking if file is empty
  if (file.available()){
    filerow = true;
    file.close();
  } else {
    filerow = true;
    SD.remove(filename);                                        // Delete file if it's empty
  }

  if (filerow){
    File file = SD.open(filename);
    if (file) {
      // Read the first row
      String firstRow = file.readStringUntil('\n');             // Read first row
      firstRow.replace("\r", "");
//      firstRow = firstRow.substring(0, firstRow.length()); 
      file.close();
  
      // Print the first row
      Serial.println("First row: " + firstRow);
      parseRow(firstRow);                                       // Listing .txt FILEs
    } else {
      Serial.println("Error opening file");
    }
  }
   
  if (checkInternetConnectivity()) {
    Serial.println("Internet connected");
    Serial.println("Check Last Upload ...");
    checkLastUpload();
    compareDateTime();

    if (upload[0] || upload[0] || upload[0]){
      jsonPayload = "{";
      if (upload[0]){
        jsonPayload += ("\""+ tableData[0].tableName + "\": {\"datetime_id\": \"");
        jsonPayload += (rowData[0] + "\",\"t_min\": ");
        jsonPayload += (rowData[1] + ",\"t_avg\": ");
        jsonPayload += (rowData[2] + ",\"t_max\": ");
        jsonPayload += (rowData[3] + ",\"h_min\": ");
        jsonPayload += (rowData[4] + ",\"h_avg\": ");
        jsonPayload += (rowData[5] + ",\"h_max\": ");
        jsonPayload += (rowData[6] + "}");
      }
      if (upload[1]){
        if (upload[0]){
           jsonPayload += ",";
        }
        jsonPayload += ("\""+ tableData[1].tableName + "\": {\"datetime_id\": \"");
        jsonPayload += (rowData[0] + "\",\"t_min\": ");
        jsonPayload += (rowData[7] + ",\"t_avg\": ");
        jsonPayload += (rowData[8] + ",\"t_max\": ");
        jsonPayload += (rowData[9] + ",\"h_min\": ");
        jsonPayload += (rowData[10] + ",\"h_avg\": ");
        jsonPayload += (rowData[11] + ",\"h_max\": ");
        jsonPayload += (rowData[12] + "}");
      }
      if (upload[2]){
        if (upload[1]){
           jsonPayload += ",";
        }
        jsonPayload += ("\""+ tableData[2].tableName + "\": {\"datetime_id\": \"");
        jsonPayload += (rowData[0] + "\",\"a_min\": ");
        jsonPayload += (rowData[13] + ",\"a_avg\": ");
        jsonPayload += (rowData[14] + ",\"a_max\": ");
        jsonPayload += (rowData[15] + "}");
      } 
      jsonPayload += "}";
      Serial.println(jsonPayload);
      uploadData(jsonPayload);
      jsonPayload="";

    } else {
      deleteFirstLine(filename);
//      deleteFirstRow(String filename);
    }
  } else {
    Serial.println("No internet connection");
  }
}

void compareDateTime(){
  upload[0] = isLeftSideNewest(rowData[0], tableData[0].lastUpload);
  upload[1] = isLeftSideNewest(rowData[0], tableData[1].lastUpload);
  upload[2] = isLeftSideNewest(rowData[0], tableData[2].lastUpload);
  Serial.print("Upload status: ");Serial.print(upload[0]);Serial.print(upload[1]);Serial.println(upload[2]);
}
  
  

bool isLeftSideNewest(const String& leftDateTime, const String& rightDateTime) {
  return leftDateTime.compareTo(rightDateTime) > 0;
}
