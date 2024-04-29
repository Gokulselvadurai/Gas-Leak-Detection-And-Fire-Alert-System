#define BLYNK_TEMPLATE_ID "Template_Id"
#define BLYNK_TEMPLATE_NAME "Home security"
#define BLYNK_AUTH_TOKEN "Token"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "Token"; // Your Blynk authentication token
char ssid[] = "Network_Name";  // Your WiFi network SSID
char pass[] = "Network_Pass";  // Your WiFi network password

const int flameSensorPin = 34; // Pin connected to flame sensor
const int gasSensorPin = 33;   // Pin connected to gas sensor
const int buzzerPin = 23;      // Pin connected to the buzzer
const int thresholdf = 4000;    // Threshold value for flame sensor trigger
const int thresholdg = 300;     // Threshold value for gas sensor trigger

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  Blynk.run();
  int flameValue = analogRead(flameSensorPin);
  int gasValue = analogRead(gasSensorPin);

  Serial.print("Flame sensor value: ");
  Serial.println(flameValue);
  
  Serial.print("Gas sensor value: ");
  Serial.println(gasValue);

  if (flameValue < thresholdf || gasValue > thresholdg) {
    digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
    Serial.println("Fire or gas detected!");
  } else {
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  }

  Blynk.virtualWrite(V0, flameValue); // Send flame sensor value to Blynk app
  Blynk.virtualWrite(V1, gasValue);   // Send gas sensor value to Blynk app

  delay(1000); // Adjust delay according to your needs
}