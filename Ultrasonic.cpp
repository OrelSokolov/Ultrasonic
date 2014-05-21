#include "Ultrasonic.h"
#include <TimerOne.h>

Ultrasonic* Ultrasonic::lock=NULL;

void ultrasonic_on_rising_echo_wrapper(){
  Ultrasonic::lock->onRisingEcho();
}

void ultrasonic_on_falling_echo_wrapper(){
  Ultrasonic::lock->onFallingEcho();
}

void ultrasonic_on_timeout_wrapper(){
  Ultrasonic::lock->onTimeOut();
}


Ultrasonic Ultrasonic::create(int trig_arg, int echo_arg, byte interrupt_number_arg, float K_arg, float B_arg ){
  void (*ultrasonic_on_rising_echo_wrapper_ptr)() = ultrasonic_on_rising_echo_wrapper;
  void (*ultrasonic_on_falling_echo_wrapper_ptr)() = ultrasonic_on_falling_echo_wrapper;
  Timer1.initialize(30000);
  Timer1.attachInterrupt(ultrasonic_on_timeout_wrapper);
  Timer1.stop();

  return Ultrasonic(trig_arg, echo_arg, interrupt_number_arg, ultrasonic_on_rising_echo_wrapper_ptr, ultrasonic_on_falling_echo_wrapper_ptr, K_arg, B_arg );
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
  if(Ultrasonic::lock==NULL){
    Ultrasonic::lock = this;
    attachInterrupt(interrupt_number, on_rising_echo_wrapper, RISING);
    ResetEchoDelay();
    SendPulse(10);
    Timer1.start();
  }
}

void Ultrasonic::onTimeOut(){
  detachInterrupt(interrupt_number);
  Timer1.stop();
  Serial.println("Timeout");
  result_time = Ultrasonic::INF_TIME;
  Ultrasonic::lock=NULL;
}

void Ultrasonic::onRisingEcho(){
  Timer1.stop();
  detachInterrupt(interrupt_number);
  echo_delay_time=micros();
  attachInterrupt(interrupt_number, on_falling_echo_wrapper, FALLING);
}

void Ultrasonic::onFallingEcho(){
  if(echo_delay_time!=0){
    int echo_length=micros()-echo_delay_time;
    result_time=(echo_length/10)*10;
  }
  detachInterrupt(interrupt_number);
  Ultrasonic::lock=NULL;
}

float Ultrasonic::koef(float x){
  return K*x+B;
}

double Ultrasonic::getDistance()
{
  if(result_time!=Ultrasonic::INF_TIME){
    long _time = result_time;
    distance_cm = _time/koef(_time);
    return distance_cm;
  }else{
    distance_cm = Ultrasonic::INF_DIST;
    return distance_cm;
  }
}

bool Ultrasonic::is_infinity()
{
  return (distance_cm == Ultrasonic::INF_DIST);
}
