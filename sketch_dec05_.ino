/*
 Fergal McNamara 
 This code  

 measures movement in X,Y,Z with an accelometer 

 alert is displayed on a 16x2 LCD

 */

#include <Adafruit_MPU6050.h>
#include "rgb_lcd.h"
#include <DFRobot_DHT11.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
rgb_lcd lcd;
DFRobot_DHT11 DHT;

#define TRIG_PIN 18           // ESP32 pin GPIO18 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 5            // ESP32 pin GPIO5  connected to Ultrasonic Sensor's ECHO pin
#define LED1_PIN 13           // ESP32 pin GPIO13 connected to LED's pin
#define LED6_PIN 25           // ESP32 pin GPIO25 connected to LED's pin
#define DHT11_PIN 4           // ESP32 pin GPIO4  connected to DHT11 Temp & Humidity signal pin
#define DISTANCE_THRESHOLD 6  // set desired threshold distance to an object in centimeters
#define SENSOR_PIN 32         // ESP32 pin GPIO0  connected to Poteniometer signal pin

int sensorValue = 4;          // variable to store the value coming from the sensor
float duration_us, distance_cm;  //time and distance will change
                                 
// customChar truck back cargo on board  (cob)
byte TruckBcob[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01100,
  B01100
};
// customChar truck front cargo on board   (cob)
byte TruckFcob[8] = {
  B11000,
  B11110,
  B11010,
  B11111,
  B11111,
  B11111,
  B01100,
  B01100
};
// customChar truck back no cargo on board   (ncob)
byte TruckBncob[8] = {
  B11111,
  B10000,
  B10000,
  B10000,
  B10000,
  B11111,
  B01100,
  B01100
};
// customChar truck front no cargo on board  (ncob)
byte TruckFncob[8] = {
  B11000,
  B01110,
  B01010,
  B01111,
  B01111,
  B11111,
  B01100,
  B01100
};
// customChar fuel on reserve   (fuel low)
byte FuelLow[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111
};
// customChar fuel level less than half
byte Fuelhalf[8] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);       // initialize serial port at 115200 baud rate
  lcd.begin(16, 2);           // setup LCD 16 columns x 2 rows

  pinMode(TRIG_PIN, OUTPUT);  // set ESP32 pin to output mode
  pinMode(ECHO_PIN, INPUT);   // set ESP32 pin to input mode
  pinMode(LED1_PIN, OUTPUT);  // set ESP32 pin to output mode
  pinMode(LED6_PIN, OUTPUT);  // set ESP32 pin to output mode

#if 1
  // create character truck back cargo on board
  lcd.createChar(1, TruckBcob);
  // create character truck front cargo on board
  lcd.createChar(2, TruckFcob);
  // create character truck back no cargo on board
  lcd.createChar(3, TruckBncob);
  // create character truck front no cargo on board
  lcd.createChar(4, TruckFncob);
  // create character fuel on reserve 
  lcd.createChar(5, FuelLow);
  // create character fuel level less than half  
  lcd.createChar(6, Fuelhalf);
#endif

  Serial.print("Adafruit MPU6050 test!");  
  lcd.begin(16, 2);
  lcd.print("  MPU6050 test");
    delay(2000);                          // delay for 2 seconds

  while (!Serial)
    delay(1000);                          // will pause Zero, Leonardo, etc until serial console opens

  if (!mpu.begin()) {                     // if accelerometer fails to start

  Serial.print("Failed to find MPU6050 chip");
  lcd.begin(16, 2);
  lcd.print(" Failed to find MPU6050 chip");  //***************add scroll*************************
    delay(1000);

    while (1)
      delay(1000);
  }

  Serial.println("MPU6050 Found!");
  lcd.begin(16, 2);
  lcd.print("    MPU6050");
  lcd.setCursor(1, 1);
  lcd.print("    Found!");
    delay(1000);


  // setupt motion detection
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true);  // Keep it latched.  Will turn off when reinitialized.
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);

  Serial.print("");
    delay(1000);

  for (int i; i < 2; i++) {
  lcd.begin(16, 2);
  // TruckB and TruckF No Cargo on board in motion
  lcd.print("    Vehicle");
  lcd.setCursor(0, 1);
  lcd.write(3);
  lcd.setCursor(1, 1);
  lcd.write(4);
  lcd.print(" in Transit");
    delay(1200);
  // TruckB and TruckF
  lcd.begin(16, 2);
  lcd.print("    Vehicle");
  lcd.setCursor(1, 1);
  lcd.write(3);
  lcd.setCursor(2, 1);
  lcd.write(4);
  lcd.print("in Transit");
    delay(1200);
  }

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
  lcd.print("   Fuel Level");
  lcd.setCursor(1, 1);
  lcd.print("     Half");
  lcd.setCursor(15, 1);
  lcd.write(6);
    delay(2000);
  // display fuel level on reserve
  lcd.begin(16, 2);
  lcd.print("   Fuel Level");
  lcd.setCursor(1, 1);
  lcd.print("      Low");
  lcd.setCursor(15, 1);
  lcd.write(5);
  digitalWrite(LED6_PIN, HIGH);  // turn on LED6
    delay(2000);
  digitalWrite(LED6_PIN, LOW);  // turn off LED6
}

void loop() {

  // put your main code here, to run repeatedly:

  digitalWrite(TRIG_PIN, LOW);  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse
    delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);  // The sensor is triggered by a High pulse of
    delayMicroseconds(10);         //10 or more microseconds.
  digitalWrite(TRIG_PIN, LOW);   //?????

  duration_us = pulseIn(ECHO_PIN, HIGH);  // measure duration of pulse from ECHO pin
  distance_cm = 0.017 * duration_us;      // calculate the distance

  Serial.begin(115200);  // initialize serial port at 115200 baud rate
  // display a message on serial terminal
  Serial.print("\n Distance: ");
  Serial.print(distance_cm);
  Serial.print("cm     ");
  //read temp & humidity
  DHT.read(DHT11_PIN);
  Serial.print("    Temp:");
  Serial.print(DHT.temperature);
  Serial.print("°C    ");
  Serial.print("   Humi:");
  Serial.print(DHT.humidity);
  Serial.print("%\n");

  if (distance_cm < DISTANCE_THRESHOLD) {
    digitalWrite(LED1_PIN, HIGH);  // turn on LED1
    lcd.begin(16, 2);
    lcd.print("    Temp:");
    lcd.print(DHT.temperature);
    lcd.print("C");
    //TruckB and TruckFcob
    lcd.setCursor(0, 1);
    lcd.write(1);
    lcd.setCursor(1, 1);
    lcd.write(2);
    lcd.print("  Humi:");
    lcd.print(DHT.humidity);
    lcd.print("%");
      delay(1000);

  } else {                          // Print a message to the LCD
      digitalWrite(LED1_PIN, LOW);  // turn off LED1
      lcd.begin(16, 2);             // set up the LCD's number of columns and rows
      lcd.print("    Temp:");
      lcd.print(DHT.temperature);
      lcd.print("C");
      //TruckB and TruckFncob
      lcd.setCursor(0, 1);
      lcd.write(3);
      lcd.setCursor(1, 1);
      lcd.write(4);
      lcd.print("  Humi:");
      lcd.print(DHT.humidity);
      lcd.print("%");
        delay(1000);
  }
  if (distance_cm < DISTANCE_THRESHOLD && mpu.getMotionInterruptStatus()) {
    // Get new sensor events
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    digitalWrite(LED1_PIN, HIGH);  // turn on LED1
    // display message on the serial terminal
    Serial.print("    Temp:");
    Serial.print(DHT.temperature);
    Serial.print("°C    ");
    Serial.print("   Humi:");
    Serial.print(DHT.humidity);
    Serial.print("%\n");
    // display messages on LCD
    lcd.begin(16, 2);
    lcd.print("    Temp:");
    lcd.print(DHT.temperature);
    lcd.print("C");
    // TruckB and TruckFcob
    lcd.setCursor(0, 1);
    lcd.write(1);
    lcd.setCursor(1, 1);
    lcd.write(2);
    lcd.print("  Humi:");
    lcd.print(DHT.humidity);
    lcd.print("%");
      delay(1200);
    lcd.begin(16, 2);
    lcd.print("    Temp:");
    lcd.print(DHT.temperature);
    lcd.print("C");
    // TruckB and TruckFcob
    lcd.setCursor(1, 1);
    lcd.write(1);
    lcd.setCursor(2, 1);
    lcd.write(2);
    lcd.print(" Humi:");
    lcd.print(DHT.humidity);
    lcd.print("%");
      delay(1200);

  } else if (mpu.getMotionInterruptStatus()) {
      // Get new sensor events
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      //Print alert to the serial terminal
      Serial.printf("\n Vehicle in Transit\n");   
      // display a message on serial terminal
      Serial.print("    Temp:");
      Serial.print(DHT.temperature);
      Serial.print("°C    ");
      Serial.print("   Humi:");
      Serial.print(DHT.humidity);
      Serial.print("%\n");
      // display message on LCD
      lcd.print("    Temp:");
      lcd.print(DHT.temperature);
      lcd.print("C");
      //TruckB and TruckFncob
      lcd.setCursor(0, 1);
      lcd.write(3);
      lcd.setCursor(1, 1);
      lcd.write(4);
      lcd.print("  Humi:");
      lcd.print(DHT.humidity);
      lcd.print("%");
        delay(1200);
      lcd.begin(16, 2);
      lcd.print("    Temp:");
      lcd.print(DHT.temperature);
      lcd.print("C");
      //TruckB and TruckFncob
      lcd.setCursor(1, 1);
      lcd.write(3);
      lcd.setCursor(2, 1);
      lcd.write(4);
      lcd.print(" Humi:");
      lcd.print(DHT.humidity);
      lcd.print("%");
        delay(1200);
    }

  // read the value from the fuel sensor:
  sensorValue = analogRead(SENSOR_PIN);
  // // read the analog value for pin 2:
  // int analogValue = analogRead(SENSOR_PIN);

  // print out the values read
  Serial.printf("\n ADC analog value = %d\n", analogValue);
    delay(10);              // delay in between reads for clear read from serial

  if (sensorValue < 3023 || sensorValue == 2024) {
    Serial.printf("\n Fuel Half");
    // Print an alert message to the LCD
    lcd.setCursor(15, 1);
    lcd.write(6);
    // delay(500);
    }else if (sensorValue < 2023) {
      // Print an alarm message to the LCD
      Serial.printf("\n Fuel Low");
      digitalWrite(LED6_PIN, HIGH);  // turn on LED6
      lcd.setCursor(15, 1);
      lcd.write(5);
      //delay(500);
      // lcd.write("");
      // delay(500);
      } else {
        digitalWrite(LED6_PIN, LOW);  // turn off LED6
      }

}
