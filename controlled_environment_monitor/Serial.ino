void SerialinTransit(){
  Serial.printf(" Vehicle in Transit\n");  // Print Vehicle in Transit alert to the serial terminal
}
void TempHumiSerial(){
  Serial.print("    Temp:");
  Serial.print(DHT.temperature);
  Serial.print("°C    ");
  Serial.print("   Humi:");
  Serial.print(DHT.humidity);
  Serial.print("%\n");
}

void SerialDistance(){
  digitalWrite(TRIG_PIN, LOW);                 // Give a short LOW pulse beforehand to ensure a clean HIGH pulse
    delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);                // The sensor is triggered by a High pulse of
    delayMicroseconds(10);                     // 10 or more microseconds.
  digitalWrite(TRIG_PIN, LOW);                 // needed for accurate reads

  duration_us = pulseIn(ECHO_PIN, HIGH);       // measure duration of pulse from ECHO pin
  distance_cm = 0.017 * duration_us;           // calculate the distance

  Serial.begin(115200);                        // initialize serial port at 115200 baud rate
  Serial.print("\n Distance: ");               // display a message on serial terminal
  Serial.print(distance_cm);
  Serial.print("cm     ");
}