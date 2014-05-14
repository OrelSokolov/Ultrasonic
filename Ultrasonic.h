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
    volatile int result_time;
    static Ultrasonic* lock;

    static bool try_acquire(Ultrasonic*);
    static bool try_free(Ultrasonic*);


    void (*on_rising_echo_wrapper)();
    void (*on_falling_echo_wrapper)();


    static Ultrasonic initialize(int trig_pin, int echo_pin, byte interrupt_number, float K_arg=0.00016, float B_arg = 55.9);

    Ultrasonic(int trig_pin, int echo_pin, byte interrupt_number, void (*)() , void (*)(), float K_arg=0.00016, float B_arg = 55.9);

    void   UpdateDistanceAsync();
    double Ranging();
    void   onRisingEcho();
    void   onFallingEcho();

  private:
    volatile int echo_delay_time;

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
