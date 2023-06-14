void listFiles(File dir) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      // No more files
      break;
    }
    if (entry.isDirectory()) {
      // Recursive call for directories
      listFiles(entry);
    } else {
      String fileName = entry.name();
      if (fileName.endsWith(".txt")) {
        // Remove the leading "/" and ".txt" extension
        fileName.remove(0, 1);
        fileName.remove(fileName.length() - 4);
        // Add the file name to the array
        txtFiles[txtFileCount] = fileName;
        txtFileCount++;
      }
    }
    entry.close();
  }
}

void sortFileNames() {
  for (int i = 0; i < txtFileCount - 1; i++) {
    for (int j = i + 1; j < txtFileCount; j++) {
      if (txtFiles[j] < txtFiles[i]) {
        // Swap file names
        String temp = txtFiles[i];
        txtFiles[i] = txtFiles[j];
        txtFiles[j] = temp;
      }
    }
  }
}

void logData(String file_name, String data_to_store) {
  File dataFile = SD.open(file_name, FILE_APPEND); // Append to the log file
  if (dataFile) {
    dataFile.print(data_to_store+"\n");
    dataFile.close();
    Serial.println("Data logged: " + data_to_store);
  } else {
    Serial.println("Error opening log file");
  }
}

void deleteFirstLine(String path) {
  File originalFile = SD.open(path);
  if (!originalFile) {
    Serial.println("Failed to open the file for reading");
    return;
  }
  
  File tempFile = SD.open("/temp.txt", FILE_WRITE);
  if (!tempFile) {
    Serial.println("Failed to create a temporary file for writing");
    originalFile.close();
    return;
  }

  bool isFirstLine = true;
  while(originalFile.available()){
    String line = originalFile.readStringUntil('\n');
    if (isFirstLine) {
      isFirstLine = false;
      continue;
    }
    tempFile.println(line);
  }

  originalFile.close();
  tempFile.close();

  // Delete the original file
  if (SD.remove(path)) {
    Serial.println("Original file deleted");
  } else {
    Serial.println("Failed to delete the original file");
  }

  // Rename the temporary file to the original file
  if (SD.rename("/temp.txt", path)) {
    Serial.println("Temporary file has been renamed to the original file");
  } else {
    Serial.println("Failed to rename the temporary file to the original file");
  }
}

void StoreData(){
  if (year() > 2022){
    String YYYY, MM, DD, hh, mm;
    YYYY  = String(year());
    if (month()<10){MM = "0"+String(month());}   else {MM = String(month());}
    if (day()<10){DD = "0"+String(day());}       else {DD = String(day());}
    if (hour()<10){hh = "0"+String(hour());}     else {hh = String(hour());}
    if (minute()<10){mm = "0"+String(minute());} else {mm = String(minute());}
    
    String filename  = "/" + YYYY + "-" + MM + "-" + DD + ".txt";
    String datastore = YYYY+"-"+MM+"-"+DD+" "+hh+":"+mm+":00" + "," + String(S_T1_min) + "," + String(S_T1_avg) + "," + String(S_T1_max) + "," + String(S_H1_min) + "," + String(S_H1_avg) + "," + String(S_H1_max) + "," + String(S_T2_min) + "," + String(S_T2_avg) + "," + String(S_T2_max) + "," + String(S_H2_min) + "," + String(S_H2_avg) + "," + String(S_H2_max) + "," + String(S_A1_min) + "," + String(S_A1_avg) + "," + String(S_A1_max);
    
    Serial.println("File Target   : " + filename);
    Serial.println("Data to Store : " + datastore);
    Serial.print(filename + " is");
    if (SD.exists(filename)) {
      Serial.println(" available");
      logData(filename, datastore);
    } else {
      Serial.println("'t available");
      Serial.println("Creating "+filename+" ...");
 
      File file = SD.open(filename, FILE_WRITE);
      if (file) {
        Serial.println(filename + " create");
        file.close();
        logData(filename, datastore);
      }
    }
  }
}

//--------------------------------------------------------------------------------------
void parseRow(String row) {
  int sensorCount = 0;
  
  char receivedDataBuffer[row.length() + 1];
  row.toCharArray(receivedDataBuffer, row.length() + 1);
  
  char* token = strtok(receivedDataBuffer, ",");
  
  while (token != NULL && sensorCount < MAX_rowData) {
    rowData[sensorCount] = String(token);
    token = strtok(NULL, ",");
    sensorCount++;
  }
}
