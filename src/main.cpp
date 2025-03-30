#include <Arduino.h>

// put function declarations here:
int LED_D4 = 12;
int LED_D5 = 13;


void setup() {
pinMode(LED_D4,OUTPUT);
pinMode(LED_D5,OUTPUT);
}

void loop() {
  digitalWrite(LED_D4, LOW);
  digitalWrite(LED_D5, HIGH);
  delay(1000);
  digitalWrite(LED_D4, HIGH);
  digitalWrite(LED_D5, LOW);
  delay(1000);
}

