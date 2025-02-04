#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

float correctionfactor = 0.1;
int VoltageSensor = A1;
float vout = 0.0;
float vin = 0.0;
// two resistors 30K and 7.5k ohm
float R1 = 30000; //   
float R2 = 7500;  //  
int value = 0.0;
float soc = 0.0; // State of Charge

const float VCC = 5.0; // Voltage of the Arduino supply
const int model = 0; // Index for the sensitivity array
float cutOffLimit = 1.01; // Cutoff current limit in amperes
float sensitivity[] = {0.185}; // Sensitivity of the ACS712 model (185 mV/A for ACS712-05B)
float QOV = 2.5; // Quiescent Output Voltage (2.5V for a 5V supply)
float voltage;
float current;

// Rated values for supply control
const float ratedVoltage1 = 3.9; // Example rated voltage
const float ratedTemperature = 37.0; // Example rated temperature

#define SUPPLY_CONTROL_PIN 3        // Define the digital pin for supply control
#define CURRENT_SENSOR_PIN A0       // Define the analog pin for the current sensor

void setup() 
{
  Serial.begin(9600); // Initialize SoftwareSerial with baud rate 115200
  pinMode(VoltageSensor, INPUT);
  Serial.println("ACS712 current sensor");

  // Initialize DHT sensor
  dht.begin();

  // Initialize supply control pin
  pinMode(SUPPLY_CONTROL_PIN, OUTPUT);
  digitalWrite(SUPPLY_CONTROL_PIN, HIGH); // Assume HIGH means supply is allowed initially

  // Initialize the LCD
  lcd.init();
  lcd.backlight(); // Turn on the backlight
  lcd.setCursor(0, 0);
}

void loop() {
  // Voltage Sensor
  value = analogRead(VoltageSensor);
  vout = (value * 5.0) / 1024.0; // Assuming voltage sensor gives 0-5V output
  vin = vout *  ((R1 + R2)/R2); // Voltage divider formula
  vin = vin + correctionfactor;

  // Ensure vin is within expected range
  vin = constrain(vin, 0, 4); // Assuming maximum 12V voltage

  // Display voltage reading on LCD
  lcd.clear();
  lcd.print("Voltage = ");
  lcd.print(vin, 2);
  delay(1000); // Delay for 1000 ms

  // DHT11 Temperature Sensor
  float temperature = dht.readTemperature(); // Read temperature as Celsius (default)

  // Display temperature reading on LCD
  lcd.clear();
  lcd.print("Temperature = ");
  lcd.print(temperature, 1);
  delay(1000); // Delay for 1000 ms

  // Read the raw voltage from the current sensor
  float voltage_raw = (VCC / 1023.0) * analogRead(CURRENT_SENSOR_PIN);
  
  // Adjust the raw voltage to get the actual sensor output voltage
  voltage = voltage_raw - QOV;
  
  // Calculate the current based on the adjusted voltage
  current = voltage / sensitivity[model];

  // Debug: Print raw and adjusted voltage values
  Serial.print("Raw Voltage: ");
  Serial.println(voltage_raw, 3);
  Serial.print("Adjusted Voltage: ");
  Serial.println(voltage, 3);

  // Control the supply based on voltage and temperature
  if (vin > ratedVoltage1 || temperature > ratedTemperature) 
  {
    Serial.println("Supply Stopped");
    digitalWrite(SUPPLY_CONTROL_PIN, LOW);
  } 
  else 
  {
    Serial.println("Supply Allowed");
    digitalWrite(SUPPLY_CONTROL_PIN, HIGH);
  }

  // Calculate State of Charge (SOC) for a 12V, 7A battery
  // Assuming the battery voltage range is 10.5V to 12.6V for a 12V battery
  soc = map(vin, 0, 4, 0, 100);

  // Display State of Charge
  lcd.clear();
  lcd.print("SOC = ");
  lcd.print(soc);
  lcd.print("%");
  delay(1000); // Delay for 1000 ms

  // ACS712 Current Sensor
  float sensitivity = 0.185; // Sensitivity of ACS712 sensor (mV/A)
  float zeroCurrentVoltage = 2.5; // Zero current output voltage of ACS712 sensor (V)

  // Read analog input from ACS712 sensor
  int rawValue = analogRead(A0);

  // Convert raw value to voltage
  float voltage = (rawValue / 1023.0) * 5.0;

  // Calculate current based on voltage and sensor characteristics
  float current = ((voltage - zeroCurrentVoltage) / sensitivity);

  // Display current reading on LCD
  lcd.clear();
  lcd.print("Current = ");
  lcd.print(current, 2);
  delay(1000); // Delay for 100 ms

  Serial.print(vin, 2);
  Serial.print(",");
  Serial.print(temperature, 1);
  Serial.print(",");
  Serial.print(current, 2);
  Serial.print(",");
  Serial.print(soc);
  
  Serial.println(); // Print newline to signify end of data

  delay(5000); // Delay for 5 seconds before sending the next set of data
}
