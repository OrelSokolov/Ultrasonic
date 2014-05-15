
#ifndef config_h
#define config_h

  #define BOARD UNO

  #define DELAY_TIME 1000

  #if (BOARD == UNO)
    #define ULTRASONIC_PIN_TRIG 12
    #define ULTRASONIC_PIN_ECHO 2
    #define ULTRASONIC_INTERRUPT_NUMBER 0
    #define SERIAL_SPEED 9600
  #elif (BOARD == NANO)


  #endif

#endif
