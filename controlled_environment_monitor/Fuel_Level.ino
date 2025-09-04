void ReadFuelLevel(){
sensorValue = analogRead(SENSOR_PIN);                        // read the value from the fuel sensor:
  int analogValue = analogRead(SENSOR_PIN);                    // read the analog value for pin 32:
  Serial.printf("\n ADC analog value = %d", analogValue);   // print out the values read
    delay(10);                                                // delay in between reads for clear read from serial
//}
//void FuelLevel(){
if (sensorValue > 3001) {
  Serial.printf("\n Fuel above Half\n");  
  lcd.setCursor(15, 1);
  lcd.write(" ");
  } 
  else if (sensorValue < 3069 && sensorValue > 1023) {
    Serial.printf("\n Fuel less than Half\n");
    lcd.setCursor(15, 1);
    lcd.write(6);                                               // Print an alert message to the LCD
  }
    else {
      lcd.setCursor(15, 1);
      lcd.write(" "); 
    }

if (sensorValue < 1023) {
  Serial.printf("\n Fuel Low\n");
  digitalWrite(LED6_PIN, HIGH);                              // turn on LED6
  lcd.setCursor(15, 1);
  lcd.write(5);                                              // Print an alarm message to the LCD
    delay(500);
  lcd.setCursor(15, 1);
  lcd.write(" ");
  } 
    else {
      digitalWrite(LED6_PIN, LOW);             // turn off LED6                 
    }
}