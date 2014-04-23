#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int trig_arg, int echo_arg)
{
   trig_pin = trig_arg;
   echo_pin = echo_arg;
   pinMode(trig_pin, OUTPUT);
   pinMode(echo_pin, INPUT);
}

void Ultrasonic::SendPulse(){
  delay(10);
  attachInterrupt(0, onRisingEcho, RISING);
  Ultrasonic::time=0;

  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  Serial.println("______");
}

volatile int Ultrasonic::time=0;
volatile int Ultrasonic::result_time=0;


void Ultrasonic::onRisingEcho(){
  detachInterrupt(0);
  Ultrasonic::time=micros();
  attachInterrupt(0, onFallingEcho, FALLING);
}

void Ultrasonic::onFallingEcho(){
  if(Ultrasonic::time!=0){
    int temp_time=micros()-Ultrasonic::time;
    Ultrasonic::result_time=(temp_time/10)*10;
  }
}

double Ultrasonic::Ranging()
{
  SendPulse();
  duration = pulseIn(echo_pin, HIGH);

  distacne_cm = duration/58.0;
  return distacne_cm;
}
