#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_NeoPixel.h>
#define BLYNK_PRINT Serial
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//#define RED 12
//#define GREEN 13
//#define BLUE 14
#define LED_PIN 27

char auth[] = "4zZrZB50mQlI1S7QgVFuOsUvexbGCzpi";
char ssid[] = "...";
char pass[] = "...";

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);

const int analogPin = 36;  // Analog input pin 0 (GPIO 36)
int sensorValue = 0;  // Value read from the ADC

BlynkTimer timer;

BLYNK_WRITE(V1) {
  int r = param[0].asInt();
  int g = param[1].asInt();
  int b = param[2].asInt();

  strip.setPixelColor(0, strip.Color(r , g , b )); // Moderately bright green color.
  strip.show();

}

void setup() {
  Serial.begin(9600); // Initialize serial monitor output at 9600 bps:
  Blynk.begin(auth, ssid, pass);  // Connect to Blynk Cloud
  strip.begin();
  strip.show();
  timer.setInterval(2000L, AnalogPinRead);  // Run sensor scan 4 times a second
}

void AnalogPinRead() {
  sensorValue = analogRead(analogPin);  // Read the analog in value:
  Serial.print("sensor = ");  // Print the results...
  Serial.println(sensorValue);  // ...to the serial monitor:
  Blynk.virtualWrite(V0, sensorValue);  // Send the results to Gauge Widget
}

void loop() {
   if (sensorValue > (0.8 * 4095)) {
    Blynk.notify(sensorValue);
  }
  Blynk.run();
  timer.run();
}