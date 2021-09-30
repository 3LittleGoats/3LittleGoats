#ifndef MYSERIAL2CK
  #define MYSERIAL2CK

#if(ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif


class MySerial2_ck{
  // Class-scope variables
  byte _pin1;
  byte _pin2;
  byte _ck_pin;
  unsigned int _bit_time;
  unsigned int _line_up_time;
  bool _signal = false;
  
  public:
    // Constructor
    MySerial2_ck();
    // Transmitter
    begin_t(byte pin1, byte pin2, byte pin3, unsigned int bitTime, unsigned int lineUpTime=1000);
    transmit(byte _buf[255], int byteTotal);
    
    // Receiver
    begin_r(byte pin1, byte pin2, byte pin3);
    bool signal();
    listen();
    int receive(byte _buf[255]);
  
  private:
    
};


#endif
