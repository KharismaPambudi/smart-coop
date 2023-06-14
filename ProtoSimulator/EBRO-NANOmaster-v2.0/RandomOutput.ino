void RandomOutput(){
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    // Generate random values for each pin
    for (int i = 0; i < numPins; i++) {
      int randomValue = random(2);  // Generate 0 or 1 randomly
      digitalWrite(outputPins[i], randomValue);
    }
  }
}
