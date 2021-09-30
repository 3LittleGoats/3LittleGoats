#ifndef MYSERIAL
#define MYSERIAL

#if(ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif


class MySerial{
  // Class-scope variables
  byte _pin;
  unsigned int _bit_time;
  unsigned int _line_up_time;
  bool _signal = false;
  
  public:
    // Constructor
    MySerial();
    // Transmitter
    void begin_t(byte pin, unsigned int bitTime, unsigned int lineUpTime=1000);
    void transmit(byte _buf[255], int byteTotal);
    
    // Receiver
    void begin_r(byte pin, unsigned int bitTime);
    bool signal();
    void listen();
    int receive(byte _buf[255]);

  private:
    
};


#endif
