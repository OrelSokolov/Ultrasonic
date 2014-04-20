#ifndef Ultrasonic_h
#define Ultrasonic_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define CM 1
#define INC 0

class Ultrasonic
{
  public:
    Ultrasonic(int trig_pin, int echo_pin);
    void   SendPulse();
    double Ranging();

  private:
    int trig_pin;
    int echo_pin;
    double  duration, distacne_cm;

};

#endif //#ifndef Ultrasonic_h
