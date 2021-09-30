MySerial is a one-wire serial protocol.
I have used it at bitrates as high as 10kbps, but I usually use it at 1kbps and have no issues. Minimum bitrate is 15.3bps.
It has been tested on the ATMEGA8 and ATMEGA328P, both using the 16MHz external oscillator. Internal 8MHz oscillator does not seem to work. It's
    probably not accurate enough.
MySerial can be (and has been) used for sending data and then receiving a response through the same data pin, which allows a master-slave setup.
    When using this configuration, it is recommended to wait 1mS between receiving data and changing to transmitter mode. A pull-DOWN resistor
    is also required in order to prevent floating during the short period of time (about 1mS) that both the master and slave are in receive
    mode.


Class name: MySerial

Functions:
    begin_t(byte pin, unsigned int bitTime, unsigned int lineUpTime=1000)
        This function sets the serial object as a transmitter.
        'pin' is the digital pin used to transmit data.
        'bitTime' is the time between bits, in microseconds. For example, a bitTime of 1000 would yield a bitrate of 1kbps and a bitTime of
            100 would yield a bitrate of 10kbps.
        'lineUpTime' is the time that the transmitter pulls the transmit pin high for, in order for the receiver to prepare to receive data.
            This is an optional parameter to set.
    
    transmit(byte _buf[255], int byteTotal)
        This function transmits data.
        '_buf' is the data to be sent. A maximum of 255 bytes of data can be sent per transmission, because the very first byte sent (which
            does not count in 'byteTotal') is the number of bytes that are coming through.
        'byteTotal' is the number of bytes that are desired to be sent. Again, this does not count the first actual byte of data.
    
    begin_r(byte pin, unsigned int bitTime)
        This function sets the serial object as a receiver.
        'pin' is the digital pin used to receive data.
        'bitTime' is the time between bits, in microseconds. This must match the bitTime for the transmitter.
    
    listen()
        This function is used when in receive mode (set with begin_r()) to check the data pin to see if there is an incoming message.
    
    bool signal()
        This function returns whether or not there is an incoming message. 'true' indicates an incoming message, 'false' indicates no incoming
            message.
    
    int receive(byte _buf[255])
        This function receives the data sent by the transmitter on the other end.
        '_buf' is the data to be sent.
        'receive()' returns the number of bytes it received in case that is required. If it returns -1, it timed out waiting for data,
            indicating corrupted data.
        
        
        
