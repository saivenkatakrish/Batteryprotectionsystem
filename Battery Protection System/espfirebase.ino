#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>

#define _SSID "KK"                  // Your WiFi SSID
#define _PASSWORD "12345678"        // Your WiFi Password
#define REFERENCE_URL "https://e-bms-80fc0-default-rtdb.asia-southeast1.firebasedatabase.app/"

Firebase firebase(REFERENCE_URL);    // Create an instance of the Firebase class

void setup() 
{
  Serial.begin(9600);
  pinMode(D3, OUTPUT);
  WiFi.begin(_SSID, _PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("IP Address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(D3, LOW);
}

void loop() 
{
  if (Serial.available() > 0) 
  {
    String data = Serial.readStringUntil('\n');
    Serial.println(data);

    // Parse the data separated by commas
    int comma1 = data.indexOf(',');
    int comma2 = data.indexOf(',', comma1 + 1);
    int comma3 = data.indexOf(',', comma2 + 1);

    if (comma1 != -1 && comma2 != -1 && comma3 != -1) 
    {
      float Voltage = data.substring(0, comma1).toFloat();
      float Temperature = data.substring(comma1 + 1, comma2).toFloat();
      String Current = data.substring(comma2 + 1, comma3); // Extract Current as a string
      float soc = data.substring(comma3 + 1).toFloat();

      // Check Firebase Load value
      if (firebase.getString("E-BMS/Load") == "0") 
      {
        Serial.println("Supply Stopped due to Firebase Load value");
        firebase.setString("E-BMS/status", "Supply Stopped due to Load condition");
        digitalWrite(D3, LOW); // Turn off supply
      }
      else
      {
        // Check if voltage >= 4 or temperature > 34
        if (Voltage >= 4 || Temperature > 34) 
        {
          Serial.println("Supply Stopped due to high voltage or temperature");
          firebase.setString("E-BMS/status", "Supply_Stopped");
          digitalWrite(D3, LOW); // Turn off supply
        } 
        else 
        {
          Serial.println("Supply Allowed");
          firebase.setString("E-BMS/status", "Supply_Allowed");
          digitalWrite(D3, HIGH); // Turn on supply
        }

        // Log data to Firebase
        firebase.setString("E-BMS/Voltage", String(Voltage)); 
        firebase.setString("E-BMS/soc", String(soc));
        firebase.setString("E-BMS/Current", Current);   
        firebase.setString("E-BMS/Temperature", String(Temperature)); 
      }
    }
  }
}
