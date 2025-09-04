void demoMode(){
// demo list of display icons with descriptions
lcd.begin(16, 2);
lcd.setCursor(3, 0);  
lcd.print("***DEMO***");
lcd.setCursor(3, 1);
lcd.print("***MODE***");
delay(2500);
//int (i == 0);
  //for (int i; i < 3; i++) {
    // TruckB and TruckF No Cargo on board in motion
    lcd.begin(16, 2);
    lcd.setCursor(4, 0);
    lcd.print("Vehicle");
    lcd.setCursor(0, 1);
    lcd.write(3);
    lcd.setCursor(1, 1);
    lcd.write(4);
    lcd.setCursor(3, 1);
    lcd.print("in Transit");
      delay(1200);
    lcd.begin(16, 2);
    lcd.setCursor(4, 0);
    lcd.print("Vehicle");
    lcd.setCursor(1, 1);
    lcd.write(3);
    lcd.setCursor(2, 1);
    lcd.write(4);
    lcd.setCursor(3, 1);
    lcd.print("in Transit");
      delay(1200);
    lcd.begin(16, 2);
    lcd.setCursor(4, 0);
    lcd.print("Vehicle");
    lcd.setCursor(0, 1);
    lcd.write(3);
    lcd.setCursor(1, 1);
    lcd.write(4);
    lcd.setCursor(3, 1);
    lcd.print("in Transit");
      delay(1200);
    lcd.begin(16, 2);
    lcd.setCursor(4, 0);
    lcd.print("Vehicle");
    lcd.setCursor(1, 1);
    lcd.write(3);
    lcd.setCursor(2, 1);
    lcd.write(4);
    lcd.setCursor(3, 1);
    lcd.print("in Transit");
      delay(1200);
   // }
      // TruckB and TruckF No Cargo on board
      lcd.begin(16, 2);
      lcd.setCursor(4, 0);
      lcd.print("No Cargo");
      lcd.setCursor(0, 1);
      lcd.write(3);
      lcd.setCursor(1, 1);
      lcd.write(4);
      lcd.setCursor(4, 1);
      lcd.print("on Board");
        delay(2500);
      
      // TruckB and TruckF Cargo on board
      lcd.begin(16, 2);
      lcd.setCursor(5, 0);
      lcd.print("Cargo");
      lcd.setCursor(0, 1);
      lcd.write(1);
      lcd.setCursor(1, 1);
      lcd.write(2);
      lcd.setCursor(4, 1);
      lcd.print("on Board");
      digitalWrite(LED1_PIN, HIGH);  // turn on LED1
        delay(2500);
      digitalWrite(LED1_PIN, LOW);  // turn off LED1
  
        // display fuel level less than half
        lcd.begin(16, 2);
        lcd.setCursor(3, 0);
        lcd.print("Fuel Level");
        lcd.setCursor(3, 1);
        lcd.print("Below Half");
        lcd.setCursor(15, 1);
        lcd.write(6);
          delay(2000);
        
        // display fuel level on reserve
        lcd.begin(16, 2);
        lcd.setCursor(3, 0);
        lcd.print("Fuel Level");
        lcd.setCursor(3, 1);
        lcd.print("On Reserve");
        lcd.setCursor(15, 1);
        lcd.write(5);
        digitalWrite(LED6_PIN, HIGH);  // turn on LED6
          delay(2000);
        digitalWrite(LED6_PIN, LOW);  // turn off LED6
        lcd.begin(16, 2);
        }