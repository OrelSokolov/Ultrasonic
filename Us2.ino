// Us2.ino
#include "Ultrasonic.h"

Ultrasonic us(12, 13);

void setup() {
  Serial.begin(9600);             // start the serial port

}

void loop() {
  Serial.println(us.Ranging());
  delay(500);
}

