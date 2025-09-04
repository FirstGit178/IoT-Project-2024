
DFRobot_DHT11 DHT;            // default constructor
#define DHT11_PIN 4           // ESP32 pin GPIO4  connected to DHT11 Temp & Humidity signal pin
float duration_us, distance_cm, temp, humi, motion, cargo_status;    //time, distance, temperature and humidity values will change 


Adafruit_MPU6050 mpu;                     // default constructor 
motion = mpu.getMotionInterruptStatus();  // checks if a flag set
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);  // setup motion detection to filter out low frequency noise 
  mpu.setMotionDetectionThreshold(1);    // sets the sensitivity of motion detection 
  mpu.setMotionDetectionDuration(20);    // sets the duration in ms of movement, if duration exceeded 
  mpu.setInterruptPinLatch(true);        // pin is active high and keep it latched.  Will turn off when reinitialized.
  mpu.setInterruptPinPolarity(true);     // Interrupt detected sets pin high 
  mpu.setMotionInterrupt(true);          //sets a flag when motion is detected
   sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);          // Get new sensor event data



#define TRIG_PIN 18           // ESP32 pin GPIO18 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 5            // ESP32 pin GPIO5  connected to Ultrasonic Sensor's ECHO pin
#define DISTANCE_THRESHOLD 7  // set desired threshold distance to an object in centimeters
  pinMode(TRIG_PIN, OUTPUT);  // set ESP32 pin to output mode
  pinMode(ECHO_PIN, INPUT);   // set ESP32 pin to input mode
float duration_us, distance_cm, temp, humi, motion, cargo_status;       //time, distance,   temperature and humidity values will change
duration_us = pulseIn(ECHO_PIN, HIGH);       // measure duration of pulse from ECHO pin
  distance_cm = 0.017 * duration_us;           // calculate the distance


  #define SENSOR_PIN 32         // ESP32 pin GPIO32  connected to Poteniometer signal pin
  #define DISTANCE_THRESHOLD 7  // set desired threshold distance to an object in centimeters
  int sensorValue = 4;          // variable to store the value coming from the sensor
  sensorValue = analogRead(SENSOR_PIN);                // read the value from the fuel sensor
  int analogValue = analogRead(SENSOR_PIN);            // read the analog value for pin32

#define demoMode_PIN 15// ESP32 pin GPIO15 Push button to display DemoMode ICONS with descriptions
// Original code for Demo Mode operation
   /*if (digitalRead(demoMode_PIN) == 0){        // Option for INFO button press to start DemoMode 
     demoMode();
    // digitalWrite(LED6_PIN, HIGH); 
     Serial.print("***Demo Mode active***");
     }   */                                             // Replaced this code with an ISR 

     // flag for ***Demo Mode*** interrupt
volatile bool demoModeTriggered = false;            
//ISR,  the 'IRAM_ATTR' is needed by the ESP32 to put this function in fast-access memory (IRAM).
void IRAM_ATTR handleDemoButtonPress() {
  demoModeTriggered = true;
}
// Trigger DEMO MODE when INFO button is pressed
attachInterrupt(digitalPinToInterrupt(demoMode_PIN), handleDemoButtonPress, FALLING); 

  if (demoModeTriggered) {                             // Check for flag
    demoModeTriggered = false;                        // If flag set then reset the flag
    Serial.println("***Demo Mode active***");
    demoMode();                                      // call ***DEMO MODE*** function


unsigned long lastUpdate = 0;     // At set up, start the timer from zero
const unsigned long updateInterval = 15000;  // Set the update interval (in milliseconds) 15000 = every 15 seconds
// Inside loop
unsigned long currentMillis = millis();   // Get the current time in milliseconds since the program started
 // Check if it's time to send data to ThingSpeak by subtracting start time from current time 
  if (currentMillis - lastUpdate >= updateInterval) {  
   // Update the timestamp to lastUpdate with the current time for the next comparison
    lastUpdate = currentMillis;  
     ThingSpeakWrite();             // Send data
  }



