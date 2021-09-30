Make sure to read through the READMEs for MySerial, MySerial_ck, MySerial2_ck, and MySerial4_ck, as there is data in those I have not repeated
    here.
MySerial8_ck is the fun one! It has been tested to work at 800kbps (about 733 actually), which equates to 10uS bitTime.
At this speed it appears to have a data corruption rate of 1 byte per 3000 bytes on average.
It uses the entirety of PORTD (PD0-PD7 or digital pins 0-7) for data and PB0 (digital pin 8) for the clock.
It can be (and has been) used in bidirectional communication applications such as master-slave setups. It is recommended that a delay be used
    between receiving data and changing to transmitter mode, just like it is for all of these serial protocols. Because this protocol is made for
    high-speed applications, a delay of 1mS would be large. 20uS would probably be fine. Again, a pull-DOWN resistor is necessary when used for
    this purpose.


Class name: MySerial8_ck

Functions:
    begin_t(unsigned int bitTime, unsigned int lineUpTime=100)
        The default value of 'lineUpTime' is 100 instead of 1000 because this protocol is made for speed. It only needs to be as long as you
            need it to be. The same is true for all of these serial protocols.
    
    transmit(byte _buf[255], int byteTotal)
    
    begin_r()
    
    listen()
    
    bool signal()
    
    int receive(byte _buf[255])
