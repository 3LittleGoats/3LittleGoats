MySerial_ck is a two-wire serial protocol. 1 wire is used for data, 1 wire is used for synchronization clock.
It was originally designed to help develop a much faster serial protocol, MySerial8_ck.
The fastest reliable bitrate MySerial_ck can operate at is 100kbps. I have run it at 500kbps, but about 1 out of every 10 bytes would be
    corrupted.
As is the same for every one of these serial protocols (except for MySerial8_ck), MySerial_ck was tested and developed using the ATMEGA8 and
    ATMEGA328P.
Each time the clock pin changes, a bit is sent.
MySerial_ck, just like all of these serial protocols, can be used for a bidirectional transmitter and receiver setup. It is recommended to wait
    1mS between receiving data and changing to transmitter mode. A pull-DOWN resistor (I use 100kohm, but 10kohm or anything similar should
    work fine) is required.
The receiver for all of these serial protocols which have a clock pin is paced by the clock pin, controlled by the transmitter. Thus, it does
    not need to reference its own clock to know when the next bit is going to be sent. When the clock pin changes, the next bit is ready to be
    received.


Class name: MySerial_ck

Functions:
    begin_t(byte pin1, byte pin2, unsigned int bitTime, unsigned int lineUpTime=1000)
        'pin1' is the data pin.
        'pin2' is the clock pin.
        'bitTime' is the time between each bit (and clock pin change).
        'lineUpTime' is the time that the clock pin is initially held high for to "arm" the receiver.
    
    transmit(byte _buf[255], int byteTotal)
    
    begin_r(byte pin1, byte pin2)
        'pin1' is the data pin.
        'pin2' is the clock pin.
        Note how bitTime is not required for the receiver function here.
    
    listen()
    
    bool signal()
    
    int receive(byte _buf[255])
