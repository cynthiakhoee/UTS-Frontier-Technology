
#include <Arduino.h>
#define Button_A 0         //GPIO0 
#define Button_B 4         //GPIO4
int button1=0, button2 = 0;
int lastButtonState = 0;
int blinktime=1000;
int previousButton_A,previousButton_B = 1;

void setup() {
  Serial.begin(115200);
    pinMode(Button_A, INPUT);
    pinMode(Button_B,INPUT);
    pinMode(LED_BUILTIN,OUTPUT);
    
    
    
}

void buttonA(){
   int currentButton_A = digitalRead(Button_A);
   if (currentButton_A != previousButton_A)
    {
        if (currentButton_A == 0)
        {
              blinktime= blinktime+100;
              Serial.printf("%d",blinktime);
        }
        else
        {
            Serial.println("You have just released button A");
        }
        previousButton_A = currentButton_A;
    }
}
void buttonB(){
  int currentButton_B = digitalRead(Button_B);
  if (currentButton_B != previousButton_B)
    {
        if (currentButton_B == 0)
        {
              blinktime= blinktime-100;
              Serial.printf("%d",blinktime);
        }
        else
        {
            Serial.println("You have just released button B");
        }
        previousButton_B = currentButton_B;
    }
}
void Blink(){
  digitalWrite(LED_BUILTIN, LOW);
    delay(blinktime);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(blinktime);

}

void loop() {
   if(blinktime>=2500){
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else {
      buttonA();
    }
    buttonB();
    Blink();
    
}