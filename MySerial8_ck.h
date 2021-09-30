#ifndef MYSERIAL8CK
  #define MYSERIAL8CK

#if(ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

class MySerial8_ck{
  // Class-scope variables
  unsigned int _bit_time;
  unsigned int _line_up_time;
  bool _signal = false;

  public:
    // Constructor
    MySerial8_ck();
    // Transmitter
    void begin_t(unsigned int bitTime, unsigned int lineUpTime=100);
    void transmit(byte _buf[255], int byteTotal);
    
    // Receiver
    void begin_r();
    bool signal();
    void listen();
    int receive(byte _buf[255]);
    
  
  private:
    
};




#endif
