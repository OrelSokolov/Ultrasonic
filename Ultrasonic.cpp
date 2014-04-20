#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int trig_arg, int echo_arg)
{
   trig_pin = trig_arg;
   echo_pin = echo_arg;
   pinMode(trig_pin, OUTPUT);
   pinMode(echo_pin, INPUT);
}

void Ultrasonic::SendPulse(){
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
}

double Ultrasonic::Ranging()
{
  SendPulse();
  duration = pulseIn(echo_pin, HIGH);

  distacne_cm = duration/58.0;
  return distacne_cm;
}
