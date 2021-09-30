Make sure to read through the READMEs for MySerial and MySerial_ck, as there is data in those I have not repeated here.
This serial protocol has not been tested very much.
As a result, I do not remember what the maximum stable bitrate is for MySerial2_ck.
Function names and parameters are the exact same for this protocol as for MySerial_ck, the only difference being that there are 2 data wires
  instead of 1.

Class name: MySerial2_ck

Functions:
    begin_t(byte pin1, byte pin2, byte pin3, unsigned int bitTime, unsigned int lineUpTime=1000)
        'pin1' is the first data pin.
        'pin2' is the second data pin.
        'pin3 is the clock pin.
    
    transmit(byte _buf[255], int byteTotal)
    
    begin_r(byte pin1, byte pin2, byte pin3)
        'pin1' is the first data pin.
        'pin2' is the second data pin.
        'pin3 is the clock pin.
    
    listen()
    
    bool signal()
    
    int receive(byte _buf[255])
