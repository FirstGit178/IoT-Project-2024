/*
 Fergal McNamara 
  This code  
 measures temperature and humidity in a temperature controlled enviroment
 measures distance to an object to simulate cargo on board
 measures movement with an accelometer to simulate the vehicle in motion
 measures an analog signal from a potentiometer and converts readings through an ADC to simulate the fuel level 
 alerts are given with LEDs and displayed on a 16x2 LCD
 
 demo mode of LCD available by pressing and holding demo button for 2sec      //Add an interrupt for demo mode 

 Data also visible on Thingspeak                                           //Add an interrupt for demo mode 

 */

#include <Adafruit_MPU6050.h>
#include "rgb_lcd.h"
#include <DFRobot_DHT11.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros


Adafruit_MPU6050 mpu;
rgb_lcd lcd;
DFRobot_DHT11 DHT;

#define LED1_PIN 13           // ESP32 pin GPIO13 connected to LED's pin
#define LED2_PIN 14           // ESP32 pin GPIO14 connected to LED's pin
#define LED3_PIN 27           // ESP32 pin GPIO27 connected to LED's pin
#define LED4_PIN 26           // ESP32 pin GPIO26 connected to LED's pin
#define LED5_PIN 33           // ESP32 pin GPIO33 connected to LED's pin
#define LED6_PIN 25           // ESP32 pin GPIO25 connected to LED's pin

#define TRIG_PIN 18           // ESP32 pin GPIO18 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 5            // ESP32 pin GPIO5  connected to Ultrasonic Sensor's ECHO pin
#define demoMode_PIN 15       // ESP32 pin GPIO15 Push button to display DemoMode ICONS with descriptions 
#define DHT11_PIN 4           // ESP32 pin GPIO4  connected to DHT11 Temp & Humidity signal pin
#define SENSOR_PIN 32         // ESP32 pin GPIO32  connected to Poteniometer signal pin

#define DISTANCE_THRESHOLD 7  // set desired threshold distance to an object in centimeters
#define DHT_TEMPERATURE_THRESHOLD 20  // set desired threshold in degrees °C for upper temerature alarm level
#define DHT_HUMIDITY_THRESHOLD 93     // set desired threshold in % for humidity alarm level

int sensorValue = 4;          // variable to store the value coming from the sensor
float duration_us, distance_cm, temp, humi, motion, cargo_status;       //time, distance, temperature and humidity values will change

//distance_cm = cargo_status; 

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password

//int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

//****************************************************************

//uint8_t motion, cargo_status;

unsigned long lastUpdate = 0;        // At set up, start the timer from zero
const unsigned long updateInterval = 15000;  // Set the update interval (in milliseconds) 15000 = every 15 seconds

// flag for ***Demo Mode*** interrupt
volatile bool demoModeTriggered = false;            
//ISR,  the 'IRAM_ATTR' is required by ESP32 to place this function in fast-access memory (IRAM).
void IRAM_ATTR handleDemoButtonPress() {
  demoModeTriggered = true;
}

 // customChar();                    //unable to move to a different tab!!!
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
// customChar dhtRead             !!!!CAN NOT GET THIS CHARACTER TO WORK!!!!
byte dhtRead[8] = {                 ///Add char (dhtReadchar) and TRY AGAIN
  B00000,
  B00100,
  B01010,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup() {
  // setup code to run once
  Serial.begin(115200);       // initialize serial port at 115200 baud rate
   lcd.begin(16, 2);           // setup LCD 16 columns x 2 rows

  customCharsetup();
  motion = mpu.getMotionInterruptStatus();              //**********************

  pinMode(demoMode_PIN, INPUT_PULLUP); // set ESP32 pin to input mode (Pin is active low)
  pinMode(TRIG_PIN, OUTPUT);  // set ESP32 pin to output mode
  pinMode(ECHO_PIN, INPUT);   // set ESP32 pin to input mode
  pinMode(LED1_PIN, OUTPUT);  // set ESP32 pin to output mode
  pinMode(LED2_PIN, OUTPUT);   // set ESP32 pin to output mode
  pinMode(LED3_PIN, OUTPUT);   // set ESP32 pin to output mode
  pinMode(LED4_PIN, OUTPUT);   // set ESP32 pin to output mode
  pinMode(LED5_PIN, OUTPUT);   // set ESP32 pin to output mode
  pinMode(LED6_PIN, OUTPUT);  // set ESP32 pin to output mode

  
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  Serial.print("\n\n  Adafruit MPU6050 test!");  
  lcd.setCursor(4, 0);
  lcd.print("MPU6050");
  lcd.setCursor(5, 1);
  lcd.print("Test!");  
  delay(2500);                          // delay for 2 seconds

  while(!mpu.begin()) {                     // if accelerometer fails to start
  Serial.print("\n Failed to find MPU6050 chip");
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  lcd.print("Failed to find");  //***************add scroll*************************
  lcd.setCursor(2, 1); 
  lcd.print("MPU6050 chip");
    delay(2500);
   }

  Serial.println("\n  MPU6050 Found!");
  lcd.begin(16, 2);
  lcd.setCursor(4, 0);
  lcd.print("MPU6050");
  lcd.setCursor(5, 1);
  lcd.print("Found!");
    delay(1000);

            // setup motion detection
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true);  // Keep it latched.  Will turn off when reinitialized.
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);

  Serial.print("");
    delay(1000);

             
  demoMode();                    // demo list of display icons with descriptions
  attachInterrupt(digitalPinToInterrupt(demoMode_PIN), handleDemoButtonPress, FALLING); // Trigger DEMO MODE when INFO button is pressed
  
  }

                            
void loop() {               // main code to run repeatedly

unsigned long currentMillis = millis();   // Get the current time in milliseconds since the program started

  
  if (currentMillis - lastUpdate >= updateInterval) {   // Check if it's time to send data to ThingSpeak by subtracting start time from current time
    lastUpdate = currentMillis;  // Update the timestamp to lastUpdate with the current time for the next comparison
     ThingSpeakWrite();          // Send data
  }


  
  
  /*if (digitalRead(demoMode_PIN) == 0){        // Option for INFO button press to start DemoMode 
     demoMode();
    // digitalWrite(LED6_PIN, HIGH); 
     Serial.print("***Demo Mode active***");
     }   */                                             // Replaced this code with an ISR 

  if (demoModeTriggered) {                             // Check for flag
    demoModeTriggered = false;                        // If flag set then reset the flag
    Serial.println("***Demo Mode active***");
    demoMode();                                      // call ***DEMO MODE*** function
  }
  
  TempHumi();
  SerialDistance();                               // display a message on serial terminal
  DisplayLEDs();                                  //Display Temp and Humi limits on LEDs
  if (distance_cm < DISTANCE_THRESHOLD) {
    
    Serial.printf("\n Cargo on Board\n");  // Print alert to the serial terminal
    digitalWrite(LED1_PIN, HIGH);              // turn on LED1
    TruckBandTruckFcobPosition1();             // TruckB and TruckF Cargo on board position 1 message on LCD
    
      } else {  
      Serial.printf("\n No Cargo on Board\n");  // Print alert to the serial terminal                                
      digitalWrite(LED1_PIN, LOW);             // turn off LED1
      TruckBandTruckFncobPosition1();          // TruckB and TruckF No Cargo on board position 1 message on LCD
     
      }

  if (distance_cm < DISTANCE_THRESHOLD && mpu.getMotionInterruptStatus()) {
   
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);               // Get new sensor events
    digitalWrite(LED1_PIN, HIGH);              // Turn on LED1  Cargo on board

            
    SerialinTransit();                         //  Display Cargo on Board Vehicle in Transit alert to the serial terminal
    TruckBandTruckFcobPosition1();               // TruckB and TruckF Cargo on board position 1 message on LCD
      delay(1200);
    TruckBandTruckFcobPosition2();               // TruckB and TruckF Cargo on board position 2 message on LCD
   
      
    } else  if(mpu.getMotionInterruptStatus()) {
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);            // Get new sensor events
          
      SerialinTransit();                     // display No Cargo on Board Vehicle in Transit message on the serial terminal
      TruckBandTruckFncobPosition1();               //TruckB and TruckF No Cargo on board position 1
       delay(1200);
      TruckBandTruckFncobPosition2();               //TruckB and TruckF No Cargo on board position 2
        
    }
      ReadFuelLevel();
     
}