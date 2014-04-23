// Us2.ino
#include "Ultrasonic.h"

Ultrasonic us(12, 2);

float koef(float x){
  const float K = 0.00016;
  const float B = 55.9;

  // float result = K*x+B;
  // Serial.print("result: ");
  // Serial.println(result);
  // return result;
  return K*x+B;
}

void setup() {
    Serial.begin(9600);             // start the serial port
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    Serial.println("Hello");
}

void loop()
{
  us.SendPulse();
  delay(1000);
  Serial.print("Time: ");
  float _time = float(Ultrasonic::result_time);
  Serial.println(_time);
  float dist = _time/koef(_time);
  Serial.println(dist);
  Ultrasonic::result_time = 0;
}
