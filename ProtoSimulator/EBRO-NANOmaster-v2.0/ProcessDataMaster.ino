void processReceivedData() {
  Serial.println(receivedData);
  parseStringToIntArray(receivedData, SensorDatas, maxIntegers);
//  int count = parseStringToIntArray(receivedData, SensorDatas, maxIntegers);
//  for (int i = 0; i < count; i++) {
//    Serial.println(SensorDatas[i]);
//  }
}
void parseStringToIntArray(const String& data, int* integers, int maxSize) {
  int count = 0;
  char* token = strtok((char*)data.c_str(), "/");  // Split the string by "/"
  // Parse each token and store it in the integer array
  while (token != NULL && count < maxSize) {
    integers[count] = atoi(token);
    count++;
    token = strtok(NULL, "/");  // Move to the next token
  }
//  return count;
}
