#ifndef MYSERIALCK
#define MYSERIALCK

#if(ARDUINO >= 100)
  #include<Arduino.h>
#else
  #include<WProgram.h>
#endif


class MySerial_ck{
  byte _pin;
  byte _ck_pin;
  unsigned int _bit_time;
  unsigned int _line_up_time;
  bool _signal = false;

  public: 
    // Constructor
    MySerial_ck();
    
    // Transmitter
    void begin_t(byte pin1, byte pin2, unsigned int bitTime, unsigned int lineUpTime=1000);
    void transmit(byte _buf[255], int byteTotal);
    
    // Receiver
    void begin_r(byte pin1, byte pin2);
    bool signal();
    void listen();
    int receive(byte _buf[255]);
  
  private:
    
};





#endif
