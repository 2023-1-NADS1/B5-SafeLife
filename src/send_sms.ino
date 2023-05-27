#include "twilio.hpp"

// Set these - but DON'T push them to GitHub!
static const char *ssid = "Caio";
static const char *password = "241204ca";

// Values from Twilio (find them on the dashboard)
static const char *account_sid = "AC9cfac0ba123b27f6f5084485aa9b87ea";
static const char *auth_token = "56db5583d77533663937502e5519a2e1";
// Phone number should start with "+<countrycode>"
static const char *from_number = "+13159097507";

// You choose!
// Phone number should start with "+<countrycode>"
static const char *to_number = "+5511970501468";
static const char *message = "Sent from my ESP32";

Twilio *twilio;

const int buttonPin = 5;
volatile bool buttonPressed = false;

void IRAM_ATTR buttonInterrupt() {
  buttonPressed = true;
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING);  
  
  Serial.begin(115200);
  Serial.print("Connecting to WiFi network '");
  Serial.print(ssid);
  Serial.println("'...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting...");
    delay(500);
  }
  Serial.println("Connected!");

  twilio = new Twilio(account_sid, auth_token);
}

void loop() {
  if (buttonPressed) {
    buttonPressed = false;  
    String response;
    bool success = twilio->send_message(to_number, from_number, message, response);
    if (success) {
      Serial.println("Sent message successfully!");
    } else {
      Serial.println(response);
    }
  }
  
  // Resto do código do loop
}
