// Us2.ino
#include "Ultrasonic.h"
#include "config.h"


Ultrasonic us = Ultrasonic::create(ULTRASONIC_PIN_TRIG, ULTRASONIC_PIN_ECHO, ULTRASONIC_INTERRUPT_NUMBER);


void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println("Setup done. Starting...");
}

void loop()
{
  us.UpdateDistanceAsync();
  delay(DELAY_TIME);
  float dist = us.getDistance();
  Serial.println(dist);
}
