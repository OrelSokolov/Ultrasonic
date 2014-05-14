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
    static const float INF_DIST=99999.999;
    static volatile int result_time;


    Ultrasonic(int trig_pin, int echo_pin, byte interrupt_number, float K_arg=0.00016, float B_arg = 55.9);
    void   UpdateDistanceAsync();
    double Ranging();
    static void   onRisingEcho();
    static void   onFallingEcho();

  private:
    static volatile int echo_delay_time;

    int     trig_pin,
            echo_pin;
    double  duration,
            distacne_cm;
    float K, B;
    byte interrupt_number;

    void SendPulse(byte delay_us);
    void ResetEchoDelay();
    float koef(float x);

};

#endif //#ifndef Ultrasonic_h
