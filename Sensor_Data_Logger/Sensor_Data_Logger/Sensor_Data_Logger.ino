// MILESTONE 1
// Author: Spoon1405

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// configurations
#define SAMPLE_INTERVAL_MS 2000UL
#define SERIAL_BAUD 115200
#define BME280_I2C_ADDR 0x76 // Make sure to try 0x77 if begin() fails

// globals
Adafruit_BME280 bme; // sensor
unsigned long lastSampleTime = 0;   // Loop check
bool samplingEnabled = true;        // Gloabal check flag
uint32_t sampleCount = 0;           // count check

void setup() {
  Serial.begin(SERIAL_BAUD);  // serial monitor setup
  while (!Serial) { ; }      // Just a safety check to wait for serial monitor to start

  Serial.println(F(" Sensor Data Logger MILESTONE 1 "));
  Serial.println(F(" INITIALISING BME280 "));

  if(!bme.begin(BME280_I2C_ADDR)) {     // Fail check
    Serial.println(F(" ERROR: BME280 not found. Potential wiring issue or I2C address"));
    Serial.print(F(" HALTING."));
    while(true) { ; }   // HARD STOP
  }

  // We want to set BME280 to noraml mode with standard oversampling
  bme.setSampling(
    Adafruit_BME280::MODE_NORMAL,
    Adafruit_BME280::SAMPLING_X1,   // temp
    Adafruit_BME280::SAMPLING_X1,   // pressure
    Adafruit_BME280::SAMPLING_X1,   // humidity
    Adafruit_BME280::FILTER_OFF,    // make sure there is no IIR filter
    Adafruit_BME280::STANDBY_MS_1000
  );

  Serial.println(F(" BME280 OK "));
  Serial.print(F(" Sample Interval: "));
  Serial.print(SAMPLE_INTERVAL_MS);
  Serial.println(F(" ms"));

  // CSV header
  Serial.println(F("uptime_ms,sample,temp_C,humidity_pct,pressure_hPa"));
}

void loop() {
  // setup millis()
  unsigned long now = millis();

  if(samplingEnabled && (now - lastSampleTime >= SAMPLE_INTERVAL_MS)) {
    lastSampleTime = now; //millis exchange
    takeSample(now);    // actual sample command
  }

}

void takeSample(unsigned long timestamp) {
  float temp = bme.readTemperature();         // set to celsius
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F; // transforms Pa to hPa

  sampleCount++; // increment sample time

  // CSV output
  Serial.print(timestamp);            Serial.print(',');
  Serial.print(sampleCount);        Serial.print(',');
  Serial.print(temp, 2);              Serial.print(',');
  Serial.print(humidity, 2);          Serial.print(',');
  Serial.println(pressure, 2);
}
