// Us2.ino
#include "Ultrasonic.h"

#define BOARD UNO

#if (BOARD == UNO)
  #define ULTRASONIC_PIN_TRIG 12
  #define ULTRASONIC_PIN_ECHO 2
  #define ULTRASONIC_INTERRUPT_NUMBER 0
  #define SERIAL_SPEED 9600
#elif (BOARD == NANO)


#endif

Ultrasonic us = Ultrasonic::initialize(ULTRASONIC_PIN_TRIG, ULTRASONIC_PIN_ECHO, ULTRASONIC_INTERRUPT_NUMBER);


void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println("Setup done. Starting...");
}

void loop()
{
  us.UpdateDistanceAsync();
  delay(1000);
  float dist = us.Ranging();
  Serial.println(dist);
}
