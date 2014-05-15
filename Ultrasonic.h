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
    static Ultrasonic* lock;

    static Ultrasonic create(int trig_pin, int echo_pin, byte interrupt_number, float K_arg=0.00016, float B_arg = 55.9);


    void   UpdateDistanceAsync();
    double getDistance();
    friend void ultrasonic_on_falling_echo_wrapper();
    friend void ultrasonic_on_rising_echo_wrapper();


  private:
    void (*on_rising_echo_wrapper)();
    void (*on_falling_echo_wrapper)();

    volatile int result_time, echo_delay_time;
    int     trig_pin, echo_pin;
    double  duration, distacne_cm;
    float    K, B;
    byte    interrupt_number;

    Ultrasonic(int trig_pin, int echo_pin, byte interrupt_number, void (*)() , void (*)(), float K_arg=0.00016, float B_arg = 55.9);

    void SendPulse(byte delay_us);
    void ResetEchoDelay();
    void onRisingEcho();
    void onFallingEcho();
    float koef(float x);

};

#endif //#ifndef Ultrasonic_h
