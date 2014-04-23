#ifndef Ultrasonic_h
#define Ultrasonic_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Ultrasonic
{
  public:
    static volatile int time;
    static volatile int result_time;


    Ultrasonic(int trig_pin, int echo_pin);
    void   SendPulse();
    double Ranging();
    static void   onRisingEcho();
    static void   onFallingEcho();

  private:
    int trig_pin;
    int echo_pin;
    double  duration, distacne_cm;

};

#endif //#ifndef Ultrasonic_h
