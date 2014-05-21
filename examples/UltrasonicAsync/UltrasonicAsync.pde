#include "Ultrasonic.h"
#include "config.h"

#define toggle(pin) digitalWrite(pin, !digitalRead(pin))

void toggleLed(){toggle(13);}

Ultrasonic us = Ultrasonic::create(ULTRASONIC_PIN_TRIG, ULTRASONIC_PIN_ECHO, ULTRASONIC_INTERRUPT_NUMBER);
// Ultrasonic us2 = Ultrasonic::create(11, 3, 1);

void setup()
{
  Serial.begin(SERIAL_SPEED);
  Serial.println("Setup done. Starting...");
}

void loop(){

  us.UpdateDistanceAsync();
  delay(1000);
  float dist = us.getDistance();
  Serial.println("Us1:");
  Serial.println(dist);

  // us2.UpdateDistanceAsync();
  // delay(800);
  // dist = us2.getDistance();
  // Serial.println("Us2:");
  // Serial.println(dist);
}
