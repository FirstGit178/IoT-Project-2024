void DisplayLEDs(){ 
if (distance_cm < DISTANCE_THRESHOLD) {               // if temperature is below TEMPERATURE THRESHOLD)
  digitalWrite(LED1_PIN, HIGH);                      // turn on LED1

} else {
  digitalWrite(LED1_PIN, LOW);                       // turn off LED1
  }

if (DHT.temperature == DHT_TEMPERATURE_THRESHOLD) {  // if temperature is equal to TEMPERATURE THRESHOLD)
  digitalWrite(LED3_PIN, HIGH);                      // turn on LED3
  digitalWrite(LED2_PIN, LOW);                       // turn off LED2
  digitalWrite(LED4_PIN, LOW);                       // turn off LED4
  } 
  else if (DHT.temperature > DHT_TEMPERATURE_THRESHOLD){    // if temperature is above TEMPERATURE THRESHOLD)
    digitalWrite(LED2_PIN, HIGH);                       // turn on LED2
    digitalWrite(LED3_PIN, LOW);                        // turn off LED3
    digitalWrite(LED4_PIN, LOW);                        // turn off LED4
    } 
    else if (DHT.temperature < DHT_TEMPERATURE_THRESHOLD) {  // if temperature is below TEMPERATURE THRESHOLD)
        digitalWrite(LED4_PIN, HIGH);                      // turn on LED4
        digitalWrite(LED2_PIN, LOW);                       // turn off LED2
        digitalWrite(LED3_PIN, LOW);                       // turn off LED3
        }


if (DHT.humidity > DHT_HUMIDITY_THRESHOLD) {        // if humidity is above or below TEMPERATURE THRESHOLD)
    digitalWrite(LED5_PIN, HIGH);                     // turn on LED5
  } 
  else {
    digitalWrite(LED5_PIN, LOW);                      // turn off LED5
    }

if (sensorValue < 2023) {
    digitalWrite(LED6_PIN, HIGH);                    // turn on LED6
  } 
  else {
    digitalWrite(LED6_PIN, LOW);                     // turn off LED6
    }
}