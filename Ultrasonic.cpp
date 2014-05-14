#include "Ultrasonic.h"

volatile int Ultrasonic::echo_delay_time=0;
volatile int Ultrasonic::result_time=0;

Ultrasonic::Ultrasonic(int trig_arg, int echo_arg, byte interrupt_number_arg, float K_arg, float B_arg )
{
   trig_pin = trig_arg;
   echo_pin = echo_arg;
   interrupt_number = interrupt_number_arg;
   K = K_arg;
   B = B_arg;

   pinMode(trig_pin, OUTPUT);
   pinMode(echo_pin, INPUT);
}

void Ultrasonic::ResetEchoDelay(){
  Ultrasonic::echo_delay_time=0;
}

void Ultrasonic::SendPulse(byte delay_us){
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(delay_us);
  digitalWrite(trig_pin, LOW);
}

void Ultrasonic::UpdateDistanceAsync(){
  // delay(10);
  attachInterrupt(interrupt_number, onRisingEcho, RISING);
  ResetEchoDelay();
  SendPulse(10);
}

void Ultrasonic::onRisingEcho(){
  detachInterrupt(0);
  Ultrasonic::echo_delay_time=micros();
  attachInterrupt(0, onFallingEcho, FALLING);
}

void Ultrasonic::onFallingEcho(){
  if(Ultrasonic::echo_delay_time!=0){
    int echo_length=micros()-Ultrasonic::echo_delay_time;
    Ultrasonic::result_time=(echo_length/10)*10;
  }
}

float Ultrasonic::koef(float x){
  return K*x+B;
}

double Ultrasonic::Ranging()
{
  long _time = Ultrasonic::result_time;
  distacne_cm = _time/koef(_time);
  return distacne_cm;
}
