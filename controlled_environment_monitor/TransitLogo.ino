


void TruckBandTruckFcobPosition1(){   
    //TruckB and TruckF Cargo on board position 1
    lcd.setCursor(2, 1);
    lcd.write(" ");
    lcd.setCursor(0, 1);
    lcd.write(1);
    lcd.setCursor(1, 1);
    lcd.write(2);
    }
void TruckBandTruckFcobPosition2(){
    //TruckB and TruckF Cargo on board position 2
    lcd.setCursor(0, 1);
    lcd.write(" ");
    lcd.setCursor(1, 1);
    lcd.write(1);
    lcd.setCursor(2, 1);
    lcd.write(2);
    }
    
void TruckBandTruckFncobPosition1(){
    //TruckB and TruckF No Cargo on board position 1
    lcd.setCursor(2, 1);
    lcd.write(" ");
    lcd.setCursor(0, 1);
    lcd.write(3);
    lcd.setCursor(1, 1);
    lcd.write(4);
    }
void TruckBandTruckFncobPosition2(){
     // TruckB and TruckF No Cargo on board Position 2
    lcd.setCursor(0, 1);
    lcd.write(" ");
    lcd.setCursor(1, 1);
    lcd.write(3);
    lcd.setCursor(2, 1);
    lcd.write(4);
    }