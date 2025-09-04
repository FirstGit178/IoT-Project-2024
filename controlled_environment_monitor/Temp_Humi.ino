void TempHumi(){
  DHT.read(DHT11_PIN);                         // read temp & humidity
  temp = DHT.temperature;
  humi =  DHT.humidity;
    delay(1000);                                 // delay for 1 second to get clear data read
  lcd.setCursor(12, 0);                         
  lcd.write(" ");                              // to clear C symbol following DHT error displying 255C
  lcd.setCursor(12, 1);                         
  lcd.write(" ");                              // to clear % symbol following DHT error displaying 255%

            // display Temperature and Humidity on serial terminal
  Serial.print("\n    Temp:");                   
  Serial.print(temp);
  Serial.print("°C    ");
  Serial.print("   Humi:");
  Serial.print(humi);
  Serial.print("%\n");
            // display Temperature and Humidity on LCD
  lcd.setCursor(4, 0);
  lcd.print("Temp:");
  lcd.print(DHT.temperature);
  lcd.print("C");
  lcd.setCursor(4, 1);
  lcd.print("Humi:");
  lcd.print(DHT.humidity);
  lcd.print("%");
}