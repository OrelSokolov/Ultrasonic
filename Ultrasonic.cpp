#include "Ultrasonic.h"

typedef  void (Ultrasonic::*UltrasonicMemFn)();

Ultrasonic* Ultrasonic::lock=NULL;

void ultrasonic_on_rising_echo_wrapper(){
  Ultrasonic::lock->onRisingEcho();
}

void ultrasonic_on_falling_echo_wrapper(){
  Ultrasonic::lock->onFallingEcho();
}

Ultrasonic Ultrasonic::initialize(int trig_arg, int echo_arg, byte interrupt_number_arg, float K_arg, float B_arg ){
  void (*ultrasonic_on_rising_echo_wrapper_ptr)() = ultrasonic_on_rising_echo_wrapper;
  void (*ultrasonic_on_falling_echo_wrapper_ptr)() = ultrasonic_on_falling_echo_wrapper;

  Ultrasonic temp(trig_arg, echo_arg, interrupt_number_arg, ultrasonic_on_rising_echo_wrapper_ptr, ultrasonic_on_falling_echo_wrapper_ptr, K_arg, B_arg );

  return temp;
}

Ultrasonic::Ultrasonic(int trig_arg, int echo_arg, byte interrupt_number_arg, void (*on_rising_ptr)(), void (*on_falling_ptr)(), float K_arg, float B_arg )
{
   echo_delay_time=0;
   result_time=0;

   trig_pin = trig_arg;
   echo_pin = echo_arg;
   interrupt_number = interrupt_number_arg;
   K = K_arg;
   B = B_arg;
   on_rising_echo_wrapper = on_rising_ptr;
   on_falling_echo_wrapper = on_falling_ptr;

   pinMode(trig_pin, OUTPUT);
   pinMode(echo_pin, INPUT);
}

void Ultrasonic::ResetEchoDelay(){
  echo_delay_time=0;
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
  Ultrasonic::lock = this;
  attachInterrupt(interrupt_number, on_rising_echo_wrapper, RISING);
  ResetEchoDelay();
  SendPulse(10);
}

void Ultrasonic::onRisingEcho(){
  detachInterrupt(interrupt_number);
  echo_delay_time=micros();
  attachInterrupt(interrupt_number, on_falling_echo_wrapper, FALLING);
}

void Ultrasonic::onFallingEcho(){
  if(echo_delay_time!=0){
    int echo_length=micros()-echo_delay_time;
    result_time=(echo_length/10)*10;
  }
}

float Ultrasonic::koef(float x){
  return K*x+B;
}

double Ultrasonic::Ranging()
{
  long _time = result_time;
  distacne_cm = _time/koef(_time);
  return distacne_cm;
}
