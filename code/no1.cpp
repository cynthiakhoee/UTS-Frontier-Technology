
#include <Arduino.h>

const int buttonPin = 2;

int buttonState = 0;
int lastButtonState = 0;
int startPressed = 0;
int count = 0;
bool status=false;

void setup() {
  Serial.begin(115200);
    pinMode(buttonPin, INPUT);
    pinMode(LED_BUILTIN,OUTPUT);
    
    
    
}

void updateState() {
  // the button has been just released
  if (buttonState ==HIGH ) {
    startPressed = millis();
    Serial.println("Button are released ");
    Serial.printf("%d",millis()-startPressed);
    digitalWrite(LED_BUILTIN, HIGH);
    status=false;
    // delay(100);
    
  // the button has been just pressed
  } else if (buttonState == LOW) {
           Serial.println("Button are pressed ");
           status=true;
  }
  delay(500);
}

void loop() {
    buttonState = digitalRead(buttonPin);
    // Serial.print(buttonState);

    if(buttonState != lastButtonState) {
        updateState();
        lastButtonState = buttonState;
    }
    else if(millis()-startPressed>=10000 && status){
    Serial.println("sudah 10 detik");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    status=false;
    } else if(buttonState == LOW && status){
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    // buttonState=LOW;  
  }

    
}